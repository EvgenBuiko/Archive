#pragma once
#include "PObject.h"

class PRectangle : public PObject
{
public:
	PRectangle(CPoint lt, CPoint rb);
	void OnDraw(CDC* pDC);
	~PRectangle();
};

