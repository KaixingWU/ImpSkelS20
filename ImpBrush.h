#ifndef IMPBRUSH_H
#define IMPBRUSH_H

//
// ImpBrush.h
//
// The header file of virtual brush. All the other brushes inherit from it.
//

#include <stdlib.h>

// Each brush type has an associated constant.
enum
{
	BRUSH_POINTS = 0,
	BRUSH_LINES,
	BRUSH_CIRCLES,
	BRUSH_SCATTERED_POINTS,
	BRUSH_SCATTERED_LINES,
	BRUSH_SCATTERED_CIRCLES,
	BRUSH_STAR,
	BRUSH_BLUR_FILTER,
	NUM_BRUSH_TYPE // Make sure this stays at the end!
};

enum
{
	SLIDER_RIGHT_MOUSE = 0,
	GRADIENT,
	BRUSH_DIRECTION,
	NUM_STROKE_TYPE
};


class ImpressionistDoc; // Pre-declaring class

static double pre_x = 0.0;
static double pre_y = 0.0;
static bool flag = true;

class Point 
{
public:
	Point() {};
	Point(int xx, int yy) { x = xx; y = yy; };

	int x, y;
};
/*
class Line
{
public:
	Line() {};
	Line(double xx, double yy, int an) { x = xx; y = yy; angle = an; };

	double x, y, angle;
};
*/
class ImpBrush 
{
protected:
	ImpBrush::ImpBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

public:
	// The implementation of your brush should realize these virtual functions
	virtual void BrushBegin( const Point source, const Point target , int DirectionType =-1) = 0;
	virtual void BrushMove( const Point source, const Point target , int DirectionType =-1) = 0;
	virtual void BrushEnd( const Point source, const Point target ) = 0;

	// according to the source image and the position, determine the draw color
	void SetColor( const Point source );
	void SetColor(const Point source, double alpha);

	void Blend();

	// get Doc to communicate with it
	ImpressionistDoc* GetDocument( void );

	// Return the name of the brush (not used in this version).
	char* BrushName( void );
	
	static int			c_nBrushCount;	// How many brushes we have,
	static ImpBrush**	c_pBrushes;		// and what they are.
	int* getGradient(const Point source);

private:
	ImpressionistDoc*	m_pDoc;

	// Brush's name (not used in this version).
	char*				m_pBrushName;
};

#endif