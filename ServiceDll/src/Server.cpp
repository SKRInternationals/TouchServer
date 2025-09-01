#include "NetworkException.h"
#include "UDPSender.h"
#include "UDPReceiver.h"
#include "Util.h"
#include "Server.h"
#include "ServerOptions.h"

#include <iostream>
#include <thread>
#include <cmath>
#include <Windows.h>
#include <WinUser.h>
#include <unordered_map>

void ServerThread() {
	UDPReceiver server(SERVER_PORT);

	INPUT in;
	char buff[1024];
	std::string json;
	std::unordered_map<std::string, std::string> map;

	int X = 0, Y = 0;
	int nRet = 0;
	while (true)
	{

#ifndef NDEBUG
		std::cout << "Waiting for message" << std::endl;
#endif // !NDEBUG


		nRet = server.Recv(buff, 1024);
		if (nRet < 0) {
			LOG_ERR;
			throw NetworkException("Failed Receving UDP packet", __FILE__, __LINE__);
			exit(-1);
		}
		json = std::string(buff, 256);
		ReadJSON(json, map);

#ifndef NDEBUG
		std::cout << json << std::endl;
#endif // !NDEBUG

		in.type = std::stoi(map["type"]);
		if (in.type == INPUT_MOUSE) {
			in.mi.dx = std::stoi(map["dx"]);
			in.mi.dy = std::stoi(map["dy"]);
			in.mi.mouseData = std::stoi(map["mouseData"]);
			in.mi.time = std::stoi(map["time"]);
			in.mi.dwExtraInfo = std::stoi(map["dwExtraInfo"]);
			in.mi.dwFlags = std::stoi(map["dwFlags"]);
		}
		else if (in.type == INPUT_KEYBOARD) {
			in.ki.wVk = std::stoi(map["wVk"]);
			in.ki.wScan = std::stoi(map["wScan"]);
			in.ki.dwFlags = std::stoi(map["dwFlags"]);
			in.ki.time = std::stoi(map["time"]);
			in.ki.dwExtraInfo = std::stoi(map["dwExtraInfo"]);
		}
		else if (in.type == INPUT_HARDWARE) {
			//For Future
		}
		else {
			LOG_ERR;
		}

#ifndef NDEBUG
		std::cout << "\n\ntype\t\t:" << in.type << std::endl;
		if (in.type == INPUT_MOUSE) {
			std::cout << "dx\t\t:" << in.mi.dx << std::endl;
			std::cout << "dy\t\t:" << in.mi.dy << std::endl;
			std::cout << "mouseData\t:" << in.mi.mouseData << std::endl;
			std::cout << "mouse Flags\t:" << in.mi.dwFlags << std::endl;
		}
		else if (in.type == INPUT_KEYBOARD) {
			std::cout << "wVk\t\t:" << in.ki.wVk << std::endl;
			std::cout << "wScan\t\t:" << in.ki.wScan << std::endl;
			std::cout << "key Flags\t:" << in.ki.dwFlags << std::endl << std::endl << std::endl;
		}
#endif // !NDEBUG
		SendInput(1, &in, sizeof(INPUT));
	}
}

void EchoThread() {
	struct IPv4 ip;
	if (!GetMyIP(ip)) {
		LOG_ERR;
		throw NetworkException("Failed to get Local IP", __FILE__, __LINE__);
	}

	IPv4 broadCast = ip;
	broadCast.s_b4 = 255;

	UDPSender echo(broadCast, ECHO_PORT);

	while (true)
	{
		if (!GetMyIP(ip)) {
			LOG_ERR;
			throw NetworkException("Failed to get Local IP", __FILE__, __LINE__);
		}

		IPv4 broadCast = ip;
		broadCast.s_b4 = 255;

		echo.Send((const char*)&ip, 4, broadCast);
		Sleep(3000);
		std::cout << (int)ip.s_b1 << " " << (int)ip.s_b2 << " " << (int)ip.s_b3 << " " << (int)ip.s_b4 << std::endl;
	}
}

void EchoThreadA(IPv4 ip) {
	IPv4 broadCast = ip;
	broadCast.s_b4 = 255;

	UDPSender echo(broadCast, ECHO_PORT);
	std::cout << (int)ip.s_b1 << " " << (int)ip.s_b2 << " " << (int)ip.s_b3 << " " << (int)ip.s_b4 << std::endl;

	while (true)
	{
		echo.Send((const char*)&ip, 4, broadCast);
		Sleep(3000);
	}
}

#ifdef NDEBUG
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif // NDEBUG

{
	std::thread echo;

	/// Parse Command Line Arguments
	if (CmdOptionExists(argv, argv + argc, "-h"))
	{
		std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
		std::cout << "Options:" << std::endl;
		std::cout << "\t-h\t\t: Show this help message" << std::endl;
		std::cout << "\t-a <IP Address>\t: IP Address to send Echo Packets" << std::endl;
		/*std::cout << "\t-p <Port>\t: Port to listen for UDP Packets" << std::endl;
		std::cout << "\t\t\t  Default: " << SERVER_PORT << std::endl;*/
		return 0;
	}
	
	// -a <IP Address> : IP Address to send Echo Packets
	char* adrs = GetCmdOption(argv, argv + argc, "-a");
	if (adrs != 0)
	{
		struct IPv4 ip;
		std::string str(adrs);

		int pos = str.find('.');
		ip.s_b1 = std::stoi(str.substr(0, pos));
		str.erase(0, pos + 1);
		pos = str.find('.');
		ip.s_b2 = std::stoi(str.substr(0, pos));
		str.erase(0, pos + 1);
		pos = str.find('.');
		ip.s_b3 = std::stoi(str.substr(0, pos));
		str.erase(0, pos + 1);
		ip.s_b4 = std::stoi(str);

		echo = std::thread(EchoThreadA, ip);
	}
	else {
		echo = std::thread(EchoThread);
	}

	std::thread server(ServerThread);

	server.join();
	echo.join();
	return 0;
}
