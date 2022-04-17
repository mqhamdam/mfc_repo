#pragma once
#include <atltypes.h>

class CustomEllipse
{
public:
	CustomEllipse(CPoint pt, int r) {
		point = pt;
		radius = r;
	}
	CPoint point;
	int radius;
};

