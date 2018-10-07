#include "main.h"
#include "killer.h"
#include "card.h"
#include "poker.h"
#include "manager.h"

extern enum PROCSTATUS status;
extern const char *killerName[];

Manager *manager;

extern bool enTable;

void gameInitProcess(struct JSON *json) {
	int num = getContent(json, "num")->data.json_int;
	struct JSON *killers = getContent(json, "killers")->data.json_array;
	vector<Killer *>list;
	for (int i = 0; i < num; i++) {
		struct JSON *obj = getElement(killers, i)->data.json_object;
		Killer * k = new Killer((KILLER)getContent(obj, "killer")->data.json_int, i);
		k->setName(getContent(obj, "user")->data.json_string);
		list.push_back(k);
	}
	manager = new Manager(list, getContent(json, "position")->data.json_int);

	status = PS_GAMING;
}
void cardInitProcess(struct JSON *json) {
	struct JSON *cards = getContent(json, "cards")->data.json_array;
	
	while (!enTable);
	for (int i = 0; i < 4; i++) {
		Card c;
		struct JSON *card = getElement(cards, i)->data.json_object;
		c.color = (Color)getContent(card, "color")->data.json_int;
		c.num = getContent(card, "num")->data.json_int;
		c.cont = (Content)getContent(card, "content")->data.json_int;
		
		addPoker(Poker(c));
	}
}

void layoutGaming() {
	easyWidget(SG_OUTPUT, "self", 500, 300, 120, 160,
		killerName[manager->getSelf()->getKiller()], NULL);
	getWidgetByName("self")->tf.size = 32;
	int num = manager->getPlayer().size();
	int pos = manager->getPosition();
	for (int i = 1; i < num; i++) {
		easyWidget(SG_OUTPUT,
			(string("enemy") + std::to_string((pos + i) % num)).data(),
			10 + 80 * (i - 1), 10, 60, 80,
			killerName[manager->getPlayer()[(pos + i) % num]->getKiller()], NULL);
	}
	easyWidget(SG_LABEL, "instruction", 10, 450, 480, 20, "", NULL);
	getWidgetByName("instruction")->tf.size = 16;
}
void clearGaming() {
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
}

void tableLoop() {

}
