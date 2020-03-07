#include "LinesBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <cmath>


extern float frand();

LinesBrush::LinesBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LinesBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	int lineWidth = pDoc->getLineWidth();
	int lineAngle = pDoc->getLineAngle();

	glLineWidth((float)lineWidth);
	//glRotatef(lineAngle, 0.0, 0.0, 1.0);

	BrushMove(source, target);
}

void LinesBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int lineAngle = pDoc->getLineAngle();

	glBegin(GL_LINES);
		SetColor(source);
		glVertex2d(source.x - size/2 * cos(lineAngle * M_PI / 180), source.y - size/2 * sin(lineAngle * M_PI / 180));
		glVertex2d(target.x + size/2 * cos(lineAngle * M_PI / 180), target.y + size/2 * sin(lineAngle * M_PI / 180));

	glEnd();
}

void LinesBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

