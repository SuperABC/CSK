#include "winsgl.h"

SOCKET client;
int userId;

void connectServer() {
	char idStr[8];
	socketSend(client, "login");
	socketReceive(client, idStr, 8);
	userId = atoi(idStr);
}
void sgSetup() {
	initWindow(640, 480, "CS Killer", BIT_MAP);
	initKey();
	initMouse(SG_COORDINATE);
	client = createClient("127.0.0.1", 4497);

	connectServer();
	connectServer();
	connectServer();
	connectServer();
}
void sgLoop() {

}