#pragma once
#include "PObject.h"

class PLine : public PObject
{
public:
	PLine(CPoint lt, CPoint rb);
	void OnDraw(CDC* pDC);
	~PLine();
};

