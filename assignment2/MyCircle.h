#pragma once
#include <windef.h>
#include <atltypes.h>
class MyCircle
{
public:

	MyCircle(int radius, CPoint dxy, COLORREF color, CPoint point) {
		this->radius = radius;
		this->point = point;
		this->color = color;
		this->dxy = dxy;
	};

	int radius;
	CPoint dxy;
	COLORREF color;
	CPoint point;
};

