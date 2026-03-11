#include "stdafx.h"
#include "PMover.h"


PMover::PMover() : b_active(false), start_loc(0, 0) { obj = nullptr; }
void PMover::SetActive(bool val) 
{ 
	b_active = val;
	if (!b_active)
	{
		obj = nullptr;
		start_loc = CPoint(0, 0);
	}
}
bool PMover::GetActive() const { return b_active; }
bool PMover::HaveObject() const { return (obj != nullptr); }
void PMover::InitMoving(PObject * obj, CPoint start_loc)
{
	if (!b_active)
		return;
	this->obj = obj;
	this->start_loc = start_loc;
}
void PMover::DetachObject()
{
	obj = nullptr;
	start_loc = CPoint(0, 0);
}
void PMover::UpdateLocation(CPoint new_loc)
{
	if (!obj || !b_active)
		return;
	CPoint offset = new_loc - start_loc;
	obj->SetLeftTop(obj->GetLeftTop() + offset);
	obj->SetRightBottom(obj->GetRightBottom() + offset);
	start_loc = new_loc;
}
PMover::~PMover() {}
