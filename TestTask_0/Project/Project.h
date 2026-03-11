
// Project.h: основной файл заголовка для приложения Project
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы
#include "PMover.h"
#include "PEvent.h"
// CProjectApp:
// Сведения о реализации этого класса: Project.cpp
//

class CProjectApp : public CWinApp
{
public:
	CProjectApp() noexcept;
	int buf_obj_type;
	PMover move_tool;
	CString obj_pathname;
	PEvent<CString> on_open_file;
	PEvent<CString> on_save_file;
	PEvent<> on_close_file;
// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	afx_msg void OnAppAbout();
	afx_msg void CreateTriangle();
	afx_msg void CreateRectangle();
	afx_msg void CreateEllipse();
	afx_msg void MoveObject();
	afx_msg void CreateConnection();
	afx_msg void OpenFile();
	afx_msg void SaveFile();
	afx_msg void CloseFile();
	DECLARE_MESSAGE_MAP()
};

extern CProjectApp theApp;
