#include "main.h"
#include "user.h"
#include "room.h"
#include "killer.h"

extern vector<User *> userList;
extern vector<Room *> roomList;

void gameProcess(char *recv, int room, int pos) {
	for (unsigned int i = 0; i < roomList[room]->users.size(); i++) {
		if (pos == i)continue;
		socketSend(roomList[room]->users[i]->socket, recv);
	}
}

void changeState(int roomId) {
	STEP tmp = roomList[roomId]->manager->nextState();

	delay(100);
	struct JSON *json;
	json = createJson();
	setStringContent(json, "inst", (char *)"next state");
	for (auto u : roomList[roomId]->users) {
		socketSend(u->socket, writeJson(json));
	}
	freeJson(json);

	if (tmp == CSK_GET) {
		json = createJson();
		setStringContent(json, "inst", (char *)"get card");
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
	}
}
