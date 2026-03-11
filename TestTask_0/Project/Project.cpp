
// Project.cpp: определяет поведение классов для приложения.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Project.h"
#include "MainFrm.h"

#include "ProjectDoc.h"
#include "ProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProjectApp

BEGIN_MESSAGE_MAP(CProjectApp, CWinApp)
	ON_COMMAND(ID_TRIANGLE, &CProjectApp::CreateTriangle)
	ON_COMMAND(ID_RECTANGLE, &CProjectApp::CreateRectangle)
	ON_COMMAND(ID_ELLIPSE, &CProjectApp::CreateEllipse)
	ON_COMMAND(ID_MOVE, &CProjectApp::MoveObject)
	ON_COMMAND(ID_CONNECT, &CProjectApp::CreateConnection)
	ON_COMMAND(ID_OPEN_FILE, &CProjectApp::OpenFile)
	ON_COMMAND(ID_SAVE_FILE, &CProjectApp::SaveFile)
	ON_COMMAND(ID_CLOSE_FILE, &CProjectApp::CloseFile)
END_MESSAGE_MAP()


// Создание CProjectApp

CProjectApp::CProjectApp() noexcept
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Если приложение построено с поддержкой среды Common Language Runtime (/clr):
	//     1) Этот дополнительный параметр требуется для правильной поддержки работы диспетчера перезагрузки.
	//   2) В своем проекте для сборки необходимо добавить ссылку на System.Windows.Forms.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: замените ниже строку идентификатора приложения строкой уникального идентификатора; рекомендуемый
	// формат для строки: ИмяКомпании.ИмяПродукта.СубПродукт.СведенияОВерсии
	SetAppID(_T("Project.AppID.NoVersion"));

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
	obj_pathname = CString("null");
}

// Единственный объект CProjectApp

CProjectApp theApp;


// Инициализация CProjectApp

BOOL CProjectApp::InitInstance()
{
	// InitCommonControlsEx() требуются для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// Для использования элемента управления RichEdit требуется метод AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующего
	// конкретные процедуры инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));
	LoadStdProfileSettings(4);  // Загрузите стандартные параметры INI-файла (включая MRU)


	// Зарегистрируйте шаблоны документов приложения.  Шаблоны документов
	//  выступают в роли посредника между документами, окнами рамок и представлениями
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CProjectDoc),
		RUNTIME_CLASS(CMainFrame),       // основное окно рамки SDI
		RUNTIME_CLASS(CProjectView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Разрешить использование расширенных символов в горячих клавишах меню
	CMFCToolBar::m_bExtCharTranslation = TRUE;

	// Синтаксический разбор командной строки на стандартные команды оболочки, DDE, открытие файлов
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Команды диспетчеризации, указанные в командной строке.  Значение FALSE будет возвращено, если
	// приложение было запущено с параметром /RegServer, /Register, /Unregserver или /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Одно и только одно окно было инициализировано, поэтому отобразите и обновите его
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// Обработчики сообщений CProjectApp



// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Команда приложения для запуска диалога
void CProjectApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Обработчики сообщений CProjectApp

void CProjectApp::CreateTriangle() 
{ 
	buf_obj_type = ID_Triangle;
	move_tool.SetActive(false);
}
void CProjectApp::CreateRectangle() 
{ 
	buf_obj_type = ID_Rectangle; 
	move_tool.SetActive(false);
}
void CProjectApp::CreateEllipse() 
{ 
	buf_obj_type = ID_Ellipse;	
	move_tool.SetActive(false);
}
void CProjectApp::CreateConnection() 
{ 
	buf_obj_type = ID_Line; 
	move_tool.SetActive(false);
}
void CProjectApp::OpenFile()
{
	CFileDialog dlg(true, (LPCTSTR)L"txt", NULL, OFN_READONLY, (LPCTSTR)L" Text Files (*.txt) |*.txt||");
	if (dlg.DoModal() == IDOK)
	{
		obj_pathname = dlg.GetPathName();
		on_open_file(obj_pathname);
	}
}
void CProjectApp::SaveFile()
{
	if (obj_pathname.Compare(L"null") == 0)
	{
		CFileDialog dlg(false, (LPCTSTR)L"txt", NULL, OFN_READONLY | OFN_OVERWRITEPROMPT, (LPCTSTR)L" Text Files (*.txt) |*.txt||");
		if (dlg.DoModal() == IDOK)
		{
			obj_pathname = dlg.GetPathName();
			on_save_file(obj_pathname);
		}
	}
	else on_save_file(obj_pathname);
}
void CProjectApp::CloseFile()
{
	if (obj_pathname.Compare(L"null") != 0)
		on_close_file();
}
void CProjectApp::MoveObject() 
{ 
	move_tool.SetActive(true);
	buf_obj_type = -1;
}
