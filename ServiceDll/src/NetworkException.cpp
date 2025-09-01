#include "NetworkException.h"

NetworkException::NetworkException(std::string message, std::string file, int line)
{
    this->message = message.append("::File:").append(file).append("::Line:").append(std::to_string(line));
    this->file = file;
    this->line = line;
}

NetworkException::~NetworkException()
{
}

const char *NetworkException::what() noexcept
{
    return this->message.c_str();
}

std::string NetworkException::getFileName()
{
    return this->file;
}

int NetworkException::getLine()
{
    return this->line;
}