#pragma once
#include "PToolComponent.h"
#include "PLine.h"

class PConnecter : public PToolComponent
{
private:
	PLine* line;
	PObject* obj_A;
	PObject* obj_B;
	
public:
	PConnecter();
	void InitObjA(PObject* obj_A);
	void InitObjB(PObject* obj_B);
	void InitLine(PLine* line);
	void Update();
	~PConnecter();
};

