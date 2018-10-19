#include "main.h"
#include "user.h"
#include "room.h"
#include "killer.h"

extern vector<User *> userList;
extern vector<Room *> roomList;

NEW_THREAD_FUNC(gameLoop) {
	int roomId = *(int*)param;
	delete param;

	Manager *manager = roomList[roomId]->manager;
	while (1) {
		switch (manager->tmpStep) {
		case CSK_INIT:
			stateProcess(roomId);
			delay(100);
			break;
		case CSK_START:
			stateProcess(roomId);
			delay(100);
			break;
		case CSK_GET: {
			stateProcess(roomId);
			delay(100);

			struct JSON *json;
			json = createJson();
			setStringContent(json, "inst", (char *)"touch card");
			setIntContent(json, "num", 2);

			struct JSON *cardList = createJsonArray();
			for (int i = 0; i < 2; i++) {
				struct JSON *card = createJson();
				Card c = roomList[roomId]->manager->touchCard();
				setIntContent(card, "color", c.color);
				setIntContent(card, "num", c.num);
				setIntContent(card, "content", c.cont);
				setObjectElement(cardList, INT_MAX, card);
			}
			setArrayContent(json, "cards", cardList);
			socketSend(
				roomList[roomId]->users[roomList[roomId]->manager->getPlayer()]->socket,
				writeJson(json));
			freeJson(json);
			delay(100);
			break;
		}
		case CSK_USE:
			break;
		case CSK_DROP:
			break;
		case CSK_END:
			stateProcess(roomId);
			delay(100);
			break;
		case CSK_FINISH: {
			struct JSON *json;
			json = createJson();
			setStringContent(json, "inst", (char *)"over");
			for (auto u : roomList[roomId]->users) {
				socketSend(u->socket, writeJson(json));
			}
			freeJson(json);

			for (auto &u : roomList[roomId]->users) {
				userList[u->userId]->status = US_LOGIN;
			}
			delete roomList[roomId];
			roomList[roomId] = NULL;

			return 0;
		}
		}
	}
	return 0;
}

void stateProcess(int roomId) {
	roomList[roomId]->manager->nextState();

	struct JSON *json;
	json = createJson();
	setStringContent(json, "inst", (char *)"next state");
	for (auto u : roomList[roomId]->users) {
		socketSend(u->socket, writeJson(json));
	}
	freeJson(json);
}
void relayProcess(char *recv, int room, int pos) {
	for (unsigned int i = 0; i < roomList[room]->users.size(); i++) {
		socketSend(roomList[room]->users[i]->socket, recv);
	}
}
void dyingProcess(int room, int pos, int amount) {
	struct JSON *json;
	json = createJson();
	setStringContent(json, "inst", (char *)"dead");
	setIntContent(json, "pos", pos);
	for (auto u : roomList[room]->users) {
		socketSend(u->socket, writeJson(json));
	}
	freeJson(json);

	roomList[room]->manager->deadOne(pos);
}
