#include "Geometry.h"

bool PointInFigure(int n, int* arrX, int* arrY, int x, int y)
{
	int *lineX = new int[2];
	int *lineY = new int[2];
	lineX[0] = x;
	lineX[1] = x + 1000;
	lineY[0] = y;
	lineY[1] = y;
	int numberOfCrossing = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == n - 1)
		{
			int* finalX = new int[2];
			int* finalY = new int[2];
			finalX[0] = arrX[n - 1];
			finalX[1] = arrX[0];
			finalY[0] = arrY[n - 1];
			finalY[1] = arrY[0];
			if (SegmentsCrossing(lineX, lineY, finalX, finalY))
				++numberOfCrossing;
		}
		else
		{
			if (SegmentsCrossing(lineX, lineY, arrX + i, arrY + i))
				++numberOfCrossing;
		}
		
	}
	if (numberOfCrossing != 1)
		return false;
	return true;
}

double Angle(double k1, double k2)
{
	double tg = (k1 - k2) / (1 + k1 * k2);
	double ang = atan(tg);
	return ang;
}

int sign(double a)
{
	if (a > 0)
		return 1;
	else
		if (a == 0)
			return 0;
		else
			return -1;
}

bool SegmentsCrossing(int *x1, int *y1, int *x2, int *y2)
{
	int x11,x12,y11,y12;
	x11 = x1[0];
	x12 = x1[1];
	y11 = y1[0];
	y12 = y1[1];
	int x21, x22, y21, y22;
	x21 = x2[0];
	x22 = x2[1];
	y21 = y2[0];
	y22 = y2[1];
	int v12, v11, v21, v22;
	v11 = (x1[1] - x1[0]) * (y2[0] - y1[0]) - (y1[1] - y1[0]) * (x2[0] - x1[0]);
	v12 = (x1[1] - x1[0]) * (y2[1] - y1[0]) - (y1[1] - y1[0]) * (x2[1] - x1[0]);
	v21 = (x2[1] - x2[0]) * (y1[0] - y2[0]) - (y2[1] - y2[0]) * (x1[0] - x2[0]);
	v22 = (x2[1] - x2[0]) * (y1[1] - y2[0]) - (y2[1] - y2[0]) * (x1[1] - x2[0]);
	if (sign(v11) == sign(v12))
 		return false;
	if (sign(v21) == sign(v22))
		return false;
	return true;
}