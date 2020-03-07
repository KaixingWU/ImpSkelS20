#pragma once

#ifndef CIRCLESBRUSH_H
#define CIRCLESBRUSH_H

#include "ImpBrush.h"
class CirclesBrush : public ImpBrush
{
public:
	CirclesBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

};


#endif

