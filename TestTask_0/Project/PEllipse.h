#pragma once
#include "PObject.h"

class PEllipse : public PObject 
{
private:
public:
	PEllipse(CPoint lt, CPoint rb);
	void OnDraw(CDC* pDC);
	~PEllipse();
};

