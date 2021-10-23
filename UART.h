// UART.h : main header file for the UART application
//

#if !defined(AFX_UART_H__B5C2E39B_9C5F_4C8A_ADB5_2AEE53F01A58__INCLUDED_)
#define AFX_UART_H__B5C2E39B_9C5F_4C8A_ADB5_2AEE53F01A58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUARTApp:
// See UART.cpp for the implementation of this class
//

class CUARTApp : public CWinApp
{
public:
	CUARTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUARTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUARTApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UART_H__B5C2E39B_9C5F_4C8A_ADB5_2AEE53F01A58__INCLUDED_)
