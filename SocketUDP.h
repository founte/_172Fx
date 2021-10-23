 #ifndef SOCKETUDP_H
#define SOCKETUDP_H

#include <winsock2.h>
#include <Ws2tcpip.h>
#include "tool.h"
#include <stdio.h>
#include <stdlib.h>



struct SocketInitializer
{
  ~SocketInitializer()
    {
		Uninit();
    }
    SocketInitializer()
    {
		Init();
	}

	static void Init()
	{
        WSADATA wsaData;
        int err = WSAStartup(MAKEWORD(2,2), &wsaData);
		if(err != 0)
		{
			TCHAR msg[128] = {0};
			sprintf_s(msg, _T("WSAStartup failed with error: %d!"), err);
			ErrorMassageBox(msg);
		}
		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) 
		{
			ErrorMassageBox(_T("Could not find a usable version of Winsock.dll!"));
			WSACleanup();
		}
		bInit = true;
	}
	static void Uninit()
	{
        WSACleanup();
		bInit = false;
	}
	static bool bInit;
};


class SocketUDP
{
public:
	SocketUDP();
	~SocketUDP();
	bool Bind(unsigned short Pt, const char* localIP = NULL);
	bool Send(const char* pSend, size_t len, const char* IP, unsigned short Port);
	int Receive(char* pRecv, size_t MaxLen, char* senderIP, unsigned short* senderPt);
	void SetBlocking(bool flag);
	const char* GetErrorMessage();
	bool SocketUDP::join_multicast_group(const char* grpaddr, const char* iaddr = NULL);
	bool SocketUDP::set_local_interface(const char* iaddr);
private:
	char	m_szErrorMsg[256];
	SOCKET	m_socket;
private:
	void ErrorToString(const char* lpszMessage);
	void Create();
	void Close();
};

#endif //SOCKETUDP_H