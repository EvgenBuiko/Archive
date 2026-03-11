#pragma once
#include "PObject.h"

class PMover
{
private:
	PObject* obj;
	bool b_active;
	CPoint start_loc;

public:
	PMover();
	void SetActive(bool val);
	bool GetActive() const;
	bool HaveObject() const;
	void InitMoving(PObject* obj, CPoint start_loc);
	void DetachObject();
	void UpdateLocation(CPoint new_loc);
	~PMover();
};

