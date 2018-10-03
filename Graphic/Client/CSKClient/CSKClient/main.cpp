#include "winsgl.h"
#include "main.h"

SOCKET client;
int userId, roomId;

enum PROCSTATUS status;

void layoutWidget() {
	easyWidget(SG_LABEL, "waiting", 0, 0, 120, 20, "等待进入游戏...", NULL);
}
void connectServer() {
	char userStr[8], roomStr[8];
	client = createClient("127.0.0.1", 4497);
	socketSend(client, "login SuperGP4");
	socketReceive(client, userStr, 8);
	userId = atoi(userStr);
	socketSend(client, (std::string("room ") + userStr).data());
	socketReceive(client, roomStr, 8);
	roomId = atoi(roomStr);
}
void msgRecv() {
	char buf[256] = { 0 };
	while (socketReceive(client, buf, 256) != SG_CONNECTION_FAILED) {
		status = PS_KILLER;
		debugf(buf);
		struct JSON *json = readJson(buf);
		freeJson(json);
	}
}

void sgSetup() {
	initWindow(640, 480, "CS Killer", BIT_MAP);
	initKey();
	initMouse(SG_COORDINATE);

	status = PS_ENTERING;
	layoutWidget();
	connectServer();
	createThread(msgRecv);
}
void sgLoop() {
	if(status == PS_KILLER)
		if(getWidgetByName("waiting"))deleteWidgetByName("waiting");
}
