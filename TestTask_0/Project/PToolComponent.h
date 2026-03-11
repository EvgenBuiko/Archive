#pragma once

class PToolComponent
{
public:
	PToolComponent();
	virtual void Update() = 0;
	virtual ~PToolComponent();
};