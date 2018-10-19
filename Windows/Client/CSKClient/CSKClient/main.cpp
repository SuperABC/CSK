#include "main.h"
#include "killer.h"
#include <vector>

SOCKET client;

enum PROCSTATUS status;

NEW_THREAD_FUNC(msgRecv) {
	char buffer[256] = { 0 };
	char *buf = buffer;
	while (socketReceive(client, buffer, 256) != SG_CONNECTION_FAILED) {
		struct JSON *json = readJson(buf);
		struct JSON_Item *item = getContent(json, "inst");
		std::string inst = item ? item->data.json_string : "";

		if (inst == "login success") {
			loginProcess(json);
		}
		else if (inst == "relogin success") {
			reloginProcess(json);
		}
		else if (inst == "room success") {
			roomProcess(json);
		}
		else if (inst == "choose killer") {
			killerProcess(json);
		}

		else if (inst == "game init") {
			gameInitProcess(json);
		}
		else if (inst == "card init") {
			cardInitProcess(json);
		}
		else if (inst == "next state") {
			nextStateProcess(json);
		}
		else if (inst == "touch card") {
			touchCardProcess(json);
		}
		else if (inst == "game") {
			gameReceiveProcess(json);
		}
		else if (inst == "dead") {
			deadOneProcess(json);
		}
		else if (inst == "over") {
			gameOverProcess(json);
		}
		freeJson(json);
	}
	return 0;
}

void layoutWidget(int status) {
	switch (status) {
	case PS_START:
		layoutStart();
		break;
	case PS_LOGIN:
		layoutLogin();
		break;
	case PS_ROOM:
		layoutRoom();
		break;
	case PS_KILLER:
		layoutKiller();
		break;
	case PS_PLAYING:
		layoutPlaying();
		break;
	}
}
void clearWidget(int status) {
	switch (status) {
	case PS_START:
		clearStart();
		break;
	case PS_LOGIN:
		clearLogin();
		break;
	case PS_ROOM:
		clearRoom();
		break;
	case PS_KILLER:
		clearKiller();
		break;
	case PS_PLAYING:
		clearPlaying();
		break;
	}
}

void sgSetup() {
	initWindow(640, 480, "CS Killer", BIT_MAP);
	initKey();
	initMouse(SG_COORDINATE);

	status = PS_START;
	//client = createClient("47.106.223.165", 4497);
	client = createClient("127.0.0.1", 4497);
	createThread(msgRecv, NULL);
}
void sgLoop() {
	static int pre = -1;
	if (pre != status) {
		clearWidget(pre);
		pre = status;
		layoutWidget(status);
	}
	if (status == PS_PLAYING)tableLoop();
}
