                      #pragma once

//#include "串口控制dlg.h"
//////////////////////////////////////
#define  NET_OK 0
#define  NET_FAILED 1

//////////////////////////////////////

class CUdpNetComm
{
public:
	CUdpNetComm(void);
	~CUdpNetComm(void);
public:
	int CloseNewWork(void);
	int StartWork();  //开启新线程负责网络的接收与发送
	int InitNetwork(void);
	int lenSvr1;
	int lenSvr2;
	SOCKET m_socketPanel1,m_socketPanel2;
	SOCKADDR_IN m_addrServerPn1,m_addrServerPn2;
	SOCKADDR_IN m_addrClientPn1,m_addrClientPn2;
private:
	HANDLE m_hThread;  //接收线程句柄
	DWORD m_threadId;  //线程ID

private:
	static unsigned __stdcall ThreadFun(LPVOID lParam)
	{
		CUdpNetComm* theClass = (CUdpNetComm*)lParam;
		while(1)
		{
			theClass->Run();
		}
		return 1;
	}
	int Run();
};
