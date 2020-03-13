#include "StarBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "cmath"


extern float frand();

StarBrush::StarBrush(ImpressionistDoc* pDoc, char* name) :
    ImpBrush(pDoc, name)
{
}

void StarBrush::BrushBegin(const Point source, const Point target, int DirectionType)
{
    ImpressionistDoc* pDoc = GetDocument();
    ImpressionistUI* dlg = pDoc->m_pUI;

    int size = pDoc->getSize();


    BrushMove(source, target, DirectionType);
}

void StarBrush::BrushMove(const Point source, const Point target, int DirectionType)
{
    ImpressionistDoc* pDoc = GetDocument();
    ImpressionistUI* dlg = pDoc->m_pUI;

    if (pDoc == NULL) {
        printf("StarBrush::BrushMove  document is NULL\n");
        return;
    }

    DrawStar(source, target);
}

void StarBrush::BrushEnd(const Point source, const Point target)
{
    // do nothing so far
}
void StarBrush::DrawStar(const Point source, const Point target)
{
    ImpressionistDoc* pDoc = GetDocument();
    ImpressionistUI* dlg = pDoc->m_pUI;
    double size = pDoc->getSize();

    Blend();

    //glBegin(GL_TRIANGLES);
        /*glVertex2f(target.x,target.y+size/2);//output vertex
        glVertex2f(target.x-size*sqrt(3)/4,target.y-size/4);
        glVertex2f(target.x+size*sqrt(3)/4,target.y-size/4);
        glVertex2f(target.x,target.y-size/2);
        glVertex2f(target.x+size*sqrt(3)/4,target.y+size/4);
        glVertex2f(target.x+size*sqrt(3)/4,target.y +size/4);*/
        double L1 = size/2 * cos(36 * M_PI / 180);
        double L2 = size / 2 * sin(36 * M_PI / 180);
        double L3 = size / 2 * cos(72 * M_PI / 180);
        double L4 = size / 2 * sin(72 * M_PI / 180);
        double L5 = L2 * tan(72 * M_PI / 180);
        double L6 = L2 / cos(72 * M_PI / 180);
        double L7 = L6 * sin(54 * M_PI / 180);
        double L8 = L6 * cos(54 * M_PI / 180) + size / 2;

        glBegin(GL_POLYGON);

        SetColor(source);
        glVertex2f(target.x, target.y);
        glVertex2f(target.x, L5 + L1+ target.y);
        glVertex2f(L2+ target.x, L1 + target.y);
        glVertex2f(L2 + L6+target.x, L1 + target.y);
        glVertex2f(L4 + target.x, -L3 + target.y);
        glVertex2f(L7 + target.x, -L8 + target.y);
        glVertex2f(target.x, -size/2+target.y);
        glVertex2f(-L7 + target.x, -L8 + target.y);
        glVertex2f(-L4 + target.x, -L3 + target.y);
        glVertex2f(-L2 - L6 + target.x, L1 + target.y);
        glVertex2f(-L2 + target.x, L1 + target.y);
        glVertex2f(target.x, L5 + L1 + target.y);
        glEnd();

        glFlush();

}

