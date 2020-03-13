#pragma once


#ifndef STARBRUSH_H
#define STARBRUSH_H

#include "ImpBrush.h"

class StarBrush : public ImpBrush
{

	public:
		StarBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

		void BrushBegin(const Point source, const Point target, int DirectionType = -1);
		void BrushMove(const Point source, const Point targe, int DirectionType = -1);
		void BrushEnd(const Point source, const Point target);
		char* BrushName(void);
		void DrawStar(const Point source, const Point target);

};

#endif


