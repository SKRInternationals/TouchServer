#pragma comment (lib,"ws2_32.lib")

#include "UDPReceiver.h"
#include "NetworkException.h"

UDPReceiver::UDPReceiver(unsigned short int port) {
	this->port = port;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		LOG_ERR;
		throw NetworkException("WSA Startup failed", __FILE__, __LINE__);
	}
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		LOG_ERR;
		throw NetworkException("Socket Open Failed", __FILE__, __LINE__);
	}

	toRecv.sin_port = htons(this->port);
	toRecv.sin_family = AF_INET;
	toRecv.sin_addr.s_addr = ADDR_ANY;

	int ret = bind(sock, reinterpret_cast<SOCKADDR*>(&toRecv), sizeof(toRecv));
	if (ret < 0) {
		LOG_ERR;
		throw NetworkException("Socket Bind Failed", __FILE__, __LINE__);
	}
	this->addrSize = sizeof(toRecv);
}

UDPReceiver::UDPReceiver(IPv4 ip, unsigned short int port) {
	this->port = port;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		LOG_ERR;
		throw NetworkException("WSA Startup failed", __FILE__, __LINE__);
	}
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		LOG_ERR;
		throw NetworkException("Socket Open Failed", __FILE__, __LINE__);
	}

	toRecv.sin_port = htons(this->port);
	toRecv.sin_family = AF_INET;
	toRecv.sin_addr.S_un.S_un_b = { ip.s_b1,ip.s_b2,ip.s_b3,ip.s_b4 };

	int ret = bind(sock, reinterpret_cast<SOCKADDR*>(&toRecv), sizeof(toRecv));
	if (ret < 0) {
		LOG_ERR;
		throw NetworkException("Socket Bind Failed", __FILE__, __LINE__);
	}
	this->addrSize = sizeof(toRecv);
}

UDPReceiver::~UDPReceiver() {
	if (sock != INVALID_SOCKET) {
		closesocket(sock);
	}
	WSACleanup();
}

int UDPReceiver::Bind(IPv4 ip, unsigned short int port) {
	return 0;
}

int UDPReceiver::Bind(IPv4 ip) {
	return 0;
}
int UDPReceiver::Bind(unsigned short int port) {
	return 0;
}

int UDPReceiver::Recv(char* data, int size, int flags) {
	int ret = recvfrom(sock, data, size, flags, reinterpret_cast<SOCKADDR*>(&toRecv), &this->addrSize);
	if (ret < 0) {
		throw NetworkException("Data Receive Failed", __FILE__, __LINE__);
	}
	data[ret] = 0;
	return 0;
}


int UDPReceiver::Recv(char* data, int size, IPv4 ip, unsigned short int port, int flags) {
	return 0;
}