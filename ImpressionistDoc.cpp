// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>
#include <cmath>
#include <ctime>

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <iostream>
using namespace std;

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "LinesBrush.h"
#include "ScatteredCirclesBrush.h"
#include "CirclesBrush.h"
#include "ScatteredLinesBrush.h"
#include "ScatteredPointsBrush.h"
#include "StarBrush.h"
#include "BlurFilterBrush.h"

#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }
extern float frand();

ImpressionistDoc::ImpressionistDoc()
{
	// Set NULL image name as init. 
	m_imageName[0] = '\0';

	m_nWidth = -1;
	m_ucBitmap = NULL;
	m_ucPainting = NULL;

	pic_intensity = NULL;


	// create one instance of each brush
	ImpBrush::c_nBrushCount = NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes = new ImpBrush * [ImpBrush::c_nBrushCount];


	ImpBrush::c_pBrushes[BRUSH_POINTS] = new PointBrush(this, "Points");

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES] = new LinesBrush(this, "Lines");
	ImpBrush::c_pBrushes[BRUSH_CIRCLES] = new CirclesBrush(this, "Circles");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS] = new ScatteredPointsBrush(this, "Scattered Points");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES] = new ScatteredLinesBrush(this, "Scattered Lines");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES] = new ScatteredCirclesBrush(this, "Scattered Circles");
	ImpBrush::c_pBrushes[BRUSH_STAR] = new StarBrush(this, "Stars");
	ImpBrush::c_pBrushes[BRUSH_BLUR_FILTER] = new BlurFilterBrush(this, "Filter Blur");

	//filter
	/*Gaussian_filter[0][0] = 1;
	Gaussian_filter[0][1] = 2;
	Gaussian_filter[0][2] = 1;
	Gaussian_filter[1][0] = 2;
	Gaussian_filter[1][1] = 4;
	Gaussian_filter[1][2] = 2;
	Gaussian_filter[2][0] = 1;
	Gaussian_filter[2][1] = 2;
	Gaussian_filter[2][2] = 1;*/


	


	// make one of the brushes current
	m_pCurrentBrush = ImpBrush::c_pBrushes[0];
	m_pDirectionType = 0;
	m_nRandSpaceOnOff = 0;
}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui)
{
	m_pUI = ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName()
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_nBrushType = type;
	m_pCurrentBrush = ImpBrush::c_pBrushes[type];
		if (type != BRUSH_LINES && type != BRUSH_SCATTERED_LINES) {
			m_pUI->m_StrokeDirectionTypeChoice->deactivate();
			m_pUI->m_BrushLineWidthSlider->deactivate();
			m_pUI->m_BrushLineAngleSlider->deactivate();
		}
		else {
			m_pUI->m_StrokeDirectionTypeChoice->activate();
			m_pUI->m_BrushLineWidthSlider->activate();
			m_pUI->m_BrushLineAngleSlider->activate();
		}
		
}

void ImpressionistDoc::setDirectionType(int type)
{
	if (type == 2 ) {
		setBrushType(1);//lines
	}
	else {
		setBrushType(4);//scattered lines
	}

}


int ImpressionistDoc::getBrushType() {
	return m_nBrushType;
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//Returns the line width of the brush.
int ImpressionistDoc::getLineWidth()
{
	return m_pUI->getLineWidth();
}

//Returns the line angle of the brush.
int ImpressionistDoc::getLineAngle()
{
	return m_pUI->getLineAngle();
}

int ImpressionistDoc::getAlpha()
{
	return m_pUI->getAlpha();
}

double ImpressionistDoc::getColorR()
{
	return m_pUI->getColorR();
}

double ImpressionistDoc::getColorG()
{
	return m_pUI->getColorG();
}

double ImpressionistDoc::getColorB()
{
	return m_pUI->getColorB();
}

int ImpressionistDoc::getDirectionType()
{
	return m_pDirectionType;
}

void	ImpressionistDoc::setSize(int size) {
	m_pUI->setSize(size);
	m_nSize = size;
}
void	ImpressionistDoc::setLineAngle(int angle) {
	m_pUI->setLineAngle(angle);
}

void	ImpressionistDoc::setPicIntensity()
{
	pic_intensity = new double* [m_nPaintWidth];
	for (int i = 0;i < 3;i++)
	{
		pic_intensity[i] = new double[m_nPaintHeight];
	}

}

int ImpressionistDoc::computeLineSize() {
	int size = sqrt(
		(rightStartPoint.x - rightEndPoint.x) * (rightStartPoint.x - rightEndPoint.x)
		+ (rightStartPoint.y - rightEndPoint.y) * (rightStartPoint.y - rightEndPoint.y)
	);
	return size;
}

int	ImpressionistDoc::computeLineAngle() {
	int angle;
	angle = atan2(rightEndPoint.y - rightStartPoint.y, rightEndPoint.x - rightStartPoint.x) * 180 / M_PI;
	if (angle < 0) {
		angle = angle + 360;
	}
	/*
	if (rightEndPoint.x != rightStartPoint.x) {
		double temp = (rightEndPoint.y - rightStartPoint.y)/ (rightEndPoint.x - rightStartPoint.x);
		angle = 180 + (int)((atan(temp) * 180) / M_PI);
	}
	else {
		angle = 180 + 90;
	}
	*/
	return angle;
}


//right click
void	ImpressionistDoc::rightStart(Point target) {
	rightStartPoint = target;
}
void	ImpressionistDoc::rightEnd(Point target) {
	rightEndPoint = target;
}



void ImpressionistDoc::applyCustomFilter(double* kernel, int w, int h, int button_val)
{
	m_pUI->m_paintView->refresh();
	FilterCustomize customizedFilter(kernel, w, h);
	GLubyte* target = new GLubyte[m_nWidth * m_nHeight * 3];
	memset(target, 0, sizeof(target));
	if (button_val == 1)
	{
	for (int i = 0; i < m_nHeight; ++i)
	{
		for (int j = 0; j < m_nWidth; ++j)
		{
			int pixelPos = (i * m_nWidth + j) * 3;

				target[pixelPos] = (GLubyte)customizedFilter.applyCustomizedFilter(m_ucBitmap, j, i, m_nWidth, m_nHeight, 0);
				target[pixelPos + 1] = (GLubyte)customizedFilter.applyCustomizedFilter(m_ucBitmap, j, i, m_nWidth, m_nHeight, 1);
				target[pixelPos + 2] = (GLubyte)customizedFilter.applyCustomizedFilter(m_ucBitmap, j, i, m_nWidth, m_nHeight, 2);
		}

		}
	}
	else
	{
		for (int i = 0; i < m_nHeight; ++i)
		{
			for (int j = 0; j < m_nWidth; ++j)
			{
				int pixelPos = (i * m_nWidth + j) * 3;
				target[pixelPos] = (GLubyte)customizedFilter.applyCustomizedFilter1(m_ucBitmap, j, i, m_nWidth, m_nHeight, 0);
				target[pixelPos + 1] = (GLubyte)customizedFilter.applyCustomizedFilter1(m_ucBitmap, j, i, m_nWidth, m_nHeight, 1);
				target[pixelPos + 2] = (GLubyte)customizedFilter.applyCustomizedFilter1(m_ucBitmap, j, i, m_nWidth, m_nHeight, 2);
			}
		}
	}
	m_ucPainting = target;
	
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char* iname)
{
	// try to open the image to read
	unsigned char* data;
	int				width,
		height;

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth = width;
	m_nPaintWidth = width;
	m_nHeight = height;
	m_nPaintHeight = height;

	// release old storage
	if (m_ucBitmap) delete[] m_ucBitmap;
	if (m_ucPainting) delete[] m_ucPainting;

	m_ucBitmap = data;

	// allocate space for draw view
	m_ucPainting = new unsigned char[width * height * 3];
	memset(m_ucPainting, 0, width * height * 3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(),
		m_pUI->m_mainWindow->y(),
		width * 2,
		height + 25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);
	m_pUI->m_paintView->refresh();


	return 1;
}

int ImpressionistDoc::loadAnotherImage(char* iname)
{
	// try to open the image to read
	unsigned char* data;
	int				width,
		height;

	//image error
	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth = width;
	m_nPaintWidth = width;
	m_nHeight = height;
	m_nPaintHeight = height;


}

//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char* iname)
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas()
{

	// Release old storage
	if (m_ucPainting)
	{
		delete[] m_ucPainting;

		// allocate space for draw view
		m_ucPainting = new unsigned char[m_nPaintWidth * m_nPaintHeight * 3];
		memset(m_ucPainting, 0, m_nPaintWidth * m_nPaintHeight * 3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}

	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel(int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= m_nWidth)
		x = m_nWidth - 1;

	if (y < 0)
		y = 0;
	else if (y >= m_nHeight)
		y = m_nHeight - 1;

	return (GLubyte*)(m_ucBitmap + 3 * (y * m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel(const Point p)
{
	return GetOriginalPixel(p.x, p.y);
}

void	ImpressionistDoc::autoPaint() {
	srand(time(NULL));
	int size = m_pUI->getSize();
	int space = m_pUI->getAutoSpace();
	int width = m_nWidth;
	int height = m_nHeight;
	//cout << size << ' ' << space << ' ' << width << ' ' << height << endl;
	ImpBrush* brush = m_pCurrentBrush;
	int rowNum = width / space;
	int colNum = height / space;
	int randOnOff = m_nRandSpaceOnOff;

	if (randOnOff % 2 == 0) {
		for (int i = 0; i < rowNum + 1; i++) {
			for (int j = 0; j < colNum + 1; j++) {
				int x = 1 + i * space;
				int y = 1 + j * space;
				Point a(x, y);
				//Point b(x,y);
				//cout << x << ' ' << y << endl;
				if (x == 1 && y == 1)
					brush->BrushBegin(a, a, 0);
				else
					brush->BrushMove(a, a, 0);
				brush->BrushEnd(a, a);
			}
		}
	}
	else {
		for (int i = 0; i < rowNum + 1; i++) {
			for (int j = 0; j < colNum + 1; j++) {
				int x = 1 + i * space;
				int y = 1 + j * space;
				Point a(x, y);
				//cout << "random" << endl;
				double random = rand() / ((double)RAND_MAX);
				double temp = 2 * random + 1.0;
				double range = temp * size;

				m_pUI->setSize(range);
				setSize(range);

				//if (x == 1 && y == 1)
				brush->BrushBegin(a, a, 0);

				brush->BrushEnd(a, a);
			}
		}

	}
	m_pUI->setSize(size);
	setSize(size);
}

void ImpressionistDoc::edgeDraw() {
	int width = m_nWidth;
	int height = m_nHeight;

	for (int i = 0; i < width + 1; i++) {
		for (int j = 0; j < height + 1; j++) {
			Point a(i,j);
			int* temp = m_pCurrentBrush->getGradient(a);
			int square = temp[0] * temp[0] + temp[1] * temp[1];
			double magnitude = sqrt(square);

			if (magnitude > m_pUI->getEdgeThreshold()) {
				GLubyte color[3];
				color[0] = 255;
				color[1] = 255;
				color[2] = 255;

				glPointSize(1);
				glBegin(GL_POINTS);
				glColor3ubv(color);
				glVertex2d(a.x, a.y);
				glEnd();
			}

		}
	}
}