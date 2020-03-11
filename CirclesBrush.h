#pragma once

#ifndef CIRCLESBRUSH_H
#define CIRCLESBRUSH_H

#include "ImpBrush.h"

static int VERTEX_DATA_NUM = 360;
class CirclesBrush : public ImpBrush
{
public:
	CirclesBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target,int DirectionType);
	void BrushMove(const Point source, const Point target, int DirectionType);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	void DrawCircle(const Point source, const Point target);
	float* circleVertex;
	float radian;
	float radius;
};


#endif

