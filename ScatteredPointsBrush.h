#pragma once
#ifndef SCATTEREDPOINTSBRUSH_H
#define SCATTEREDPOINTSBRUSH_H

#include "ImpBrush.h"
class ScatteredPointsBrush : public ImpBrush
{
public:
	ScatteredPointsBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target, int DirectionType);
	void BrushMove(const Point source, const Point target, int DirectionType);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	void DrawOnePoint(const Point source, const Point target);

};
#endif


