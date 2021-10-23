// UARTDlg.h : header file
//
//{{AFX_INCLUDES()
#include "SocketUDP.h"
#include "Thread.h"
#include "mscomm.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "UdpNetComm.h"
//}}AFX_INCLUDES

#if !defined(AFX_UARTDLG_H__9EF7B397_345B_42D4_8CC1_53EAD84E5395__INCLUDED_)
#define AFX_UARTDLG_H__9EF7B397_345B_42D4_8CC1_53EAD84E5395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUARTDlg dialog

class CUARTDlg : public CDialog
{
// Construction
public:
	CUARTDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUARTDlg)
	enum { IDD = IDD_UART_DIALOG };
	CComboBox	m_Uart_Speed;
	CComboBox	m_COM_Num;
	CMSComm	m_CMSComm;
	CString	m_RxData;
	CString EditText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUARTDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CUARTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONOpenPort();
	afx_msg void OnBUTTONClean();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrl;
	CListCtrl m_ListCtrl;
	int TabCtrl_num;
	int nPort;
	bool Autosend;//�Զ����ͱ�־
	bool Send_or_Rece;
	long uart_speed;
	int Rxdata_num;//�������ݽ��ո���
	unsigned char Rxdata[512];//���ڽ������ݻ�����
	unsigned char senddata[512];//���ڷ������ݻ�����
	unsigned char Sendtemp[1024];//���ݷ���ʱ����ʱ������
	char Rece_temp[1024];//����������ʾ����ʱ������
	bool Send_Rece;
	int COM_Data[2][256];//�б���ʾ����
	HICON m_hicn_on;//����״ָ̬ʾ��-��
	HICON m_hicn_off;//����״ָ̬ʾ��-��
	CStatic *pStatic;//ͼ��
	int flag;
	SocketUDP* g_send_sock;
	Thread *m_thread;
	int time;//ͳ��ʱ��
	int f1,f2;
public:
	void Data_name(void);
	void Equipment_name(void);
	void Signal_data(void);
	void Unlock_Data(void);
	void ComPressData(void);
	void DataCtrl();
	void FillHead(char headChar[],int len);
	void SendData(unsigned char snd[], int len);
	void RecvData();
	void FillMeterData(void);
	void SendInit();
	static void ThreadNetTask(void* param);
	static void fillSocketMdata();
	unsigned char CharToHex(unsigned char iChar);
public:
	afx_msg void OnBnClickedButtonAutosend();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	afx_msg void OnBnClickedOk();
public:
	// ���Ϳ�����
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UARTDLG_H__9EF7B397_345B_42D4_8CC1_53EAD84E5395__INCLUDED_)
