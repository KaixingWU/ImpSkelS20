

#include "FilterCustomize.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

FilterCustomize::FilterCustomize(double* okernel, int w, int h):width(w),height(h)
{
	kernel = new double[w * h];
	memcpy(kernel, okernel, w * h * sizeof(double));
}

FilterCustomize::FilterCustomize()
{
	delete[] kernel;
}

double FilterCustomize::applyCustomizedFilter(GLubyte* Bitmap, int target_x, int target_y , int Width, int Height, int k)
{

	// Paint from left lower corner
	int startX = target_x - width / 2;
	int startY = target_y - height / 2;
	double value = 0.0;
	sum_weight = 0.0;
	for (int i = 0; i < width;i++) 
	{
		const int currentX = i + startX;
		if (currentX < 0 || currentX >= Width) continue;

		for(int j = 0; j < height;j++)
		{
			const int currentY = j + startY;
			if (currentY < 0 || currentY >= Height) continue;

			value += kernel[j * width + i] * (double)(Bitmap[(currentY * Width + currentX) * 3 + k]);
	
			sum_weight += kernel[j * width + i];
	

		}
	}
	if (sum_weight == 0) sum_weight = 1;
	if (sum_weight < 0) sum_weight = -sum_weight;

	return value/sum_weight;
}

