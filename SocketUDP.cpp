#include "stdafx.h"
#include "SocketUDP.h"
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wininet.lib")


bool SocketInitializer::bInit = false;

SocketUDP::SocketUDP()
{
	if(SocketInitializer::bInit == false)
	{
		SocketInitializer::Init();
	}
	memset(m_szErrorMsg, 0, sizeof(m_szErrorMsg));
	Create();
}

SocketUDP::~SocketUDP()
{
	Close();
}

bool SocketUDP::Bind(unsigned short Port, const char* localIP)
{
	if (Port != 0)
	{
		// Build an address with the specified port
		sockaddr_in Addr;
		Addr.sin_family      = AF_INET;
		Addr.sin_port        = htons(Port);
		if(localIP == NULL)
		{
			Addr.sin_addr.s_addr = INADDR_ANY;
		}
		else
		{
			Addr.sin_addr.S_un.S_addr = inet_addr(localIP);
		}
		memset(Addr.sin_zero, 0, sizeof(Addr.sin_zero));

		// Bind the socket to the port
		if (bind(m_socket, reinterpret_cast<sockaddr*>(&Addr), sizeof(Addr)) == -1)
		{
			ErrorToString("Failed to bind the socket to port ");
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}
bool SocketUDP::Send(const char* pSend, size_t len, const char* IP, unsigned short Port)
{
   if (pSend && len)
    {
        // Build the target address
        sockaddr_in Target;
        Target.sin_family      = AF_INET;
        Target.sin_port        = htons(Port);
        Target.sin_addr.s_addr = inet_addr(IP);
        memset(Target.sin_zero, 0, sizeof(Target.sin_zero));

        // Loop until every byte has been sent
        int Sent = 0;
        int SizeToSend = static_cast<int>(len);
        for (int Length = 0; Length < SizeToSend; Length += Sent)
        {
            // Send a chunk of data
            Sent = sendto(m_socket, pSend + Length, SizeToSend - Length, 0, reinterpret_cast<sockaddr*>(&Target), sizeof(Target));

            // Check errors
            if (Sent <= 0)
			{
				ErrorToString("send failed");
                return false;
			}
        }
    }
   else
   {
		return false;
   }
	return true;
}
int SocketUDP::Receive(char* pRecv, size_t Maxlen, char* senderIP, unsigned short* senderPt)
{
	int nRes = 0;
    // Check parameters
    if (pRecv && Maxlen)
    {
        // Data that will be filled with the other computer's address
        sockaddr_in Sender;
        Sender.sin_family      = AF_INET;
        Sender.sin_port        = 0;
        Sender.sin_addr.s_addr = INADDR_ANY;
        memset(Sender.sin_zero, 0, sizeof(Sender.sin_zero));
        int SenderSize = sizeof(Sender);

        // Receive a chunk of bytes
        nRes = recvfrom(m_socket, pRecv, static_cast<int>(Maxlen), 0, reinterpret_cast<sockaddr*>(&Sender), &SenderSize);

        // Check the number of bytes received
        if (nRes > 0)
        {
			if(senderIP)
			{
				const char* p = inet_ntoa(Sender.sin_addr);
				memcpy(senderIP, p, strlen(p));
			}
			if(senderPt)
			{
				*senderPt =ntohs(Sender.sin_port);
			}
        }
        else
        {
			if(senderIP)
			{
				senderIP = 0;
			}

            if(senderPt)
			{
				*senderPt = 0;
			}

			ErrorToString("receive failed");
        }
    }
	return nRes;
}
const char* SocketUDP::GetErrorMessage()
{
	return m_szErrorMsg;
}
	
void SocketUDP::ErrorToString(const char* lpszMessage)
{
	LPVOID lpMessageBuffer;
	DWORD  error = GetLastError();	
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,      // source and processing options
		NULL,                            // pointer to message source
		error,                           // requested message identifie
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // the user default language.
		(LPTSTR) &lpMessageBuffer,       // pointer to message buffer
		0,                               // maximum size of message buffer
		NULL);                           // address of array of message inserts 
	
	// and copy it in our error string
	sprintf_s(m_szErrorMsg,"%s: (%d) %s\n", lpszMessage, error, lpMessageBuffer);	
	LocalFree(lpMessageBuffer);
}


void SocketUDP::Create()
{	
	m_socket = socket(PF_INET, SOCK_DGRAM, 0);
	if(INVALID_SOCKET != m_socket)
	{
	    int Yes = 1;
        // Enable broadcast by default
        if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char*>(&Yes), sizeof(Yes)) == -1)
        {
			ErrorMassageBox(_T("setsockopt:SO_BROADCAST failed!"));
        }
		//设置超时
		//int nNetTimeout = 100;
		//if(-1 == setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&nNetTimeout, sizeof(int)))
		//{
		//	ErrorMassageBox(_T("setsockopt:SO_RCVTIMEO failed!"));
		//}
		//设置阻塞
		SetBlocking(true);
		//无缓冲区
		int nZero = 0;
		if(-1 == setsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, (char*)&nZero, sizeof(nZero)))
		{
			ErrorMassageBox(_T("setsockopt:SO_SNDBUF failed!"));
		}
		if(-1 == setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, (char*)&nZero, sizeof(nZero)))
		{
			ErrorMassageBox(_T("setsockopt:SO_RCVBUF failed!"));
		}


	}
	else
	{
		TCHAR msg[128] = {0};
		sprintf_s(msg, _T("create socket failed %d!"), WSAGetLastError());
		ErrorMassageBox(msg);
	}	
}

//加入组播组
bool SocketUDP::join_multicast_group(const char* grpaddr, const char* iaddr)
{
	struct ip_mreq group;

	group.imr_multiaddr.s_addr = inet_addr(grpaddr);

	if(iaddr == NULL)
	{
		group.imr_interface.s_addr = INADDR_ANY;
	}
	else
	{
		group.imr_interface.s_addr = inet_addr(iaddr);
	}
	if(setsockopt(m_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) == SOCKET_ERROR )

	{
		return false;
	}
	return true;
}

//指定发送组播数据的网络接口
bool SocketUDP::set_local_interface(const char* iaddr)
{
	struct in_addr localInterface;
	localInterface.s_addr = inet_addr(iaddr);

	if(setsockopt(m_socket, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) == SOCKET_ERROR )
	{
		return false;
	}
	return true;
}
void SocketUDP::SetBlocking(bool flag)
{
	unsigned long Yes = flag ? 0 : 1;
	ioctlsocket(m_socket, FIONBIO, &Yes);
}

void SocketUDP::Close()
{
	closesocket(m_socket);
}


SocketInitializer GlobalInitializer;