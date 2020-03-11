#include "ScatteredPointsBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"


extern float frand();

ScatteredPointsBrush::ScatteredPointsBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredPointsBrush::BrushBegin(const Point source, const Point target, int DirectionType)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize(1.0);
	
	BrushMove(source, target,DirectionType);
}

void ScatteredPointsBrush::BrushMove(const Point source, const Point target, int DirectionType)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	Blend();
	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int radio = (int)((0.7 + 1 / 5 * frand()) * size); //by row and column
	int end = radio * radio;
	for (int i = 0; i < end; i++) {

		Point a(source.x - 0.5 * size + (int)(frand() * size), source.y - 0.5 * size + (int)(frand() * size));
		Point b(target.x - 0.5 * size + (int)(frand() * size), target.y - 0.5 * size + (int)(frand() * size));
		DrawOnePoint(a,b);

	}
	
}

void ScatteredPointsBrush::DrawOnePoint(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}
	glPointSize(1.0);

	Blend();
	glBegin(GL_POINTS);
	SetColor(target);

	glVertex2d(target.x, target.y);

	glEnd();
}

void ScatteredPointsBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

