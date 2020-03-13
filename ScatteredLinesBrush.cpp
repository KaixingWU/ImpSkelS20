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
		printf("ScatteredLinesBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int lineAngle = pDoc->getLineAngle();

	int* temp = getGradient(source);
	//cout <<"out"<< DirectionType << endl;
	switch (DirectionType)
	{
		//cout << DirectionType << endl;
		case 0:
			size = pDoc->getSize();
			lineAngle = pDoc->getLineAngle();

			for (int i = 0; i < rand() % 3 + 2; i++)
			{
				Point a(source.x - 0.5 * size + (int)(frand() * size), source.y - 0.5 * size + (int)(frand() * size));
				//Point b(target.x - 0.5 * size + (int)(frand() * size), target.y - 0.5 * size + (int)(frand() * size));
				DrawOneLine(a, a);
			}
			break;
		case 1:// brush direction choice
		{
			size = pDoc->getSize();
			int dx = temp[0];
			int dy = temp[1];
			lineAngle = atan2(-dy, dx) * 180 / M_PI;
			if (lineAngle < 0)
				lineAngle += 360;

			for (int i = 0; i < rand() % 3 + 2; i++)
			{
				Point a(source.x - 0.5 * size + (int)(frand() * size), source.y - 0.5 * size + (int)(frand() * size));
				Point b(target.x - 0.5 * size + (int)(frand() * size), target.y - 0.5 * size + (int)(frand() * size));
				DrawOneLine(a, b);
			}
			delete[] temp;
			return;

		}break;
		case 2:
		{
			DirectionBrush(source, target);
		}break;

	}

	delete[] temp;
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
	for (int i = 0; i < rand() % 3 + 25; i++)
	{
		//Point a(source.x - 0.5 * size + (int)(frand() * size), source.y - 0.5 * size + (int)(frand() * size));

		int a = -0.5 * size + (int)(frand() * size);
		double cos_value = cos(atan(abs((target.y - pre_y) / (target.x - pre_x))));
		double sin_value = sin(atan(abs((target.y - pre_y) / (target.x - pre_x))));
		double x1 = source.x + size / 2 * cos_value + a;
		double y1 = source.y - size / 2 * sin_value + a;
		double x2 = source.x - size / 2 * cos_value + a;
		double y2 = source.y + size / 2 * sin_value + a;
		double x3 = source.x - size / 2 * cos_value - a;
		double y3 = source.y - size / 2 * sin_value + a;
		double x4 = source.x + size / 2 * cos_value - a;
		double y4 = source.y + size / 2 * sin_value + a;


		if (target.y - pre_y == 0)
		{
			glVertex2d(source.x - size / 2 + a, source.y + a);
			glVertex2d(source.x + size / 2 + a, source.y + a);
		}
		if (target.x - pre_x == 0)
		{
			glVertex2d(source.x + a, source.y - size / 2 + a);
			glVertex2d(source.x + a, source.y + size / 2 + a);
		}
		else if ((target.y - pre_y) / (target.x - pre_x) < 0)
		{
			glVertex2d(x1, y1);
			glVertex2d(x2, y2);
		}
		else if ((target.y - pre_y) / (target.x - pre_x) > 0)
		{
			glVertex2d(x3, y3);
			glVertex2d(x4, y4);
		}

		pre_x = target.x;
		pre_y = target.y;
		glEnd();
	}
}