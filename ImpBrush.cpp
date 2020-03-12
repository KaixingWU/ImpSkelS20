//local
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"
#include <iostream>
using namespace std;

// Static class member initializations
int			ImpBrush::c_nBrushCount = 0;
ImpBrush** ImpBrush::c_pBrushes = NULL;

ImpBrush::ImpBrush(ImpressionistDoc* pDoc,
	char* name) :
	m_pDoc(pDoc),
	m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor(const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();
	double alpha = pDoc->getAlpha();

	//GLubyte color[3];

	//memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );

	//glColor3ubv( color );
	SetColor(source, alpha);
}

void ImpBrush::Blend()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);
}

void ImpBrush::SetColor(const Point source, double alpha)
{
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte color[4];

	memcpy(color, pDoc->GetOriginalPixel(source), 3);
	double chosen_R = pDoc->getColorR();
	double chosen_G = pDoc->getColorG();
	double chosen_B = pDoc->getColorB();


	/*color[0] = (int)(color[0] * chosen_R);
	color[1] = (int)(color[1] * chosen_G);
	color[2] = (int)(color[2] * chosen_B);*/

	color[3] = alpha;
	//glColor4ubv(color);
	//cout << alpha << endl;
	glColor4ub(color[0], color[1], color[2], static_cast<unsigned char>(double(alpha)));
}

int* ImpBrush::getGradient(const Point source) {//Gaussian filter
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte pixel1[3];
	GLubyte pixel2[3];
	GLubyte pixel3[3];
	GLubyte pixel4[3];
	GLubyte pixel5[3];
	GLubyte pixel6[3];
	GLubyte pixel7[3];
	GLubyte pixel8[3];
	GLubyte pixel9[3];

	memcpy(pixel1, pDoc->GetOriginalPixel(source.x - 1, source.y - 1), 3);
	memcpy(pixel2, pDoc->GetOriginalPixel(source.x, source.y - 1), 3);
	memcpy(pixel3, pDoc->GetOriginalPixel(source.x + 1, source.y - 1), 3);
	memcpy(pixel4, pDoc->GetOriginalPixel(source.x - 1, source.y), 3);
	memcpy(pixel5, pDoc->GetOriginalPixel(source.x, source.y), 3);
	memcpy(pixel6, pDoc->GetOriginalPixel(source.x + 1, source.y), 3);
	memcpy(pixel7, pDoc->GetOriginalPixel(source.x - 1, source.y + 1), 3);
	memcpy(pixel8, pDoc->GetOriginalPixel(source.x, source.y + 1), 3);
	memcpy(pixel9, pDoc->GetOriginalPixel(source.x + 1, source.y + 1), 3);

	double grayScale1 = pixel1[0] * 0.299 + pixel1[1] * 0.587 + pixel1[2] * 0.144;
	double grayScale2 = pixel2[0] * 0.299 + pixel2[1] * 0.587 + pixel2[2] * 0.144;
	double grayScale3 = pixel3[0] * 0.299 + pixel3[1] * 0.587 + pixel3[2] * 0.144;
	double grayScale4 = pixel4[0] * 0.299 + pixel4[1] * 0.587 + pixel4[2] * 0.144;
	double grayScale5 = pixel5[0] * 0.299 + pixel5[1] * 0.587 + pixel5[2] * 0.144;
	double grayScale6 = pixel6[0] * 0.299 + pixel6[1] * 0.587 + pixel6[2] * 0.144;
	double grayScale7 = pixel7[0] * 0.299 + pixel7[1] * 0.587 + pixel7[2] * 0.144;
	double grayScale8 = pixel8[0] * 0.299 + pixel8[1] * 0.587 + pixel8[2] * 0.144;
	double grayScale9 = pixel9[0] * 0.299 + pixel9[1] * 0.587 + pixel9[2] * 0.144;

	int dx = -1 * grayScale1 + grayScale3 - 2 * grayScale4 + 2 * grayScale6 - grayScale7 + grayScale9;
	int dy = -1 * grayScale1 - 2 * grayScale2 - grayScale3 + grayScale7 + 2 * grayScale8 + grayScale9;

	int* temp = new int[2];
	temp[0] = dx;
	temp[1] = dy;
	return temp;
}