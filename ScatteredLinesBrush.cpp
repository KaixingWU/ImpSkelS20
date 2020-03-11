#include "ScatteredLinesBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <cmath>
#include <iostream>
using namespace std;


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
	//cout <<"out"<< DirectionType << endl;
	switch (DirectionType)
	{
		//cout << DirectionType << endl;
		case 0:
			for (int i = 0; i < rand() % 3 + 2; i++)
			{
				Point a(source.x - 0.5 * size + (int)(frand() * size), source.y - 0.5 * size + (int)(frand() * size));
				//Point b(target.x - 0.5 * size + (int)(frand() * size), target.y - 0.5 * size + (int)(frand() * size));
				DrawOneLine(a, a);
			}
			break;
		case 1:// brush direction choice
		{
		}break;
		case 2:
		{
			DirectionBrush(source, target);
		}break;

	}
}

void ScatteredLinesBrush::DrawOneLine(const Point source, const Point target)
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

	
	glVertex2d(source.x - size / 2 * cos(lineAngle * M_PI / 180), source.y - size / 2 * sin(lineAngle * M_PI / 180));
	glVertex2d(target.x + size / 2 * cos(lineAngle * M_PI / 180), target.y + size / 2 * sin(lineAngle * M_PI / 180));
	
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

	glBegin(GL_LINES);
	while (flag)
	{
		pre_x = target.x;
		pre_y = target.y;
		flag = false;
		glVertex2d(source.x - size / 2, source.y);
		glVertex2d(source.x + size / 2, source.y);
	}

	SetColor(source);
	for (int i = 0; i < rand() % 3 + 3; i++)
	{
		//Point a(source.x - 0.5 * size + (int)(frand() * size), source.y - 0.5 * size + (int)(frand() * size));

		int a = -0.5 * size + (int)(frand() * size);

		if ((target.y - pre_y != 0) && (target.x - pre_x != 0))
		{
			glVertex2d(source.x - size / 2 * (cos(atan(abs((target.x - pre_x) / (target.y - pre_y))))) - 0.5 * size + (int)(frand() * size) + a, source.y - size / 2 * (sin(atan(abs((target.x - pre_x) / (target.y - pre_y))))) + a);
			glVertex2d(source.x + size / 2 * (cos(atan(abs((target.x - pre_x) / (target.y - pre_y))))) - 0.5 * size + (int)(frand() * size) + a, source.y + size / 2 * (sin(atan(abs((target.x - pre_x) / (target.y - pre_y))))) + a);
		}
		else if (target.y - pre_y == 0)
		{
			glVertex2d(source.x - size / 2 + a, source.y + a);
			glVertex2d(source.x + size / 2 + a, source.y + a);
		}
		else if (target.x - pre_x == 0)
		{
			glVertex2d(source.x + a, source.y - size / 2 + a);
			glVertex2d(source.x + a, source.y + size / 2 + a);
		}

		pre_x = target.x;
		pre_y = target.y;
		glEnd();
	}
}