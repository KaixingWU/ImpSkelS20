#pragma once
#ifndef SCATTEREDLINESBRUSH_H
#define SCATTEREDLINESBRUSH_H

#include "ImpBrush.h"
class ScatteredLinesBrush : public ImpBrush
{
public:
	ScatteredLinesBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target, int DirectionType);
	void BrushMove(const Point source, const Point target, int DirectionType);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	void DrawOneLine(const Point source, const Point target);
	void DirectionBrush(const Point source, const Point target);
};
#endif

