
// ProjectView.h: интерфейс класса CProjectView
//

#pragma once
#include <vector>
#include "PObject.h"
#include "PToolComponent.h"
#include <memory>

class CProjectView : public CView
{
	
protected: // создать только из сериализации
	CProjectView() noexcept;
	DECLARE_DYNCREATE(CProjectView)

// Атрибуты
public:
	CProjectDoc* GetDocument() const;
	std::vector<PObject*> Objects;
	std::vector<PToolComponent*> Tools;
	PToolComponent* curr_tool;
	PObject* curr_obj;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	static PObject* Find(CPoint loc, std::vector<PObject*>& objs);
	afx_msg void OnLButtonDown(UINT Flags, CPoint Location);
	afx_msg void OnLButtonUp(UINT Flags, CPoint Location);
	afx_msg void OnMouseMove(UINT Flags, CPoint Location);
	afx_msg void OpenFile(CString pathname);
	afx_msg void SaveFile(CString pathname);
	afx_msg void CloseFile();
	
protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в ProjectView.cpp
inline CProjectDoc* CProjectView::GetDocument() const
   { return reinterpret_cast<CProjectDoc*>(m_pDocument); }
#endif

