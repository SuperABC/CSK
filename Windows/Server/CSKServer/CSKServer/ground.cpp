#include "main.h"
#include "user.h"
#include "room.h"
#include "killer.h"

using std::cout;
using std::endl;

extern vector<User *> userList;
extern vector<Room *> roomList;

void loginProcess(struct JSON *recv, SOCKET socket) {
	string name = getContent(recv, "name")->data.json_string;

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
	setIntContent(json, "id", userList.size());
	setIntContent(json, "status", US_LOGIN);
	socketSend(socket, writeJson(json));
	userList.push_back(new User(name, socket, userList.size()));
	freeJson(json);
}
void roomProcess(struct JSON *recv, SOCKET socket) {
	int id = getContent(recv, "id")->data.json_int;

	struct JSON *json = createJson();
	for (auto r : roomList) {
		if (r == NULL)continue;
		if (r->waiting()) {
			setStringContent(json, "inst", (char *)"room success");
			setIntContent(json, "id", r->roomId);
			socketSend(socket, writeJson(json));
			r->comein(userList[id]);
			break;
		}
	}
	if (userList[id]->status == US_LOGIN) {
		Room *r = new Room(roomList.size());
		setStringContent(json, "inst", (char *)"room success");
		setIntContent(json, "id", r->roomId);
		socketSend(socket, writeJson(json));
		r->comein(userList[id]);
		roomList.push_back(r);
	}
}
void killerProcess(struct JSON *recv, SOCKET socket) {
	int id = getContent(recv, "id")->data.json_int;
	int killer = getContent(recv, "killer")->data.json_int;
	roomList[userList[id]->roomId]->assign(id, (KILLER)killer);
}

void chooseKiller(int roomId) {
	cout << roomId << "号房间准备完毕，人数" << roomList[roomId]->users.size() << endl;
	vector<KILLER> killerSet;
	for (int i = 1; i < KILLER_END; i++)killerSet.push_back((KILLER)i);
	shuffleVector(killerSet);

	for (auto &u : roomList[roomId]->users) {
		u->status = US_KILLER;

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
void enterTable(int roomId) {
	cout << roomId << "号房间开始游戏。" << endl;
	shuffleVector(roomList[roomId]->users);

	struct JSON *json;

	json = createJson();
	setStringContent(json, "inst", (char *)"game init");
	setIntContent(json, "num", roomList[roomId]->users.size());
	struct JSON *killerList = createJsonArray();
	for (auto k : roomList[roomId]->users) {
		struct JSON *killer = createJson();
		setStringContent(killer, "user", (char *)k->name.data());
		setIntContent(killer, "killer", k->killer);
		setObjectElement(killerList, INT_MAX, killer);
	}
	setArrayContent(json, "killers", killerList);

	int position = 0;
	for (auto &u : roomList[roomId]->users) {
		u->status = US_PLAYING;

		setIntContent(json, "position", position++);
		socketSend(u->socket, writeJson(json));
	}
	freeJson(json);
	delay(100);

	roomList[roomId]->manager = new Manager(roomList[roomId]->users);
	json = createJson();
	setStringContent(json, "inst", (char *)"card init");
	for (auto &u : roomList[roomId]->users) {
		struct JSON *cardList = createJsonArray();
		for (int i = 0; i < 4; i++) {
			struct JSON *card = createJson();
			Card c = roomList[roomId]->manager->touchCard();
			setIntContent(card, "color", c.color);
			setIntContent(card, "num", c.num);
			setIntContent(card, "content", c.cont);
			setObjectElement(cardList, INT_MAX, card);
		}
		setArrayContent(json, "cards", cardList);
		socketSend(u->socket, writeJson(json));
		deleteContent(json, "cards");
	}
	freeJson(json);
	delay(100);

	int *param = new int(roomId);
	createThread(gameLoop, param);
}
