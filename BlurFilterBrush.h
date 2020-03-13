#pragma once

#ifndef BLURFILTERBRUSH_H
#define  BLURFILTERBRUSH_H

#include "ImpBrush.h"
class BlurFilterBrush : public ImpBrush
{
	public:
		BlurFilterBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

		void BrushBegin(const Point source, const Point target, int DirectionType);
		void BrushMove(const Point source, const Point target, int DirectionType);
		void BrushEnd(const Point source, const Point target);
		char* BrushName(void);
		void SetColor(const Point source);
	
	};


#endif


