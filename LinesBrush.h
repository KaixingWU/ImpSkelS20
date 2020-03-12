#pragma once


#ifndef LINESBRUSH_H
#define LINESBRUSH_H

#include "ImpBrush.h"


class LinesBrush : public ImpBrush
{
public:
	LinesBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target, int DirectionType=-1);
	void BrushMove(const Point source, const Point targe, int DirectionType=-1);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	void DirectionBrush(const Point source, const Point target);

};

#endif

