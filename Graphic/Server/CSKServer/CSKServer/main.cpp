#include "winsgl.h"
#include <vector>
SGL_CONSOLE_FRAME

SOCKET server, connection;

std::vector<int> loginList;
int loginMax = 0;

void mainHandler(char *str, SOCKET socket) {
	char idStr[8];
	if (std::string(str) == "login") {
		itoa(loginMax, idStr, 10);
		socketSend(socket, idStr);
		loginList.push_back(loginMax);
		loginMax++;
	}
}
void singleMsg() {
	SOCKET tmp = connection;
	char buf[64] = { 0 };

	while (socketReceive(tmp, buf, 64) != SG_CONNECTION_FAILED) {
		mainHandler(buf, tmp);
	}
	closeSocket(tmp);
}
void socketResponse() {
	while (1) {
		connection = acceptOne(server);
		createThread(singleMsg);
	}
}
int main() {
	std::string buf;

	server = createServer(4497);
	createThread(socketResponse);
	std::cout << "CSK Server is on." << std::endl;

	while (1) {
		std::getline(std::cin, buf);
		if (buf == "status") {
			std::cout << "CSK Server is running." << std::endl;
		}
		if (buf == "users") {
			for (auto i : loginList)
				std::cout << i << " ";
			std::cout << std::endl;
		}
	}
}
