#include "stdafx.h"
#include "PObject.h"
#include "PTriangle.h"
#include "PRectangle.h"
#include "PEllipse.h"
#include "PLine.h"

PObject::PObject() : lt(0, 0), rb(0, 0) {}
PObject::PObject(CPoint lt, CPoint rb) 
{
	this->lt = lt;
	this->rb = rb;
}
PObject::PObject(PObject& copy)
{
	this->lt = copy.lt;
	this->rb = copy.rb;
}
PObject* PObject::CreateObject(ObjectType type, CPoint lt, CPoint rb)
{
	switch (type)
	{
	case ID_Triangle:
		return new PTriangle(lt, rb);
	case ID_Rectangle:
		return new PRectangle(lt, rb);
	case ID_Ellipse:
		return new PEllipse(lt, rb);
	case ID_Line:
		return new PLine(lt, rb);
	default:
		return nullptr;
	}
}
CPoint PObject::GetLeftTop() const { return CPoint(lt); }
CPoint PObject::GetRightBottom() const { return CPoint(rb); }
void PObject::SetLeftTop(CPoint new_lt) { lt = new_lt; }
void PObject::SetRightBottom(CPoint new_rb) { rb = new_rb; }
CPoint PObject::GetCenter() const { return CPoint((lt.x + rb.x) / 2, (lt.y + rb.y) / 2); }
ObjectType PObject::GetType() const { return type; }
PObject::~PObject() { }
