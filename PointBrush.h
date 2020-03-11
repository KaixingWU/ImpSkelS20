//
// PointBrush.h
//
// The header file for Point Brush. 
//

#ifndef POINTBRUSH_H
#define POINTBRUSH_H

#include "ImpBrush.h"

class PointBrush : public ImpBrush
{
public:
	PointBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target, int DirectionType);
	void BrushMove( const Point source, const Point target, int DirectionType);
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif