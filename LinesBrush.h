#pragma once


#ifndef LINESBRUSH_H
#define LINESBRUSH_H

#include "ImpBrush.h"

class LinesBrush : public ImpBrush
{
public:
	LinesBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

};

#endif

