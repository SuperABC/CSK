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

NEW_THREAD_FUNC(mainHandler) {
	char *str = (char *)param;
	SOCKET socket;
	memcpy(&socket, (char *)param + strlen((char *)param) + 1, sizeof(socket));

	struct JSON *json = readJson(str);
	string inst = getContent(json, "inst")->data.json_string;

	cout << inst << endl;

	if (inst == "��¼����") {
		loginProcess(json, socket);
	}
	else if (inst == "���뷿��") {
		roomProcess(json, socket);
	}
	else if (inst == "ѡ���佫") {
		killerProcess(json, socket);
	}

	if (inst == "���ƽ���") {
		int roomId = getContent(json, "room")->data.json_int;
		useProcess(json, roomId);
		stateProcess(roomId);
	}
	else if (inst == "���ƽ���") {
		int roomId = getContent(json, "room")->data.json_int;
		dropProcess(json, roomId);
		stateProcess(roomId);
	}
	else if (inst == "ʹ������") {
		int roomId = getContent(json, "room")->data.json_int;
		int playerPos = getContent(json, "position")->data.json_int;
		char *cardCont = getContent(json, "action")->data.json_string;
		cardProcess(str, roomId, playerPos, cardCont);
	}
	else if (inst == "�������") {
		int roomId = getContent(json, "room")->data.json_int;
		int playerPos = getContent(json, "position")->data.json_int;
		char *cardCont = getContent(json, "action")->data.json_string;
		replyProcess(str, roomId, playerPos, cardCont);
	}
	else if (inst == "���ÿ���") {
		int roomId = getContent(json, "room")->data.json_int;
		int playerPos = getContent(json, "position")->data.json_int;
		Card dropCard = getContent(json, "card")->data.json_object;
		lossProcess(str, roomId, playerPos, dropCard);
	}
	else if (inst == "�������") {
		int roomId = getContent(json, "room")->data.json_int;
		int playerPos = getContent(json, "position")->data.json_int;
		doneProcess(roomId, playerPos);
	}
	else if (inst == "����仯") {
		int roomId = getContent(json, "room")->data.json_int;
		int playerPos = getContent(json, "position")->data.json_int;
		int changeAmount = getContent(json, "amount")->data.json_int;
		gradeProcess(str, roomId, playerPos, changeAmount);
	}

	freeJson(json);
	free(param);
	return 0;
}
NEW_THREAD_FUNC(singleMsg) {
	SOCKET tmp = *(SOCKET *)param;
	char buffer[256] = { 0 };
	char *buf;

	while (socketReceive(tmp, buffer, 256) != SG_CONNECTION_FAILED) {
		buf = buffer;
		while (buf[0]) {
			char *param = (char *)malloc(256);
			memcpy(param, buf, strlen(buf) + 1);
			memcpy(param + strlen(buf) + 1, &tmp, sizeof(tmp));
			createThread(mainHandler, param);
			buf += strlen(buf) + 1;
		}
		memset(buffer, 0, 256);
	}
	closeSocket(tmp);
	free(param);
	return 0;
}
NEW_THREAD_FUNC(socketResponse) {
	bool nodelay = true;
	while (1) {
		connection = acceptOne(server);
		setsockopt(connection, SOL_SOCKET, TCP_NODELAY, (const char *)&nodelay, sizeof(bool));

		SOCKET *param = (SOCKET *)malloc(sizeof(SOCKET));
		*param = connection;
		createThread(singleMsg, param);
	}
	return 0;
}

void cmdProc(string cmd) {
	if (cmd == "server status") {
		cout << "CSK Server is running." << endl;
	}
	if (cmd == "view users") {
		for (auto u : userList) {
			cout << u->name << ":";
			switch (u->status) {
			case US_LOGIN:
				cout << "����";
				break;
			case US_ROOM:
				cout << u->roomId << "�ŷ���";
				break;
			case US_WAITING:
				cout << "�ȴ���";
				break;
			case US_KILLER:
				cout << "ѡ��ѧ����";
				break;
			case US_PLAYING:
				cout << "��Ϸ��";
				break;
			}
			cout << endl;
		}
	}
	if (cmd == "view rooms") {
		for (auto r : roomList) {
			if (r == NULL)continue;
			cout << r->roomId << "�ŷ���:����" << r->users.size();
			switch (r->status) {
			case RS_WAITING:
				cout << " �ȴ���";
				break;
			case RS_PLAYING:
				cout << " ��Ϸ��";
				break;
			default:
				break;
			}
			cout << endl;
		}
	}
	if (cmd == "new room") {
		Room *r = new Room(roomList.size());
		roomList.push_back(r);
	}
	if (cmd == "veiw managers") {
		for (auto r : roomList) {
			if (r == NULL)continue;
			cout << r->roomId << "�ŷ���:����" << r->users.size() << endl;
			if (r->manager) {
				r->manager->logInfo();
			}
			cout << endl;
		}
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
