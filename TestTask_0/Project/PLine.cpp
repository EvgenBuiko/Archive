#include "stdafx.h"
#include "PLine.h"

PLine::PLine(CPoint lt, CPoint rb) : PObject(lt, rb) { type = ID_Line; }
void PLine::OnDraw(CDC* pDC)
{
	POINT points[2] = { lt, rb };
	pDC->Polyline(points, 2);
}
PLine::~PLine() {}
