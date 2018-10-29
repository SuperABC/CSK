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
NEW_THREAD_FUNC(waitGoaway) {
	waitFor("结算完成");
	int action = *(char *)param;

	return 0;
}
void lockTable() {
	//alertInfo("locked", "", 0);
}
NEW_THREAD_FUNC(unlockTable) {
	waitFor("结算完成");
	//alertInfo("unlocked", "", 0);
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

			struct JSON *json = createJson();
			setStringContent(json, "inst", (char *)"使用手牌");
			setStringContent(json, "action", (char *)"study");
			setObjectContent(json, "card", card[0].toJson());
			setIntContent(json, "room", roomId);
			setIntContent(json, "position", manager->getPosition());
			socketSend(client, writeJson(json));

			freeJson(json);
			removePoker(drop);
			break;
		}
		case CC_STAYUP: {
			lockTable();
			createThread(unlockTable, NULL);

			struct JSON *json = createJson();
			setStringContent(json, "inst", (char *)"使用手牌");
			setStringContent(json, "action", (char *)"stayup");
			setObjectContent(json, "card", card[0].toJson());
			setIntContent(json, "room", roomId);
			setIntContent(json, "position", manager->getPosition());
			socketSend(client, writeJson(json));

			freeJson(json);
			removePoker(drop);
			break;
		}
		case CC_SCRIPT:
		case CC_LOLI:
		case CC_VIRUS:
		case CC_LINE:
		case CC_OFFLINE:
		case CC_BOOM:
		case CC_SPINPEN:
		case CC_PTA:
		case CC_CHICKEN:
		case CC_CHAIRMAN:
		case CC_GUARD:
		case CC_KEYBOARD:
		case CC_FLYING:
		case CC_GLASSES:
		case CC_GTX:
		case CC_DBELEPHANT:
		case CC_MOTOR:
		case CC_BUS:
		case CC_ARM:
		case CC_LAKE:
		case CC_MOUNTAIN:
		case CC_BUILDING:
		case CC_FOREST: {
			lockTable();
			createThread(unlockTable, NULL);

			struct JSON *json = createJson();
			setStringContent(json, "inst", (char *)"使用手牌");
			setStringContent(json, "action", (char *)"equip");
			setObjectContent(json, "card", card[0].toJson());
			setIntContent(json, "room", roomId);
			setIntContent(json, "position", manager->getPosition());
			socketSend(client, writeJson(json));

			freeJson(json);
			removePoker(drop);
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
		case CC_PREVENT: 
		case CC_COMMERCE:
		case CC_PARTY:{
			int aim = w->value % manager->getPlayer().size();
			if (manager->getSelf()->getEquipCards().cont[ET_WEAPON].cont == CC_NULL) {
				if (manager->calDist(manager->getPosition(), aim) > 1)break;
			}
			else {
				if (manager->calDist(manager->getPosition(), aim) >
					weaponDist(manager->getSelf()->getEquipCards().cont[ET_WEAPON]))break;
			}

			lockTable();
			createThread(unlockTable, NULL);

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
		case CC_HACK: {
			int aim = w->value % manager->getPlayer().size();
			lockTable();
			createThread(unlockTable, NULL);

			struct JSON *json = createJson();
			setStringContent(json, "inst", (char *)"使用手牌");
			setIntContent(json, "room", roomId);
			setIntContent(json, "position", manager->getPosition());
			setStringContent(json, "action", (char *)"hack");
			setObjectContent(json, "card", card[0].toJson());
			setIntContent(json, "aim", aim);

			socketSend(client, writeJson(json));
			freeJson(json);

			removePoker(drop);
			createThread(waitGoaway, (void *)"hack");
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
NEW_THREAD_FUNC(cardReplyThread) {
	waitFor("结算完成");

	struct JSON *reply = createJson();
	setStringContent(reply, "inst", (char *)"结算完成");
	setIntContent(reply, "room", roomId);
	setIntContent(reply, "position", manager->getPosition());
	socketSend(client, writeJson(reply));
	freeJson(reply);
	return 0;
}
NEW_THREAD_FUNC(goawayReplyThread) {
	return 0;
}
void cardReply(widgetObj *w) {
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
			deleteWidgetByName("reply");
			deleteWidgetByName("cancel");

			struct JSON *reply = createJson();
			setStringContent(reply, "inst", (char *)"打出手牌");
			setIntContent(reply, "room", roomId);
			setIntContent(reply, "position", manager->getPosition());
			setStringContent(reply, "action", (char *)"deny");
			setObjectContent(reply, "card", card[0].toJson());
			socketSend(client, writeJson(reply));
			freeJson(reply);

			removePoker(drop);
			createThread(cardReplyThread, NULL);
			break;
		}
		case CC_STUDY: {
			deleteWidgetByName("reply");
			deleteWidgetByName("cancel");

			struct JSON *reply = createJson();
			setStringContent(reply, "inst", (char *)"打出手牌");
			setIntContent(reply, "room", roomId);
			setIntContent(reply, "position", manager->getPosition());
			setStringContent(reply, "action", (char *)"study");
			setIntContent(reply, "aim", manager->dying);
			setObjectContent(reply, "card", card[0].toJson());
			socketSend(client, writeJson(reply));

			removePoker(drop);
			createThread(cardReplyThread, NULL);
			break;
		}
		case CC_STAYUP: {
			if (manager->dying != manager->getPosition())break;

			deleteWidgetByName("reply");
			deleteWidgetByName("cancel");

			struct JSON *reply = createJson();
			setStringContent(reply, "inst", (char *)"打出手牌");
			setIntContent(reply, "room", roomId);
			setIntContent(reply, "position", manager->getPosition());
			setStringContent(reply, "action", (char *)"study");
			setIntContent(reply, "aim", manager->dying);
			setObjectContent(reply, "card", card[0].toJson());
			socketSend(client, writeJson(reply));

			removePoker(drop);
			createThread(cardReplyThread, NULL);
			break;
		}
		case CC_GOAWAY: {
			createThread(goawayReplyThread, NULL);
		}
		default:
			break;
		}
	}
}
NEW_THREAD_FUNC(preventWoundThread) {
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
	return 0;
}
void preventWound(widgetObj *w) {
	deleteWidgetByName("reply");
	deleteWidgetByName("cancel");

	createThread(preventWoundThread, NULL);
}
void noOperation(widgetObj *w) {
	deleteWidgetByName("reply");
	deleteWidgetByName("cancel");

	struct JSON *reply = createJson();
	setStringContent(reply, "inst", (char *)"结算完成");
	setIntContent(reply, "room", roomId);
	setIntContent(reply, "position", manager->getPosition());
	socketSend(client, writeJson(reply));
	freeJson(reply);
}
void layoutPlaying() {
	widgetObj *selfCard = newWidget(SG_OUTPUT, "card");
	selfCard->size.x = 120;
	selfCard->size.y = 161;
	strcpy((char *)selfCard->content,
		(killerName[manager->getSelf()->getKiller()] + string("\n") +
			std::to_string(manager->getSelf()->getHealth()) + "/" +
			std::to_string(manager->getSelf()->getFull())).data());
	selfCard->tf.size = 32;
	widgetObj *selfWeapon = newWidget(SG_LABEL, "weapon");
	selfWeapon->pos.x = 10;
	selfWeapon->pos.y = 80;
	selfWeapon->size.x = 100;
	selfWeapon->size.y = 20;
	selfWeapon->tf.size = 20;
	widgetObj *selfDefender = newWidget(SG_LABEL, "defender");
	selfDefender->pos.x = 10;
	selfDefender->pos.y = 100;
	selfDefender->size.x = 100;
	selfDefender->size.y = 20;
	selfDefender->tf.size = 20;
	widgetObj *selfVehicle = newWidget(SG_LABEL, "vehicle");
	selfVehicle->pos.x = 10;
	selfVehicle->pos.y = 120;
	selfVehicle->size.x = 100;
	selfVehicle->size.y = 20;
	selfVehicle->tf.size = 20;
	widgetObj *selfBarrier = newWidget(SG_LABEL, "barrier");
	selfBarrier->pos.x = 10;
	selfBarrier->pos.y = 140;
	selfBarrier->size.x = 100;
	selfBarrier->size.y = 20;
	selfBarrier->tf.size = 20;
	widgetObj *selfCombine = newCombinedWidget(5, "self", selfCard,
		selfWeapon, selfDefender, selfVehicle, selfBarrier);
	selfCombine->pos.x = 500;
	selfCombine->pos.y = 300;
	registerWidget(selfCombine);

	int num = manager->getPlayer().size();
	int pos = manager->getPosition();
	for (int i = 1; i < num; i++) {
		widgetObj *enemyCard = newWidget(SG_OUTPUT, "card");
		enemyCard->size.x = 90;
		enemyCard->size.y = 121;
		strcpy((char *)enemyCard->content,
			(killerName[manager->getPlayer()[(pos + i) % num]->getKiller()] + string("\n") +
				std::to_string(manager->getPlayer()[(pos + i) % num]->getHealth()) + "/" +
				std::to_string(manager->getPlayer()[(pos + i) % num]->getFull())).data());
		enemyCard->tf.size = 20;
		enemyCard->mouseUser = (mouseClickUser)aimEnemy;
		enemyCard->value = (pos + i) % num;
		widgetObj *enemyWeapon = newWidget(SG_LABEL, "weapon");
		enemyWeapon->pos.x = 9;
		enemyWeapon->pos.y = 60;
		enemyWeapon->size.x = 72;
		enemyWeapon->size.y = 15;
		enemyWeapon->tf.size = 15;
		widgetObj *enemyDefender = newWidget(SG_LABEL, "defender");
		enemyDefender->pos.x = 9;
		enemyDefender->pos.y = 75;
		enemyDefender->size.x = 72;
		enemyDefender->size.y = 15;
		enemyDefender->tf.size = 15;
		widgetObj *enemyVehicle = newWidget(SG_LABEL, "vehicle");
		enemyVehicle->pos.x = 9;
		enemyVehicle->pos.y = 90;
		enemyVehicle->size.x = 72;
		enemyVehicle->size.y = 15;
		enemyVehicle->tf.size = 15;
		widgetObj *enemyBarrier = newWidget(SG_LABEL, "barrier");
		enemyBarrier->pos.x = 9;
		enemyBarrier->pos.y = 105;
		enemyBarrier->size.x = 72;
		enemyBarrier->size.y = 15;
		enemyBarrier->tf.size = 15;
		widgetObj *enemyCombine = newCombinedWidget(5,
			(string("enemy") + std::to_string((pos + i) % num)).data(), enemyCard,
			enemyWeapon, enemyDefender, enemyVehicle, enemyBarrier);
		enemyCombine->pos.x = 10 + 80 * (i - 1);
		enemyCombine->pos.y = 10;
		registerWidget(enemyCombine);
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

	for (auto k : manager->getPlayer()) {
		k->clearStayup();
	}

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
	if (action == "study") {
		int pos = getContent(json, "position")->data.json_int;
		if (pos == manager->getPosition()) {
			struct JSON *reply = createJson();
			setIntContent(reply, "room", roomId);
			setIntContent(reply, "position", manager->getPosition());

			setStringContent(reply, "inst", (char *)"绩点变化");
			setIntContent(reply, "amount", 1);
			socketSend(client, writeJson(reply));

			waitFor("结算完成");

			setStringContent(reply, "inst", (char *)"结算完成");
			deleteContent(reply, "amount");
			socketSend(client, writeJson(reply));
			freeJson(reply);
		}
	}
	if (action == "stayup") {
		int pos = getContent(json, "position")->data.json_int;
		manager->getPlayer()[pos]->useStayup();
	}
	if (action == "equip") {
		int pos = getContent(json, "position")->data.json_int;
		Card drop = manager->getPlayer()[pos]->addEquip(getContent(json, "card")->data.json_object);
		addEquip(Card(getContent(json, "card")->data.json_object),
			pos, pos - (manager->getPosition() + manager->getPlayer().size()) % manager->getPlayer().size());

		if (pos == manager->getPosition()) {
			struct JSON *reply = createJson();
			setIntContent(reply, "room", roomId);
			setIntContent(reply, "position", manager->getPosition());

			if (drop.cont != CC_NULL) {
				setStringContent(reply, "inst", (char *)"弃置卡牌");
				setObjectContent(reply, "card", drop.toJson());
				socketSend(client, writeJson(reply));

				waitFor("结算完成");
			}

			setStringContent(reply, "inst", (char *)"结算完成");
			deleteContent(reply, "card");
			socketSend(client, writeJson(reply));
			freeJson(reply);
		}
	}
	if (action == "hack") {
		easyWidget(SG_BUTTON, "reply", 300, 300, 80, 24, "打出", (mouseClickUser)cardReply);
		easyWidget(SG_BUTTON, "cancel", 400, 300, 80, 24, "取消", (mouseClickUser)noOperation);
	}
	freeJson(json);
	return 0;
}
NEW_THREAD_FUNC(replyReceiveProcess) {
	struct JSON *json = (struct JSON *)param;
	string action = getContent(json, "action")->data.json_string;

	if (action == "study") {
		int pos = getContent(json, "aim")->data.json_int;
		if (pos == manager->getPosition()) {
			struct JSON *reply = createJson();
			setIntContent(reply, "room", roomId);
			setIntContent(reply, "position", manager->getPosition());

			setStringContent(reply, "inst", (char *)"绩点变化");
			setIntContent(reply, "amount", 1);
			socketSend(client, writeJson(reply));

			waitFor("结算完成");

			setStringContent(reply, "inst", (char *)"结算完成");
			deleteContent(reply, "amount");
			socketSend(client, writeJson(reply));
			freeJson(reply);
		}
	}
	freeJson(json);
	return 0;
}
NEW_THREAD_FUNC(gradeChangeProcess) {
	struct JSON *json = (struct JSON *)param;
	int obj = getContent(json, "position")->data.json_int;
	int amount = getContent(json, "amount")->data.json_int;
	int left;
	if (obj != manager->getPosition()) {
		if (amount < 0)
			left = manager->getPlayer()[obj]->hurtHealth(-amount);
		else
			left = manager->getPlayer()[obj]->recureHealth(amount);
		strcpy((char *)getSubWidget((string("enemy") + std::to_string(obj)).data(), "card")->content,
			(killerName[manager->getPlayer()[obj]->getKiller()] + string("\n") +
				std::to_string(manager->getPlayer()[obj]->getHealth()) + "/" +
				std::to_string(manager->getPlayer()[obj]->getFull())).data());
		getWidgetByName((string("enemy") + std::to_string(obj)).data())->valid = 0;
		if (left < 1) {
			manager->dying = obj;
			easyWidget(SG_BUTTON, "reply", 300, 300, 80, 24, "打出", (mouseClickUser)cardReply);
			easyWidget(SG_BUTTON, "cancel", 400, 300, 80, 24, "取消", (mouseClickUser)noOperation);
		}
	}
	else {
		if (amount < 0)
			left = manager->getSelf()->hurtHealth(-amount);
		else
			left = manager->getSelf()->recureHealth(amount);
		strcpy((char *)getSubWidget("self", "card")->content,
			(killerName[manager->getSelf()->getKiller()] + string("\n") +
				std::to_string(manager->getSelf()->getHealth()) + "/" +
				std::to_string(manager->getSelf()->getFull())).data());
		getWidgetByName("self")->valid = 0;
		if (left < 1) {
			manager->dying = obj;
			easyWidget(SG_BUTTON, "reply", 300, 300, 80, 24, "打出", (mouseClickUser)cardReply);
			easyWidget(SG_BUTTON, "cancel", 400, 300, 80, 24, "取消", (mouseClickUser)noOperation);
		}
	}
	freeJson(json);
	return 0;
}

void tableLoop() {

}
