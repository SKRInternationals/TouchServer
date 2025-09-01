#include "Util.h"

#include <Windows.h>

int ReadJSON(const std::string& buff, std::unordered_map<std::string, std::string>& input) {
	int i = 0;
	char ch = buff[i];
	int state = 0;
	int start = 0;
	int stop = -1;
	std::string key;
	std::string value;
	bool flag = true;
	while (flag)
	{
		ch = buff[i];
		if (ch == ' ' || ch == '\n' || ch == '\t') {
			i++;
			continue;
		}
		switch (state) {
		case 0:
			if (ch == '{') {
				state = 1;
			}
			else if (ch == ' ') {
				break;
			}
			else {
				state = -1;
				flag = false;
			}
			break;
		case 1:
			if (ch == '\"') {
				state = 2;
			}
			else {
				state = -2;
				flag = false;
			}
			break;
		case 2:
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_') || (ch >= '0' && ch <= '9') || ch == '-' || ch == '+') {
				start = i;
				state = 3;
			}
			else {
				state = -3;
				flag = false;
			}
			break;
		case 3:
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_') || (ch >= '0' && ch <= '9') || ch == '-' || ch == '+') {
				break;
			}
			else if (ch == '\"') {
				stop = i;
				int len = stop - start;
				key = buff.substr(start, len);
				state = 4;
			}
			else {
				state = -4;
				flag = false;
			}
			break;
		case 4:
			if (ch == ':') {
				state = 5;
			}
			else {
				state = -5;
				flag = false;
			}
			break;
		case 5:
			if (ch == '\"') {
				state = 6;
			}
			else {
				state = -6;
				flag = false;
			}
			break;
		case 6:
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_') || (ch >= '0' && ch <= '9') || ch == '-' || ch == '+') {
				start = i;
				state = 7;
			}
			else {
				state = -7;
				flag = false;
			}
			break;
		case 7:
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_') || (ch >= '0' && ch <= '9') || ch == '-' || ch == '+') {
				break;
			}
			else if (ch == '\"') {
				stop = i;
				int len = stop - start;
				value = buff.substr(start, len);
				input[key] = value;
				state = 8;
			}
			else {
				state = -8;
				flag = false;
			}
			break;
		case 8:
			if (ch == ',') {
				state = 1;
			}
			else if (ch == '}') {
				state = 9;
				flag = false;
			}
			else {
				state = -9;
				flag = false;
			}
			break;
		case 9:
			flag = false;
			break;
		default:
			break;
		}
		i++;
	}
	return state;
}


void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}