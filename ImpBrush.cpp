//
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
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
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
void ImpBrush::SetColor (const Point source)
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
	double choose_R = pDoc->getColorR();
	double choose_G = pDoc->getColorG();
	double choose_B = pDoc->getColorB();


	color[0] = (int)(color[0] * choose_R);
	color[1] = (int)(color[1] * choose_G);
	color[2] = (int)(color[2] * choose_B);

	color[3] = alpha;
	//glColor4ubv(color);
	//cout << alpha << endl;
	glColor4ub(color[0], color[1], color[2], static_cast<unsigned char>(double(alpha)));
}
