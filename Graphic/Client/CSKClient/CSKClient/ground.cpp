#include "main.h"
#include <vector>

using std::vector;
using std::string;

extern SOCKET client;
int userId, roomId;

extern enum PROCSTATUS status;

extern const char *killerName[];
extern const char *killerDetail[];
vector<int> range;

void mouseMoveKiller(widgetObj *w, int x, int y) {
	if (inWidget(w, x, y)) {
		widgetObj *detail = getWidgetByName("detail");
		strcpy((char *)detail->content, killerDetail[range[w->value]]);
		detail->valid = 0;
	}
	mouseMoveDefault(w, x, y);
}

void loginPlat(widgetObj *w) {
	widgetObj *user = getWidgetByName("user");
	widgetObj *password = getWidgetByName("password");

	struct JSON *json = createJson();
	setStringContent(json, "inst", (char *)"login");
	setStringContent(json, "name", (char *)user->content);
	setStringContent(json, "password", (char *)password->content);
	socketSend(client, writeJson(json));
	freeJson(json);
}
void selectKiller(widgetObj *w) {
	struct JSON *json = createJson();
	setStringContent(json, "inst", (char *)"killer");
	setIntContent(json, "id", userId);
	setIntContent(json, "killer", range[w->value]);
	socketSend(client, writeJson(json));
	freeJson(json);
}

void loginProcess(struct JSON *json) {
	userId = getContent(json, "id")->data.json_int;

	struct JSON *ret = createJson();
	setStringContent(ret, "inst", (char *)"room");
	setIntContent(ret, "id", userId);
	socketSend(client, writeJson(ret));
	freeJson(ret);

	status = PS_ENTERING;
}
void reloginProcess(struct JSON *json) {
	userId = getContent(json, "id")->data.json_int;
	int s = getContent(json, "status")->data.json_int;
	switch (s) {
	case 0:
	case 1:
		status = PS_ENTERING;
		break;
	case 2:
		status = PS_WAITING;
		break;
	case 3:
		status = PS_KILLER;
		break;
	case 4:
		status = PS_GAMING;
		break;
	}
}
void roomProcess(struct JSON *json) {
	roomId = getContent(json, "id")->data.json_int;
}
void killerProcess(struct JSON *json) {
	status = PS_KILLER;
	struct JSON *list = getContent(json, "list")->data.json_array;
	struct JSON_Item *item = NULL;
	for (int i = 0; (item = getElement(list, i)) != NULL; i++) {
		range.push_back(item->data.json_int);
	}
}

void layoutStart() {
	easyWidget(SG_LABEL, "userLabel", 200, 160, 80, 24, "用户名：", NULL);
	easyWidget(SG_LABEL, "passwordLabel", 200, 240, 80, 24, "密码：", NULL);
	easyWidget(SG_INPUT, "user", 280, 160, 160, 24, "", NULL);
	easyWidget(SG_INPUT, "password", 280, 240, 160, 24, "", NULL);
	easyWidget(SG_BUTTON, "login", 200, 320, 240, 24, "登录", (mouseClickUser)loginPlat);
}
void clearStart() {
	if (getWidgetByName("userLabel"))deleteWidgetByName("userLabel");
	if (getWidgetByName("passwordLabel"))deleteWidgetByName("passwordLabel");
	if (getWidgetByName("user"))deleteWidgetByName("user");
	if (getWidgetByName("password"))deleteWidgetByName("password");
	if (getWidgetByName("login"))deleteWidgetByName("login");
}
void layoutEntering() {
	easyWidget(SG_LABEL, "waiting", 0, 0, 120, 20, "等待进入游戏...", NULL);
}
void clearEntering() {
	if (getWidgetByName("waiting"))deleteWidgetByName("waiting");
}
void layoutWaiting() {

}
void clearWaiting() {

}
void layoutKiller() {
	easyWidget(SG_BUTTON, "killer1", 40, 40, 60, 80, killerName[range[0]], (mouseClickUser)selectKiller);
	widgetObj *killer1 = getWidgetByName("killer1");
	killer1->value = 0;
	killer1->mouseIn = killer1->mouseOut = (mouseMoveCall)mouseMoveKiller;
	easyWidget(SG_BUTTON, "killer2", 120, 40, 60, 80, killerName[range[1]], (mouseClickUser)selectKiller);
	widgetObj *killer2 = getWidgetByName("killer2");
	killer2->value = 1;
	killer2->mouseIn = killer2->mouseOut = (mouseMoveCall)mouseMoveKiller;
	easyWidget(SG_BUTTON, "killer3", 200, 40, 60, 80, killerName[range[2]], (mouseClickUser)selectKiller);
	widgetObj *killer3 = getWidgetByName("killer3");
	killer3->value = 2;
	killer3->mouseIn = killer3->mouseOut = (mouseMoveCall)mouseMoveKiller;
	getWidgetByName("killer3")->value = 2;
	easyWidget(SG_BUTTON, "killer4", 280, 40, 60, 80, killerName[range[3]], (mouseClickUser)selectKiller);
	widgetObj *killer4 = getWidgetByName("killer4");
	killer4->value = 3;
	killer4->mouseIn = killer4->mouseOut = (mouseMoveCall)mouseMoveKiller;
	easyWidget(SG_BUTTON, "killer5", 360, 40, 60, 80, killerName[range[4]], (mouseClickUser)selectKiller);
	widgetObj *killer5 = getWidgetByName("killer5");
	killer5->value = 4;
	killer5->mouseIn = killer5->mouseOut = (mouseMoveCall)mouseMoveKiller;
	easyWidget(SG_OUTPUT, "detail", 40, 160, 560, 280, "", NULL);
}
void clearKiller() {
	if (getWidgetByName("killer1"))deleteWidgetByName("killer1");
	if (getWidgetByName("killer2"))deleteWidgetByName("killer2");
	if (getWidgetByName("killer3"))deleteWidgetByName("killer3");
	if (getWidgetByName("killer4"))deleteWidgetByName("killer4");
	if (getWidgetByName("killer5"))deleteWidgetByName("killer5");
	if (getWidgetByName("detail"))deleteWidgetByName("detail");
}

