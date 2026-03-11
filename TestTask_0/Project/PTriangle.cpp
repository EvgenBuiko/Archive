#include "stdafx.h"
#include "PTriangle.h"


PTriangle::PTriangle(CPoint lt, CPoint rb) : PObject(lt, rb) { type = ID_Triangle; }

void PTriangle::OnDraw(CDC* pDC)
{
	POINT points[3] = { CPoint(lt.x + (rb.x - lt.x) / 2, lt.y),
		CPoint(rb.x, rb.y), CPoint(lt.x, rb.y) };
	pDC->Polygon(points, 3);
}

PTriangle::~PTriangle() {}
