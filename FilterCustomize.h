#pragma once

#ifndef FILTER_CUSTOM_H
#define FILTER_CUSTOM_H

#include "impressionistDoc.h"
#include "impressionistUI.h"

class FilterCustomize
{
public:
	FilterCustomize(double* okernel, int w, int h);
	FilterCustomize();

	double applyCustomizedFilter(GLubyte* Bitmap, int target_x, int target_y, int Width, int Height, int k);

	
	double* kernel;
	int width;
	int height;
	double sum_weight;
};

#endif

