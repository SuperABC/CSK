#include "main.h"
#include "killer.h"
#include "card.h"
#include "poker.h"
#include "manager.h"
#include <mutex>

extern SOCKET client;
extern int userId, roomId;

extern enum PROCSTATUS status;

extern const char *killerName[];
extern const char *killerDetail[];

Manager *manager;
extern vector<Poker> pokerList;

vector<int> waitingList;

void waitFor(const char *inst) {
	unsigned int level = waitingList.size();
	waitingList.push_back(0);
	while (waitingList.size() > level);
}
void lockTable() {
	//alertInfo("locked", "", 0);
	getWidgetByName("use")->visible = false;
	getWidgetByName("finish")->visible = false;
}
NEW_THREAD_FUNC(unlockTable) {
	waitFor("结算完成");
	//alertInfo("unlocked", "", 0);
	getWidgetByName("use")->visible = true;
	getWidgetByName("finish")->visible = true;
	return 0;
}

void useCard(widgetObj *w) {
	vector<Card> card;
	vector<int> drop;
	for (unsigned int i = 0; i < pokerList.size(); i++) {
		if (pokerList[i].widget->hide) {
			card.push_back(pokerList[i]);
			drop.push_back(i);
		}
	}
	if (card.size() == 1) {
		switch (card[0].cont) {
		case CC_STUDY: {
			lockTable();
			createThread(unlockTable, NULL);

			int aim = manager->getPosition();
			struct JSON *json = createJson();
			setStringContent(json, "inst", (char *)"绩点变化");
			setIntContent(json, "amount", 1);
			setIntContent(json, "room", roomId);
			setIntContent(json, "position", manager->getPosition());
			setStringContent(json, "action", (char *)"study");
			setObjectContent(json, "card", card[0].toJson());
			setIntContent(json, "aim", aim);

			socketSend(client, writeJson(json));
			freeJson(json);

			removePoker(drop);
			break;
		}
		default:
			break;
		}
	}
}
void aimEnemy(widgetObj *w) {
	vector<Card> card;
	vector<int> drop;
	for (unsigned int i = 0; i < pokerList.size(); i++) {
		if (pokerList[i].widget->hide) {
			card.push_back(pokerList[i]);
			drop.push_back(i);
		}
	}
	if (card.size() == 1) {
		switch (card[0].cont) {
		case CC_PREVENT: {
			lockTable();
			createThread(unlockTable, NULL);

			int aim = w->value % manager->getPlayer().size();
			struct JSON *json = createJson();
			setStringContent(json, "inst", (char *)"使用手牌");
			setIntContent(json, "room", roomId);
			setIntContent(json, "position", manager->getPosition());
			setStringContent(json, "action", (char *)"prevent");
			setObjectContent(json, "card", card[0].toJson());
			setIntContent(json, "aim", aim);

			socketSend(client, writeJson(json));
			freeJson(json);

			removePoker(drop);
			break;
		}
		default:
			break;
		}
	}
}
void finishUse(widgetObj *w) {
	struct JSON *ret = createJson();

	setStringContent(ret, "inst", (char *)"出牌结束");
	setIntContent(ret, "room", roomId);
	socketSend(client, writeJson(ret));

	freeJson(ret);
	setWidgetTop("use");
	deleteWidgetByName("use");
	setWidgetTop("finish");
	deleteWidgetByName("finish");
}
void dropCard(widgetObj *w) {
	unsigned int max = manager->getSelf()->getHealth();

	vector<int> list;
	struct JSON *cards = createJsonArray();
	if (pokerList.size() > max) {
		for (unsigned int i = 0; i < pokerList.size(); i++) {
			if (pokerList[i].widget->hide == 0)max--;
			else list.push_back(i);
		}
		if (max != 0)return;

		for (auto i : list) {
			setObjectElement(cards, -1, pokerList[i].toJson());
		}
		removePoker(list);
	}

	struct JSON *ret = createJson();

	setStringContent(ret, "inst", (char *)"弃牌结束");
	setIntContent(ret, "room", roomId);
	setIntContent(ret, "num", list.size());
	setArrayContent(ret, "cards", cards);
	socketSend(client, writeJson(ret));

	freeJson(ret);
	setWidgetTop("drop");
	deleteWidgetByName("drop");
}
void cardReply(widgetObj *w) {
	deleteWidgetByName("deny");
	deleteWidgetByName("cancel");

	vector<Card> card;
	vector<int> drop;
	for (unsigned int i = 0; i < pokerList.size(); i++) {
		if (pokerList[i].widget->hide) {
			card.push_back(pokerList[i]);
			drop.push_back(i);
		}
	}
	if (card.size() == 1) {
		switch (card[0].cont) {
		case CC_DENY: {
			struct JSON *reply = createJson();
			setIntContent(reply, "room", roomId);
			setIntContent(reply, "position", manager->getPosition());

			setStringContent(reply, "inst", (char *)"打出手牌");
			setStringContent(reply, "action", (char *)"deny");
			setObjectContent(reply, "card", card[0].toJson());
			socketSend(client, writeJson(reply));

			removePoker(drop);
			waitFor("结算完成");

			setStringContent(reply, "inst", (char *)"结算完成");
			deleteContent(reply, "action");
			deleteContent(reply, "card");
			socketSend(client, writeJson(reply));
			freeJson(reply);
			break;
		}
		default:
			break;
		}
	}
}
void preventWound(widgetObj *w) {
	deleteWidgetByName("deny");
	deleteWidgetByName("cancel");

	struct JSON *reply = createJson();
	setIntContent(reply, "room", roomId);
	setIntContent(reply, "position", manager->getPosition());

	setStringContent(reply, "inst", (char *)"绩点变化");
	setIntContent(reply, "amount", -1);
	socketSend(client, writeJson(reply));

	waitFor("结算完成");

	setStringContent(reply, "inst", (char *)"结算完成");
	deleteContent(reply, "amount");
	socketSend(client, writeJson(reply));
	freeJson(reply);
}
void noOperation(widgetObj *w) {
	struct JSON *reply = createJson();
	setStringContent(reply, "inst", (char *)"结算完成");
	setIntContent(reply, "room", roomId);
	setIntContent(reply, "position", manager->getPosition());
	socketSend(client, writeJson(reply));
	freeJson(reply);
}
void layoutPlaying() {
	easyWidget(SG_OUTPUT, "self", 500, 300, 120, 160,
		(killerName[manager->getSelf()->getKiller()] + string("\n") +
		std::to_string(manager->getSelf()->getHealth()) + "/" +
		std::to_string(manager->getSelf()->getFull())).data(), NULL);
	getWidgetByName("self")->tf.size = 32;
	int num = manager->getPlayer().size();
	int pos = manager->getPosition();
	for (int i = 1; i < num; i++) {
		easyWidget(SG_OUTPUT,
			(string("enemy") + std::to_string((pos + i) % num)).data(),
			10 + 80 * (i - 1), 10, 60, 80,
			(killerName[manager->getPlayer()[(pos + i) % num]->getKiller()] + string("\n") +
				std::to_string(manager->getPlayer()[(pos + i) % num]->getHealth()) + "/" +
				std::to_string(manager->getPlayer()[(pos + i) % num]->getFull())).data(),
			(mouseClickUser)aimEnemy);
		getWidgetByName((string("enemy") + std::to_string((pos + i) % num)).data())->value = (pos + i) % num;
	}
	easyWidget(SG_LABEL, "instruction", 10, 450, 480, 20, "", NULL);
	getWidgetByName("instruction")->tf.size = 16;

	for (int i = 0; i < 4; i++) {
		setWidgetTop((string("poker") + std::to_string(i)).data());
	}
}
void clearPlaying() {
	if (getWidgetByName("self"))deleteWidgetByName("self");
	if (getWidgetByName("enemy0"))deleteWidgetByName("enemy0");
	if (getWidgetByName("enemy1"))deleteWidgetByName("enemy1");
	if (getWidgetByName("enemy2"))deleteWidgetByName("enemy2");
	if (getWidgetByName("enemy3"))deleteWidgetByName("enemy3");
	if (getWidgetByName("enemy4"))deleteWidgetByName("enemy4");
	if (getWidgetByName("enemy5"))deleteWidgetByName("enemy5");
	if (getWidgetByName("enemy6"))deleteWidgetByName("enemy6");
	if (getWidgetByName("enemy7"))deleteWidgetByName("enemy7");
	if (getWidgetByName("instruction"))deleteWidgetByName("instruction");

	vector<int> drop;
	for (unsigned int i = 0; i < pokerList.size(); i++) {
		drop.push_back(i);
	}
	removePoker(drop);
	if (getWidgetByName("use"))deleteWidgetByName("use");
	if (getWidgetByName("finish"))deleteWidgetByName("finish");
	if (getWidgetByName("drop"))deleteWidgetByName("drop");
}

void gameInitProcess(struct JSON *json) {
	int num = getContent(json, "num")->data.json_int;
	struct JSON *killers = getContent(json, "killers")->data.json_array;
	vector<Killer *>list;
	for (int i = 0; i < num; i++) {
		struct JSON *obj = getElement(killers, i)->data.json_object;
		Killer * k = Killer::newKiller((KILLER)getContent(obj, "killer")->data.json_int, i);
		k->setName(getContent(obj, "user")->data.json_string);
		list.push_back(k);
	}
	manager = new Manager(list, getContent(json, "position")->data.json_int);

	status = PS_PLAYING;
}
void cardInitProcess(struct JSON *json) {
	struct JSON *cards = getContent(json, "cards")->data.json_array;

	for (int i = 0; i < 4; i++) {
		Card c;
		struct JSON *card = getElement(cards, i)->data.json_object;
		c.color = (Color)getContent(card, "color")->data.json_int;
		c.num = getContent(card, "num")->data.json_int;
		c.cont = (Content)getContent(card, "content")->data.json_int;
		
		addPoker(Poker(c));
	}
}
void nextStateProcess(struct JSON *json) {
	STEP step = manager->nextState();

	if (!manager->myTurn())return;
	struct JSON *ret = createJson();
	switch (step) {
	case CSK_START:
	case CSK_GET:
	case CSK_END:
		break;
	case CSK_USE:
		//waitFor("开始出牌");
		easyWidget(SG_BUTTON, "finish", 400, 300, 80, 24, "结束", (mouseClickUser)finishUse);
		easyWidget(SG_BUTTON, "use", 300, 300, 80, 24, "使用", (mouseClickUser)useCard);
		break;
	case CSK_DROP:
		//waitFor("开始弃牌");
		easyWidget(SG_BUTTON, "drop", 400, 300, 80, 24, "弃牌", (mouseClickUser)dropCard);
		break;
	default:
		break;
	}
	freeJson(ret);
}
void touchCardProcess(struct JSON *json) {
	struct JSON *cards = getContent(json, "cards")->data.json_array;
	int num = getContent(json, "num")->data.json_int;

	for (int i = 0; i < num; i++) {
		Card c;
		struct JSON *card = getElement(cards, i)->data.json_object;
		c.color = (Color)getContent(card, "color")->data.json_int;
		c.num = getContent(card, "num")->data.json_int;
		c.cont = (Content)getContent(card, "content")->data.json_int;

		addPoker(Poker(c));
	}
}
void deadOneProcess(struct JSON *json) {
	int pos = getContent(json, "pos")->data.json_int;

	if (pos == manager->getPosition()) {
		alertInfo("您挂科了！", "游戏提示", ALERT_ICON_INFORMATION);
	}
	else {

	}
	manager->deadOne(pos);
}
void gameOverProcess(struct JSON *json) {
	alertInfo("游戏结束！", "游戏提示", ALERT_ICON_INFORMATION);

	status = PS_LOGIN;
}

NEW_THREAD_FUNC(useReceiveProcess) {
	struct JSON *json = (struct JSON *)param;
	string action = getContent(json, "action")->data.json_string;

	if (action == "prevent") {
		int aim = getContent(json, "aim")->data.json_int;
		if (aim == manager->getPosition()) {
			easyWidget(SG_BUTTON, "reply", 300, 300, 80, 24, "打出", (mouseClickUser)cardReply);
			easyWidget(SG_BUTTON, "cancel", 400, 300, 80, 24, "取消", (mouseClickUser)preventWound);
		}
	}
	freeJson(json);
	return 0;
}
NEW_THREAD_FUNC(gradeChangeProcess) {
	struct JSON *json = (struct JSON *)param;
	int obj = getContent(json, "position")->data.json_int;
	int amount = getContent(json, "amount")->data.json_int;
	if (obj != manager->getPosition()) {
		if (amount < 0)
			manager->getPlayer()[obj]->hurtHealth(-amount);
		else
			manager->getPlayer()[obj]->recureHealth(amount);
		strcpy((char *)getWidgetByName((string("enemy") + std::to_string(obj)).data())->content,
			(killerName[manager->getPlayer()[obj]->getKiller()] + string("\n") +
				std::to_string(manager->getPlayer()[obj]->getHealth()) + "/" +
				std::to_string(manager->getPlayer()[obj]->getFull())).data());
		getWidgetByName((string("enemy") + std::to_string(obj)).data())->valid = 0;
	}
	else {
		if (amount < 0)
			manager->getSelf()->hurtHealth(-amount);
		else
			manager->getSelf()->recureHealth(amount);
		strcpy((char *)getWidgetByName("self")->content,
			(killerName[manager->getSelf()->getKiller()] + string("\n") +
				std::to_string(manager->getSelf()->getHealth()) + "/" +
				std::to_string(manager->getSelf()->getFull())).data());
		getWidgetByName("self")->valid = 0;
	}
	freeJson(json);
	return 0;
}

void tableLoop() {

}
