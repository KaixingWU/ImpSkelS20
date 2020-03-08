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

	glBegin(GL_TRIANGLES);
	SetColor(source);

	glVertex2d(target.x, target.y);

	glEnd();
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

    circleVertex = new float[VERTEX_DATA_NUM * 2 + 4];
    radian = (float)(2 * M_PI / VERTEX_DATA_NUM);
    float radius = size / 2;

    circleVertex[0] = target.x;
    circleVertex[1] = target.y;

    for (int i = 0; i < VERTEX_DATA_NUM; i++) {
        circleVertex[2 * i + 2] = (float)(target.x + radius * cos(radian * i));
        circleVertex[2 * i + 1 + 2] = (float)(target.y + radius * sin(radian * i));
    }

    circleVertex[VERTEX_DATA_NUM * 2 + 2] = (float)(target.x + radius * cos(radian));
    circleVertex[VERTEX_DATA_NUM * 2 + 3] = (float)(target.y + radius * sin(radian));

	glBegin(GL_TRIANGLE_FAN);
    glDrawArrays(GL_TRIANGLE_FAN, 0, VERTEX_DATA_NUM + 2);
    glEnd();
}

