#include "main.h"
#include "user.h"
#include "room.h"
#include "killer.h"
SGL_CONSOLE_FRAME

SOCKET server, connection;

vector<User *> userList;
vector<Room *> roomList;

using std::cout;
using std::endl;

void mainHandler(char *str, SOCKET socket) {
	struct JSON *json = readJson(str);
	string inst = getContent(json, "inst")->data.json_string;

	if (inst == "login") {
		loginProcess(json, socket);
	}
	else if (inst == "room") {
		roomProcess(json, socket);
	}
	else if (inst == "killer") {
		killerProcess(json, socket);
	}
	else if (inst == "game") {
		int roomId = getContent(json, "room")->data.json_int;
		if (getContent(json, "end")) {
			changeState(roomId);
		}
		else {
			int playerPos = getContent(json, "position")->data.json_int;
			gameProcess(str, roomId, playerPos);
		}
	}

	freeJson(json);
}
void singleMsg() {
	SOCKET tmp = connection;
	char buf[256] = { 0 };

	while (socketReceive(tmp, buf, 256) != SG_CONNECTION_FAILED) {
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

void cmdProc(string cmd) {
	if (cmd == "status") {
		cout << "CSK Server is running." << endl;
	}
	if (cmd == "users") {
		for (auto u : userList) {
			cout << u->name << ":";
			switch (u->status) {
			case US_LOGIN:
				cout << "空闲";
				break;
			case US_ROOM:
				cout << u->roomId << "号房间";
				break;
			case US_WAITING:
				cout << "等待中";
				break;
			case US_KILLER:
				cout << "选择学生中";
				break;
			case US_PLAYING:
				cout << "游戏中";
				break;
			}
			cout << endl;
		}
	}
	if (cmd == "rooms") {
		for (auto r : roomList) {
			cout << r->roomId << "号房间:人数" << r->users.size();
			switch (r->status) {
			case RS_WAITING:
				cout << " 等待中";
				break;
			case RS_PLAYING:
				cout << " 游戏中";
				break;
			default:
				break;
			}
			cout << endl;
		}
	}
	if (cmd == "newroom") {
		Room *r = new Room(roomList.size());
		roomList.push_back(r);
	}
}

int main() {
	server = createServer(4497);
	createThread(socketResponse);
	cout << "CSK Server is on." << endl;

	while (1) {
		string buf;
		std::getline(std::cin, buf);
		cmdProc(buf);
	}
}
