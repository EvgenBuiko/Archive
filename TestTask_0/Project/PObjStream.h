#pragma once
#include "stdafx.h"
#include <vector>
#include "Project.h"
#include "PObject.h"
namespace PObjStream
{
	void Write(CString path, std::vector<PObject*>& objs);
	void Read(CString path, std::vector<PObject*>& objs, std::vector<PToolComponent*>& tls);
};