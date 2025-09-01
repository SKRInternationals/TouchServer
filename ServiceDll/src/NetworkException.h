#pragma once
#include <string>

#ifndef NDEBUG
#include <iostream>
#define LOG_ERR std::cerr << "Error At : " << __FILE__ << " : " << __LINE__ << ", Code : " << WSAGetLastError() << std::endl
#else
#define LOG_ERR
#endif

class NetworkException:public std::exception
{
private:
	std::string message;
	std::string file;
	int line;
public:
	NetworkException(std::string message,std::string file,int line);
	~NetworkException();

public:
	const char* what()noexcept ;
	std::string getFileName();
	int getLine();
};

