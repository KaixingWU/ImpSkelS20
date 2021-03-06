// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"
#include "FilterCustomize.h"

class ImpressionistUI;

class ImpressionistDoc
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char* iname);			// called by the UI to load image
	int		saveImage(char* iname);			// called by the UI to save image

	int     loadAnotherImage(char* iname);


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	int		getBrushType();
	void	setBrushType(int type);			// called by the UI to set the brushType
	void	setDirectionType(int type);		// called by the UI to set the directionType
	int		getSize();						// get the UI size
	void	setLineAngle(int angle);
	int		getLineWidth();					// get the UI line width
	int		getLineAngle();					// get the UI line angle
	int	    getAlpha();						// get the UI Alpha
	double  getColorR();					// get the UI ColorR
	double  getColorG();					// get the UI ColorG
	double  getColorB();					// get the UI ColorB
	int		getDirectionType();				// get the 
	void	autoPaint();
	void	edgeDraw();

	//right click
	void	rightStart(Point target);
	void	rightEnd(Point target);

	int		computeLineSize();
	int		computeLineAngle();


	void	setSize(int size);				// set the UI size
	char* getImageName();					// get the current image name
	void	setPicIntensity();

	void applyCustomFilter(double* kernel, int w, int h, int button_val);


// Attributes
public:
	//right click
	Point rightStartPoint;
	Point rightEndPoint;


	// Dimensions of original window.
	int				m_nWidth,
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth,
					m_nPaintHeight;
	// Bitmaps for original image and painting.
	unsigned char* m_ucBitmap;
	unsigned char* m_ucPainting;
	int Gaussian_filter[3][3];
	double** pic_intensity;//calculate picture intensity



	// The current active brush.
	ImpBrush* m_pCurrentBrush;
	int m_nBrushType;
	// Size of the brush.
	int m_nSize;
	int m_pDirectionType;
	int m_nRandSpaceOnOff;

	ImpressionistUI* m_pUI;

	// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel(int x, int y);
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel(const Point p);


private:
	char			m_imageName[256];

};

extern void MessageBox(char* message);

#endif
