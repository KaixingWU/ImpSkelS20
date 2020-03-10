#include "ScatteredCirclesBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "cmath"
#include <stdlib.h>
#include <time.h> 

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

    Blend();
    DrawScatteredCircle(source, target);
}

void ScatteredCirclesBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


void ScatteredCirclesBrush::DrawCircle(const Point source, const Point target)
{
    ImpressionistDoc* pDoc = GetDocument();
    ImpressionistUI* dlg = pDoc->m_pUI;
    int size = pDoc->getSize();

    circleVertex = new float[VERTEX_DATA_NUM1 * 2 + 4];
    radian = (float)(2 * M_PI / VERTEX_DATA_NUM1);
    float radius = size / 2;

    circleVertex[0] = target.x;
    circleVertex[1] = target.y;

    for (int i = 0; i < VERTEX_DATA_NUM1; i++) {
        circleVertex[2 * i + 2] = (GLfloat)(target.x + radius * cos(radian * i));
        circleVertex[2 * i + 1 + 2] = (GLfloat)(target.y + radius * sin(radian * i));
    }

    circleVertex[VERTEX_DATA_NUM1 * 2 + 2] = (GLfloat)(target.x + radius * cos(radian));
    circleVertex[VERTEX_DATA_NUM1 * 2 + 3] = (GLfloat)(target.y + radius * sin(radian));
    glBegin(GL_TRIANGLE_FAN);

    for (int k = 0; k < VERTEX_DATA_NUM1 + 2; k++)
    {
        SetColor(source);
        glVertex2f(circleVertex[2 * k], circleVertex[2 * k + 1]);//output vertex
    }

    glEnd();

}

void ScatteredCirclesBrush::DrawScatteredCircle(const Point source, const Point target)
{
    ImpressionistDoc* pDoc = GetDocument();
    ImpressionistUI* dlg = pDoc->m_pUI;
    double size = pDoc->getSize();

    srand((unsigned)time(NULL));
    for(int i=0;i<rand()%5+2;i++)
    {
        Point a((GLdouble)target.x + size/1.2*rand() / double(RAND_MAX), (GLdouble)target.y + size/1.2 * rand() / double(RAND_MAX));
        Point b((GLdouble)source.x + size/1.2*rand() / double(RAND_MAX), (GLdouble)source.y + size/1.2 * rand() / double(RAND_MAX));
       DrawCircle(a,b);
    }

}