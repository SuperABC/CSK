#include "winsgl.h"
#include "user.h"
#include "room.h"
#include "killer.h"
#include <vector>
SGL_CONSOLE_FRAME

SOCKET server, connection;

std::vector<User *> userList;
int userMax = 0;
std::vector<Room *> roomList;
int roomMax = 0;

void mainHandler(char *str, SOCKET socket) {
	std::string msg(str);
	std::string inst = msg.substr(0, msg.find(' '));
	
	if (inst == "login") {
		std::string name = msg.substr(msg.find(' ') + 1);

		struct JSON *json = createJson();
		for (auto u : userList) {
			if (u->name == name) {
				setStringContent(json, "inst", (char *)"relogin success");
				setIntContent(json, "id", u->userId);
				setIntContent(json, "status", u->status);
				socketSend(socket, writeJson(json));
				u->socket = socket;
				freeJson(json);
				return;
			}
		}
		setStringContent(json, "inst", (char *)"login success");
		setIntContent(json, "id", userMax);
		setIntContent(json, "status", US_LOGIN);
		socketSend(socket, writeJson(json));
		userList.push_back(new User(msg.substr(msg.find(' ') + 1), socket, userMax++));
		freeJson(json);
	}
	else if (inst == "room") {
		int id = atoi(msg.substr(msg.find(' ') + 1).data());

		struct JSON *json = createJson();
		for (auto r : roomList) {
			if (r->waiting()) {
				setStringContent(json, "inst", (char *)"room success");
				setIntContent(json, "id", r->roomId);
				socketSend(socket, writeJson(json));
				r->comein(userList[id]);
				break;
			}
		}
		if (userList[id]->status == US_LOGIN) {
			Room *r = new Room(roomMax++);
			setStringContent(json, "inst", (char *)"room success");
			setIntContent(json, "id", r->roomId);
			socketSend(socket, writeJson(json));
			r->comein(userList[id]);
			roomList.push_back(r);
		}
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
	bool nodelay = true;
	while (1) {
		connection = acceptOne(server);
		setsockopt(connection, SOL_SOCKET, TCP_NODELAY, (const char *)&nodelay, sizeof(bool));
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
			for (auto u : userList) {
				std::cout << u->name << ":";
				switch (u->status) {
				case US_LOGIN:
					std::cout << "空闲";
					break;
				case US_ROOM:
					std::cout << u->roomId << "号房间";
					break;
				case US_WAITING:
					std::cout << "等待中";
					break;
				case US_KILLER:
					std::cout << "选择学生中";
					break;
				case US_PLAYING:
					std::cout << "游戏中";
					break;
				}
				std::cout << std::endl;
			}
		}
		if (buf == "rooms") {
			for (auto r : roomList) {
				std::cout << r->roomId << "号房间:人数" << r->users.size();
				switch (r->status) {
				case RS_WAITING:
					std::cout << " 等待中";
					break;
				case RS_PLAYING:
					std::cout << " 游戏中";
					break;
				default:
					break;
				}
				std::cout << std::endl;
			}
		}
		if (buf == "newroom") {
			Room *r = new Room(roomMax++);
			roomList.push_back(r);
		}
	}
}

void chooseKiller(int roomId) {
	std::cout << roomId << "号房间开始游戏，人数" << roomList[roomId]->users.size() << std::endl;

	std::vector<KILLER> killerSet;
	for (int i = 0; i < KILLER_END; i++)killerSet.push_back((KILLER)i);
	shuffleVector(killerSet);

	for (auto u : roomList[roomId]->users) {
		struct JSON *ks = createJsonArray();
		for (int i = 0; i < 5; i++) {
			setIntElement(ks, -1, killerSet.back());
			killerSet.pop_back();
		}
		struct JSON *json = createJson();
		setStringContent(json, "inst", (char *)"choose killer");
		setArrayContent(json, "list", ks);
		socketSend(u->socket, writeJson(json));
		freeJson(json);
	}
}
