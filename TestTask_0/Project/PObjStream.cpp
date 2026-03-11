#include "stdafx.h"
#include "ProjectDoc.h"
#include "ProjectView.h"
#include "PObjStream.h"
#include "PConnecter.h"
#include <fstream>
void PObjStream::Write(CString path, std::vector<PObject*>& objs)
{
	if (!path)
		return;
	std::ofstream fout(path);
	for (PObject* item : objs)
		if (item)
			fout << "o " << item->GetLeftTop().x << ' ' << item->GetLeftTop().y
			<< ' ' << item->GetRightBottom().x << ' ' << item->GetRightBottom().y << ' ' << item->GetType() << '\n';
	fout.close();
}
void PObjStream::Read(CString path, std::vector<PObject*>& objs, std::vector<PToolComponent*>& tls)
{
	char buf[255], file[1024];
	memset(buf, 0, sizeof(buf));
	memset(file, 0, sizeof(file));
	if (!path)
		return;
	std::ifstream fin(path);
	while (!fin.eof())
	{
		fin >> buf;
		if (strcmp(buf, "o") != 0 && strcmp(buf, "") != 0)
		{
			objs.clear();
			tls.clear();
			return;
		}
		else
		{
			if (strcmp(buf, "") == 0)
				break;
			short type;
			CPoint lt, rb;
			fin >> lt.x >> lt.y >> rb.x >> rb.y >> type;
			objs.push_back(PObject::CreateObject((ObjectType)type, lt, rb)); 
			if (type == ID_Line)
			{
				PConnecter* buf = new PConnecter();
				buf->InitLine((PLine*)objs.back());
				buf->InitObjA(CProjectView::Find(lt, objs));
				buf->InitObjB(CProjectView::Find(rb, objs));
				tls.push_back(buf);
				buf = nullptr;
			}
		}
	}
	fin.close();
}
