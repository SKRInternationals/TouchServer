#pragma once
#include <string>
#include <unordered_map>

#ifndef NDEBUG
#define LOG(msg) std::cout<<__FILE__<<":"<<__LINE__<<"::"<<msg<<std::endl;
#else
#define LOG(msg)
#endif // !NDEBUG


int ReadJSON(const std::string& buff, std::unordered_map<std::string, std::string>& input);
void GetDesktopResolution(int& horizontal, int& vertical);
