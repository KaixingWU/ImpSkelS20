#include "ScatteredLinesBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <cmath>


extern float frand();

ScatteredLinesBrush::ScatteredLinesBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredLinesBrush::BrushBegin(const Point source, const Point target, int DirectionType)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	//int size = pDoc->getSize();
	int lineWidth = pDoc->getLineWidth();
	//int lineAngle = pDoc->getLineAngle();


	glLineWidth((float)lineWidth);

	BrushMove(source, target, DirectionType);
}

void ScatteredLinesBrush::BrushMove(const Point source, const Point target, int DirectionType)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int lineAngle = pDoc->getLineAngle();

	for (int i = 0; i < rand() % 3 + 2; i++) {
		Point a(source.x - 0.5 * size + (int)(frand() * size), source.y - 0.5 * size + (int)(frand() * size));
		//Point b(target.x - 0.5 * size + (int)(frand() * size), target.y - 0.5 * size + (int)(frand() * size));
		DrawOneLine(a, a, DirectionType);
	}
}

void ScatteredLinesBrush::DrawOneLine(const Point source, const Point target, int DirectionType)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int lineAngle = pDoc->getLineAngle();

	Blend();

	glBegin(GL_LINES);
	SetColor(source);

	if (DirectionType == 2) // brush direction choice
	{
		DirectionBrush(source, target);
	}
	else 
	{
	glVertex2d(source.x - size / 2 * cos(lineAngle * M_PI / 180), source.y - size / 2 * sin(lineAngle * M_PI / 180));
	glVertex2d(target.x + size / 2 * cos(lineAngle * M_PI / 180), target.y + size / 2 * sin(lineAngle * M_PI / 180));
	}
	glEnd();
}

void ScatteredLinesBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void ScatteredLinesBrush::DirectionBrush(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int lineAngle = pDoc->getLineAngle();


	while (flag)
	{
		pre_x = target.x;
		pre_y = target.y;
		flag = false;
		glVertex2d(source.x, source.y);
	}
	glBegin(GL_LINES);
	SetColor(source);
	if ((target.y - pre_y != 0) && (target.x - pre_x != 0))
	{
		glVertex2d(source.x - size / 2 * (cos(atan(abs((target.x - pre_x) / (target.y - pre_y))))), source.y - size / 2 * (sin(atan(abs((target.x - pre_x) / (target.y - pre_y))))));
		glVertex2d(source.x + size / 2 * (cos(atan(abs((target.x - pre_x) / (target.y - pre_y))))), source.y + size / 2 * (sin(atan(abs((target.x - pre_x) / (target.y - pre_y))))));
	}
	else if (target.y - pre_y == 0)
	{
		glVertex2d(source.x - size / 2, source.y);
		glVertex2d(source.x + size / 2, source.y);
	}
	else if (target.x - pre_x == 0)
	{
		glVertex2d(source.x, source.y - size / 2);
		glVertex2d(source.x, source.y + size / 2);
	}

	pre_x = target.x;
	pre_y = target.y;
	glEnd();
}