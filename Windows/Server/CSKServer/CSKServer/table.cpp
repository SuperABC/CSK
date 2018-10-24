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
		case CSK_INIT: {
			stateProcess(roomId);
			delay(100);
			break;
		}
		case CSK_START: {
			manager->waitFor(vector<int>());
			while (manager->isWaiting());
			//等待各个客户端对回合开始阶段的响应

			stateProcess(roomId);
			delay(100);
			break;
		}
		case CSK_GET: {
			manager->waitFor(vector<int>());
			while (manager->isWaiting());
			//等待各个客户端对回合摸牌阶段前的响应

			struct JSON *json;
			json = createJson();
			setStringContent(json, "inst", (char *)"获得手牌");
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

			manager->waitFor(vector<int>());
			while (manager->isWaiting());
			//等待各个客户端对回合摸牌阶段后的响应

			stateProcess(roomId);
			delay(100);
			break;
		}
		case CSK_USE: {
			manager->waitFor(vector<int>());
			while (manager->isWaiting());
			//等待各个客户端对回合出牌阶段前的响应

			/*struct JSON *json;
			json = createJson();
			setStringContent(json, "inst", (char *)"开始出牌");
			setIntContent(json, "position", manager->tmpPlayer);
			for (unsigned int i = 0; i < roomList[roomId]->users.size(); i++) {
				socketSend(roomList[roomId]->users[i]->socket, writeJson(json));
			}
			freeJson(json);*/

			break;
		}
		case CSK_DROP:{
			manager->waitFor(vector<int>());
			while (manager->isWaiting());
			//等待各个客户端对回合弃牌阶段前的响应

			/*struct JSON *json;
			json = createJson();
			setStringContent(json, "inst", (char *)"开始弃牌");
			setIntContent(json, "position", manager->tmpPlayer);
			for (unsigned int i = 0; i < roomList[roomId]->users.size(); i++) {
				socketSend(roomList[roomId]->users[i]->socket, writeJson(json));
			}
			freeJson(json);*/

			break;
		}
		case CSK_END: {
			manager->waitFor(vector<int>());
			while (manager->isWaiting());
			//等待各个客户端对回合结束阶段的响应

			stateProcess(roomId);
			delay(100);
			break;
		}
		case CSK_FINISH: {
			return 0;
		}
		case CSK_ASKING: {
			break;
		}
		}
	}
	return 0;
}

void stateProcess(int room) {
	roomList[room]->manager->nextState();

	struct JSON *json;
	json = createJson();
	setStringContent(json, "inst", (char *)"阶段结束");
	for (auto u : roomList[room]->users) {
		socketSend(u->socket, writeJson(json));
	}
	freeJson(json);
}
void useProcess(struct JSON *json, int room) {
	roomList[room]->manager->waitFor(vector<int>());
	while (roomList[room]->manager->isWaiting());
	//等待各个客户端对回合出牌阶段后的响应
}
void dropProcess(struct JSON *json, int room) {
	roomList[room]->manager->waitFor(vector<int>());
	while (roomList[room]->manager->isWaiting());
	//等待各个客户端对回合弃牌阶段后的响应

	int num = getContent(json, "num")->data.json_int;
	struct JSON *cards = getContent(json, "cards")->data.json_array;
	for (int i = 0; i < num; i++) {
		roomList[room]->manager->dropCard(getElement(cards, i)->data.json_object);
	}
}
void cardProcess(char *recv, int room, int pos, char *cont) {
	for (unsigned int i = 0; i < roomList[room]->users.size(); i++) {
		socketSend(roomList[room]->users[i]->socket, recv);
	}
	struct JSON *json = readJson(recv);
	int level = roomList[room]->manager->waitingLevel();
	if (string(cont) == "prevent") {
		vector<int> waiting;
		waiting.push_back(getContent(json, "aim")->data.json_int);
		roomList[room]->manager->waitFor(waiting);
		roomList[room]->manager->tmpCard.push_back(Card(getContent(json, "card")->data.json_object));
	}
	while (roomList[room]->manager->isWaiting(level));
	//等待各个客户端对该出牌的响应

	struct JSON *ret = createJson();
	setStringContent(ret, "inst", (char *)"结算完成");
	socketSend(roomList[room]->users[pos]->socket, writeJson(ret));
	freeJson(ret);
	for (auto c : roomList[room]->manager->tmpCard) {
		roomList[room]->manager->dropCard(c);
	}

	if (roomList[room]->manager->tmpStep == CSK_FINISH) {
		struct JSON *json;
		json = createJson();
		setStringContent(json, "inst", (char *)"游戏结束");
		for (auto u : roomList[room]->users) {
			socketSend(u->socket, writeJson(json));
		}
		freeJson(json);

		for (auto &u : roomList[room]->users) {
			userList[u->userId]->status = US_LOGIN;
		}
		delete roomList[room];
		roomList[room] = NULL;
	}
}
void replyProcess(char *recv, int room, int pos, char *cont) {
	for (unsigned int i = 0; i < roomList[room]->users.size(); i++) {
		socketSend(roomList[room]->users[i]->socket, recv);
	}

	struct JSON *json = readJson(recv);
	int level = roomList[room]->manager->waitingLevel();
	if (string(cont) == "prevent") {
		roomList[room]->manager->waitFor(vector<int>());
		roomList[room]->manager->tmpCard.push_back(Card(getContent(json, "card")->data.json_object));
	}
	while (roomList[room]->manager->isWaiting(level));
	//等待各个客户端对该出牌的响应

	struct JSON *ret = createJson();
	setStringContent(ret, "inst", (char *)"结算完成");
	socketSend(roomList[room]->users[pos]->socket, writeJson(ret));
	freeJson(ret);
}
void doneProcess(int room, int pos) {
	roomList[room]->manager->responseCome(pos);
}
void gradeProcess(char *recv, int room, int pos, int amount) {
	for (unsigned int i = 0; i < roomList[room]->users.size(); i++) {
		socketSend(roomList[room]->users[i]->socket, recv);
	}
	if (roomList[room]->manager->gradeChange(pos, amount) < 1) {
		int level = roomList[room]->manager->waitingLevel();
		roomList[room]->manager->waitFor(vector<int>());
		while (roomList[room]->manager->isWaiting(level));
		//等待各个客户端对濒临挂科的响应

		if (roomList[room]->manager->gradeChange(pos, 0) < 1) {
			struct JSON *json;
			json = createJson();
			setStringContent(json, "inst", (char *)"角色挂科");
			setIntContent(json, "pos", pos);
			for (auto u : roomList[room]->users) {
				socketSend(u->socket, writeJson(json));
			}
			freeJson(json);

			roomList[room]->manager->deadOne(pos);
		}
	}

	int level = roomList[room]->manager->waitingLevel();
	roomList[room]->manager->waitFor(vector<int>());
	while (roomList[room]->manager->isWaiting(level));
	//等待各个客户端对损失绩点的响应

	struct JSON *ret = createJson();
	setStringContent(ret, "inst", (char *)"结算完成");
	socketSend(roomList[room]->users[pos]->socket, writeJson(ret));
	freeJson(ret);
}

