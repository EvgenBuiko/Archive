#pragma once
#include "PObject.h"

class PTriangle : public PObject
{
public:
	PTriangle(CPoint lt, CPoint rb);
	void OnDraw(CDC* pDC);
	~PTriangle();
};

