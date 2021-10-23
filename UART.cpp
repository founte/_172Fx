// UART.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "UART.h"
#include "UARTDlg.h"
#include "Fsx.h"
#include "fcntl.h"
#include "io.h"
#include "pubData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUARTApp

BEGIN_MESSAGE_MAP(CUARTApp, CWinApp)
	//{{AFX_MSG_MAP(CUARTApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUARTApp construction

CUARTApp::CUARTApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUARTApp object

CUARTApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUARTApp initialization

BOOL CUARTApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//HANDLE hConHandle;
	//FILE* fp;
	////开启一个控制台窗口，便于调试
	//AllocConsole();
	////获取标准输出句柄
	//g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	////将STDOUT重定向到控制台
	//hConHandle = reinterpret_cast<HANDLE>(_open_osfhandle(reinterpret_cast<int>(g_hOutput), _O_TEXT));
	//fp = _fdopen(reinterpret_cast<int>(hConHandle), "w");
	//*stdout = *fp;
	//setvbuf(stdout, NULL, _IONBF, 0);
	
	//启动FSX线程
	Fsx *f = new Fsx();
	Thread* thread = new Thread(Fsx::startFsx, (void*)f);
	thread->Launch();
	
	//启动窗口
	CUARTDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return FALSE;
}
