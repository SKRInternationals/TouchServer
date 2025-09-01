#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Network.h"

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

bool GetMyIP(struct IPv4& myIP)
{
    char szBuffer[1024];

#ifdef WIN32
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 0);
    if (::WSAStartup(wVersionRequested, &wsaData) != 0)
        return false;
#endif


    if (gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR)
    {
#ifdef WIN32
        WSACleanup();
#endif
        return false;
    }

    struct hostent* host = gethostbyname(szBuffer);
    if (host == NULL)
    {
#ifdef WIN32
        WSACleanup();
#endif
        return false;
    }

    //Obtain the computer's IP
    myIP.s_b1 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b1;
    myIP.s_b2 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b2;
    myIP.s_b3 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b3;
    myIP.s_b4 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b4;

#ifdef WIN32
    WSACleanup();
#endif
    return true;
}


