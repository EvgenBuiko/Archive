#include "stdafx.h"
#include "PConnecter.h"

PConnecter::PConnecter() {}
void PConnecter::InitObjA(PObject * obj_A) { this->obj_A = obj_A; }
void PConnecter::InitObjB(PObject * obj_B) { this->obj_B = obj_B; }
void PConnecter::InitLine(PLine * line) { this->line = line; }
void PConnecter::Update()
{
	if (!obj_A || !obj_B || !line)
		return;
	line->SetLeftTop(obj_A->GetCenter());
	line->SetRightBottom(obj_B->GetCenter());
}

PConnecter::~PConnecter()
{
}
