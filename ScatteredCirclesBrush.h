#pragma once

#ifndef SCATTEREDCIRCLESBRUSH_H
#define SCATTEREDCIRCLESBRUSH_H

#include "ImpBrush.h"
static int VERTEX_DATA_NUM1 = 360;
class ScatteredCirclesBrush : public ImpBrush
{
public:
	ScatteredCirclesBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	void DrawScatteredCircle(const Point source, const Point target);
	void DrawCircle(const Point source, const Point target);
	float* circleVertex;
	float radian;
	float radius;


};

#endif
