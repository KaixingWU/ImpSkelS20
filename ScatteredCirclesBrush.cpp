#include "ScatteredCirclesBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

extern float frand();

ScatteredCirclesBrush::ScatteredCirclesBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name)
{
}


void ScatteredCirclesBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();



	//glPointSize((float)size);


	BrushMove(source, target);
}

void ScatteredCirclesBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POLYGON);
	SetColor(source);
	glVertex2i(target.x, target.y);
	glVertex2i(target.x+1, target.y+1);
	glVertex2i(target.x-1, target.y+0.5);

	glEnd();
}

void ScatteredCirclesBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}
