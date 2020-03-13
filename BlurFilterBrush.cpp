#include "BlurFilterBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "cmath"

extern float frand();

BlurFilterBrush::BlurFilterBrush(ImpressionistDoc* pDoc, char* name) :
    ImpBrush(pDoc, name)
{
}

void BlurFilterBrush::BrushBegin(const Point source, const Point target, int DirectionType)
{
    ImpressionistDoc* pDoc = GetDocument();
    ImpressionistUI* dlg = pDoc->m_pUI;

    int size = pDoc->getSize();

    glPointSize((float)size);

    BrushMove(source, target, DirectionType);
}

void BlurFilterBrush::BrushMove(const Point source, const Point target, int DirectionType)
{
    ImpressionistDoc* pDoc = GetDocument();
    ImpressionistUI* dlg = pDoc->m_pUI;

    if (pDoc == NULL) {
        printf("BlurFilterBrush::BrushMove  document is NULL\n");
        return;
    }

    Blend();
    glBegin(GL_POINTS);
    SetColor(source);

    glVertex2d(target.x, target.y);

    glEnd();
    //DrawStar(source, target);
}

void BlurFilterBrush::BrushEnd(const Point source, const Point target)
{
    // do nothing so far
}


void BlurFilterBrush::SetColor(const Point source)
{
    ImpressionistDoc* pDoc = GetDocument();
    double alpha = pDoc->getAlpha();
    GLubyte pixel1[3];
    GLubyte pixel2[3];
    GLubyte pixel3[3];
    GLubyte pixel4[3];
    GLubyte pixel5[3];
    GLubyte pixel6[3];
    GLubyte pixel7[3];
    GLubyte pixel8[3];
    GLubyte pixel9[3];

    memcpy(pixel1, pDoc->GetOriginalPixel(source.x - 1, source.y - 1), 3);
    memcpy(pixel2, pDoc->GetOriginalPixel(source.x, source.y - 1), 3);
    memcpy(pixel3, pDoc->GetOriginalPixel(source.x + 1, source.y - 1), 3);
    memcpy(pixel4, pDoc->GetOriginalPixel(source.x - 1, source.y), 3);
    memcpy(pixel5, pDoc->GetOriginalPixel(source.x, source.y), 3);
    memcpy(pixel6, pDoc->GetOriginalPixel(source.x + 1, source.y), 3);
    memcpy(pixel7, pDoc->GetOriginalPixel(source.x - 1, source.y + 1), 3);
    memcpy(pixel8, pDoc->GetOriginalPixel(source.x, source.y + 1), 3);
    memcpy(pixel9, pDoc->GetOriginalPixel(source.x + 1, source.y + 1), 3);

    GLubyte color[4];
    //color[0] =(pixel1[0]+ 2*pixel2[0] + pixel3[0] + 2*pixel4[0] + 4*pixel5[0] + 2*pixel6[0] + pixel7[0] + 2*pixel8[0] + pixel9[0])/16 ;
    //color[1] = (pixel1[1] + 2 * pixel2[1] + pixel3[1] + 2 * pixel4[1] + 4 * pixel5[1] + 2 * pixel6[1] + pixel7[1] + 2 * pixel8[1] + pixel9[1]) / 16;
    //color[2] = (pixel1[2] + 2 * pixel2[2] + pixel3[2] + 2 * pixel4[2] + 4 * pixel5[2] + 2 * pixel6[2] + pixel7[2] + 2 * pixel8[2] + pixel9[2]) / 16;
    color[0] =(pixel1[0]+ pixel2[0] + pixel3[0] + pixel4[0] + pixel5[0] + pixel6[0] + pixel7[0] + pixel8[0] + pixel9[0])/9 ;
    color[1] = (pixel1[1] + pixel2[1] + pixel3[1] + pixel4[1] + pixel5[1] + pixel6[1] + pixel7[1] + pixel8[1] + pixel9[1]) / 9;
    color[2] = (pixel1[2] + pixel2[2] + pixel3[2] + pixel4[2] +  pixel5[2] + pixel6[2] + pixel7[2] + pixel8[2] + pixel9[2]) / 9;
    double chosen_R = pDoc->getColorR();
    double chosen_G = pDoc->getColorG();
    double chosen_B = pDoc->getColorB();


    color[0] = (int)(color[0] * chosen_R);
    color[1] = (int)(color[1] * chosen_G);
    color[2] = (int)(color[2] * chosen_B);
    
    color[3] = alpha;
    
    glColor4ub(color[0], color[1], color[2], static_cast<unsigned char>(double(alpha)));

}

