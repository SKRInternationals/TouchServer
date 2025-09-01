#pragma once
#include "Network.h"

constexpr unsigned short int ECHO_PORT = 5560;
constexpr unsigned short int SERVER_PORT = 5559;

void EchoThread();
void EchoThreadA(IPv4 ip);
void ServerThread();