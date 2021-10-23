#include "stdafx.h"
#include "UdpNetComm.h"
#include "netData.h"
#include <process.h>

#define  BUFFERSIZE 1024
#define WM_USER_EDIT_END WM_USER+1001



extern  structPaneldata1    panneldata1;
extern	structPaneldata2	panneldata2;

extern int lock;
extern int lock1;

extern CRITICAL_SECTION g_criticalSection;	//ª•≥‚¡ŸΩÁ«¯
extern HWND g_hWnd;
extern HANDLE g_hOutput;

CUdpNetComm::CUdpNetComm(void)
{
	lenSvr1=0;
	lenSvr2=0;
}

CUdpNetComm::~CUdpNetComm(void)
{
}

int CUdpNetComm::InitNetwork(void)
{
	int nRes = 0;
	int err;
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );

	if ( err != 0 ) 
	{
		nRes = 1;
		return nRes;
	}

	if ( LOBYTE( wsaData.wVersion ) != 2 ||HIBYTE( wsaData.wVersion ) != 2 ) 
	{
		WSACleanup( );
		nRes = 1;
		return nRes;
	}

	m_socketPanel1 = socket(AF_INET,SOCK_DGRAM,0);	
	m_addrClientPn1.sin_addr.S_un.S_addr = inet_addr("192.168.1.19");
	m_addrClientPn1.sin_family = AF_INET;
	m_addrClientPn1.sin_port = htons(6667);

	return nRes;
}

int CUdpNetComm::CloseNewWork(void)
{
	closesocket(m_socketPanel1);
	return 0;

}

int CUdpNetComm::StartWork()
{

	m_hThread=(HANDLE)_beginthreadex(NULL,0,CUdpNetComm::ThreadFun,this,CREATE_SUSPENDED,(unsigned int *)&m_threadId);

	if(m_hThread==NULL){
		return 1;
	}

	::SetThreadPriority(m_hThread,THREAD_PRIORITY_ABOVE_NORMAL);
	::ResumeThread(m_hThread);
	return 0;
}

int CUdpNetComm::Run(void)
{

	int res = sendto(m_socketPanel1,(char *)&panneldata1,sizeof(structPaneldata1) , 0, (SOCKADDR *)&m_addrClientPn1,sizeof(SOCKADDR)); 
	Sleep(30);

	return NET_OK;

}
