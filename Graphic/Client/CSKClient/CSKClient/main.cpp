#include "winsgl.h"
#include "main.h"

SOCKET client;
int userId, roomId;

enum PROCSTATUS status;

void login(widgetObj *w) {
	widgetObj *input = getWidgetByName("input");

	socketSend(client, (std::string("login ") + (char *)input->content).data());
	status = PS_ENTERING;
}

void layoutWidget(int status) {
	switch (status) {
	case PS_START:
		easyWidget(SG_INPUT, "input", 40, 40, 440, 24, "", NULL);
		easyWidget(SG_BUTTON, "login", 520, 40, 80, 24, "登录", (mouseClickUser)login);
		break;
	case PS_ENTERING:
		easyWidget(SG_LABEL, "waiting", 0, 0, 120, 20, "等待进入游戏...", NULL);
		break;
	}
}
void clearWidget(int status) {
	switch (status) {
	case PS_START:
		if (getWidgetByName("input"))deleteWidgetByName("input");
		if (getWidgetByName("login"))deleteWidgetByName("login");
		break;
	case PS_ENTERING:
		if (getWidgetByName("waiting"))deleteWidgetByName("waiting");
		break;
	}
}
void msgRecv() {
	char buffer[256] = { 0 };
	char *buf = buffer;
	while (socketReceive(client, buffer, 256) != SG_CONNECTION_FAILED) {
		struct JSON *json = readJson(buf);
		struct JSON_Item *item = getContent(json, "inst");
		std::string inst = item ? item->data.json_string : "";
		if (inst == "login success") {
			userId = getContent(json, "id")->data.json_int;
			socketSend(client, (std::string("room ") + std::to_string(userId)).data());
		}
		else if (inst == "relogin success") {
			userId = getContent(json, "id")->data.json_int;
		}
		else if (inst == "room success") {
			roomId = getContent(json, "id")->data.json_int;
		}
		else if (inst == "choose killer") {
			status = PS_KILLER;
		}
		freeJson(json);
	}
}

void sgSetup() {
	initWindow(640, 480, "CS Killer", BIT_MAP);
	initKey();
	initMouse(SG_COORDINATE);

	status = PS_START;
	client = createClient("127.0.0.1", 4497);
	createThread(msgRecv);
}
void sgLoop() {
	static int pre = -1;
	if (pre != status) {
		clearWidget(pre);
		pre = status;
		layoutWidget(status);
	}
}
