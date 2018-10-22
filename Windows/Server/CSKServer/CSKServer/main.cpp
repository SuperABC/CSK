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

	cout << inst << endl;

	if (inst == "登录请求") {
		loginProcess(json, socket);
	}
	else if (inst == "加入房间") {
		roomProcess(json, socket);
	}
	else if (inst == "选择武将") {
		killerProcess(json, socket);
	}

	if (inst == "出牌结束") {
		int roomId = getContent(json, "room")->data.json_int;
		useProcess(json, roomId);
		stateProcess(roomId);
	}
	else if (inst == "弃牌结束") {
		int roomId = getContent(json, "room")->data.json_int;
		dropProcess(json, roomId);
		stateProcess(roomId);
	}
	else if (inst == "使用手牌") {
		int roomId = getContent(json, "room")->data.json_int;
		int playerPos = getContent(json, "position")->data.json_int;
		char *cardCont = getContent(json, "action")->data.json_string;
		cardProcess(str, roomId, playerPos, cardCont);
	}
	else if (inst == "结算完成") {
		int roomId = getContent(json, "room")->data.json_int;
		int playerPos = getContent(json, "position")->data.json_int;
		doneProcess(roomId, playerPos);
	}
	else if (inst == "绩点变化") {
		int roomId = getContent(json, "room")->data.json_int;
		int playerPos = getContent(json, "position")->data.json_int;
		gradeProcess(str, roomId, playerPos);
	}

	freeJson(json);
}
NEW_THREAD_FUNC(singleMsg) {
	SOCKET tmp = connection;
	char buffer[256] = { 0 };
	char *buf;

	while (socketReceive(tmp, buffer, 256) != SG_CONNECTION_FAILED) {
		buf = buffer;
		while (buf[0]) {
			mainHandler(buf, tmp);
			buf += strlen(buf) + 1;
		}
		memset(buffer, 0, 256);
	}
	closeSocket(tmp);
	return 0;
}
NEW_THREAD_FUNC(socketResponse) {
	bool nodelay = true;
	while (1) {
		connection = acceptOne(server);
		setsockopt(connection, SOL_SOCKET, TCP_NODELAY, (const char *)&nodelay, sizeof(bool));
		createThread(singleMsg, NULL);
	}
	return 0;
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
			if (r == NULL)continue;
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
	createThread(socketResponse, NULL);
	cout << "CSK Server is on." << endl;

	while (1) {
		string buf;
		std::getline(std::cin, buf);
		cmdProc(buf);
	}
}
