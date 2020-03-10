#include "CirclesBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "cmath"


extern float frand();

CirclesBrush::CirclesBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CirclesBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();


	BrushMove(source, target);
}

void CirclesBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

    DrawCircle(source, target);
}

void CirclesBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}
void CirclesBrush::DrawCircle(const Point source, const Point target)
{
    ImpressionistDoc* pDoc = GetDocument();
    ImpressionistUI* dlg = pDoc->m_pUI;
    int size = pDoc->getSize();
    //double alpha = pDoc->getAlpha();

    circleVertex = new float[VERTEX_DATA_NUM * 2 + 4];
    radian = (float)(2 * M_PI / VERTEX_DATA_NUM);
    float radius = size / 2;

    circleVertex[0] = target.x;
    circleVertex[1] = target.y;

    for (int i = 0; i < VERTEX_DATA_NUM; i++) {
        circleVertex[2 * i + 2] = (GLfloat)(target.x + radius * cos(radian * i));
        circleVertex[2 * i + 1 + 2] = (GLfloat)(target.y + radius * sin(radian * i));
    }

    circleVertex[VERTEX_DATA_NUM * 2 + 2] = (GLfloat)(target.x + radius * cos(radian));
    circleVertex[VERTEX_DATA_NUM * 2 + 3] = (GLfloat)(target.y + radius * sin(radian));
	
    Blend();
    
    glBegin(GL_TRIANGLE_FAN);
   
    for (int k = 0; k < VERTEX_DATA_NUM+2; k++) 
    {
        SetColor(source);
        glVertex2f(circleVertex[2 * k], circleVertex[2 * k+1]);//output vertex
    }

    glEnd();
   
}

