
// ProjectView.cpp: реализация класса CProjectView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Project.h"
#endif

#include "ProjectDoc.h"
#include "ProjectView.h"
#include "PLine.h"
#include "PConnecter.h"
#include "MethodEventHandler.h"
#include "PObjStream.h"
#define _CRT_SECURE_NO_WARNINGS
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProjectView

IMPLEMENT_DYNCREATE(CProjectView, CView)

BEGIN_MESSAGE_MAP(CProjectView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CProjectView


CProjectView::CProjectView() noexcept
{
	// TODO: добавьте код создания
	curr_obj = nullptr;
	curr_tool = nullptr;
	Objects.clear();
	Tools.clear();
	theApp.on_open_file += MY_METHOD_HANDLER(CProjectView::OpenFile);
	theApp.on_save_file += MY_METHOD_HANDLER(CProjectView::SaveFile);
	theApp.on_close_file += MY_METHOD_HANDLER(CProjectView::CloseFile);
}

CProjectView::~CProjectView()
{
	for (PObject* item : Objects)
		if (item)
			delete item;
	for (PToolComponent* item : Tools)
		if (item)
			delete item;
}

BOOL CProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

PObject * CProjectView::Find(CPoint loc, std::vector<PObject*>& objs)
{
	for (PObject* item : objs)
	{
		if (item->GetLeftTop().x <= loc.x && item->GetLeftTop().y <= loc.y &&
			item->GetRightBottom().x >= loc.x && item->GetRightBottom().y >= loc.y)
			return item;
		if (item->GetLeftTop().x <= loc.x && item->GetLeftTop().y >= loc.y &&
			item->GetRightBottom().x >= loc.x && item->GetRightBottom().y <= loc.y)
			return item;
		if (item->GetLeftTop().x >= loc.x && item->GetLeftTop().y >= loc.y &&
			item->GetRightBottom().x <= loc.x && item->GetRightBottom().y <= loc.y)
			return item;
		if (item->GetLeftTop().x >= loc.x && item->GetLeftTop().y <= loc.y &&
			item->GetRightBottom().x <= loc.x && item->GetRightBottom().y >= loc.y)
			return item;
	}
	return nullptr;
}

// Рисование CProjectView

void CProjectView::OnDraw(CDC* pDC)
{
	CPaintDC dc(this);
	CProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: добавьте здесь код отрисовки для собственных данных
	for (PObject *item : Objects)
		item->OnDraw(pDC);
	for (PToolComponent* item : Tools)
		item->Update();
	if (curr_obj)
	{
		curr_obj->OnDraw(pDC);
		InvalidateRect(0);
	}
	if (theApp.move_tool.HaveObject())
		InvalidateRect(0);
}


// Диагностика CProjectView

#ifdef _DEBUG
void CProjectView::AssertValid() const { CView::AssertValid(); }
void CProjectView::Dump(CDumpContext& dc) const { CView::Dump(dc); }
CProjectDoc* CProjectView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProjectDoc)));
	return (CProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CProjectView
void CProjectView::OnLButtonDown(UINT Flags, CPoint Location)
{
	if (theApp.buf_obj_type != -1 && theApp.buf_obj_type != ID_Line)
		curr_obj = PObject::CreateObject((ObjectType)theApp.buf_obj_type, Location, Location);
	else if (theApp.buf_obj_type == ID_Line)
	{
		PObject* founded = Find(Location, Objects);
		if (founded)
		{
			curr_obj = PObject::CreateObject(ID_Line, founded->GetCenter(), Location);
			curr_tool = new PConnecter();
			((PConnecter*)curr_tool)->InitLine((PLine*)curr_obj);
			((PConnecter*)curr_tool)->InitObjA(founded);
		}
	}
	if (theApp.move_tool.GetActive())
		theApp.move_tool.InitMoving(Find(Location, Objects), Location);
	InvalidateRect(0);
}

void CProjectView::OnLButtonUp(UINT Flags, CPoint Location)
{
	if (curr_obj != nullptr)
	{
		if (theApp.buf_obj_type == ID_Line)
		{
			PObject* founded = Find(Location, Objects);
			if (founded)
			{
				((PConnecter*)curr_tool)->InitObjB(founded);
				curr_obj->SetRightBottom(founded->GetCenter());
				Tools.push_back(curr_tool);
				Objects.push_back(curr_obj);
			}
			else
			{
				delete curr_obj;
				delete curr_tool;
			}
		}
		else
		{
			curr_obj->SetRightBottom(Location);
			Objects.push_back(curr_obj);
		}
	}
	curr_obj = nullptr;
	curr_tool = nullptr;
	theApp.move_tool.DetachObject();
	InvalidateRect(0);
}

void CProjectView::OnMouseMove(UINT Flags, CPoint Location)
{
	if (curr_obj)
		curr_obj->SetRightBottom(Location);
	if (theApp.move_tool.HaveObject())
		theApp.move_tool.UpdateLocation(Location);
}

void CProjectView::OpenFile(CString pathname)
{
	CloseFile();
	PObjStream::Read(pathname, Objects, Tools);
}

void CProjectView::SaveFile(CString pathname) { PObjStream::Write(pathname, Objects); }

void CProjectView::CloseFile()
{
	Objects.clear();
	Tools.clear();
	InvalidateRect(0);
}
