#pragma once
#include "Network.h"

#include <WinSock2.h>

#define DEFAULT_PORT 10117

class UDPSender
{
private:
    SOCKET sock;
    WSAData wsaData;
    sockaddr_in toSend;
    unsigned short port;

public:
    UDPSender(unsigned short int port = DEFAULT_PORT);
    UDPSender(IPv4 ip, unsigned short int port = DEFAULT_PORT);
    ~UDPSender();

public:
    int Bind(IPv4 ip, unsigned short int port);
    int Bind(IPv4 ip);
    int Bind(unsigned short int port);

public:
    int Send(const char *data, int size, int flags = 0);
    int Send(const char *data, int size, IPv4 ip, int flags = 0);
    int Send(const char *data, int size, IPv4 ip, unsigned short int port, int flags = 0);
    int Send(const char *data, int size, sockaddr_in toSend, int flags = 0);
};
