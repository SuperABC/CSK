#include "main.h"
#include "killer.h"
#include <vector>

SOCKET client;

enum PROCSTATUS status;

NEW_THREAD_FUNC(msgRecv) {
	char buffer[256] = { 0 };
	char *buf;
	while (socketReceive(client, buffer, 256) != SG_CONNECTION_FAILED) {
		buf = buffer;
		while (buf[0]) {
			struct JSON *json = readJson(buf);
			struct JSON_Item *item = getContent(json, "inst");
			std::string inst = item ? item->data.json_string : "";

			if (inst == "登录成功") {
				loginProcess(json);
			}
			else if (inst == "重连成功") {
				reloginProcess(json);
			}
			else if (inst == "加房成功") {
				roomProcess(json);
			}
			else if (inst == "发武将牌") {
				killerProcess(json);
			}

			else if (inst == "进入游戏") {
				gameInitProcess(json);
			}
			else if (inst == "初始摸牌") {
				cardInitProcess(json);
			}
			else if (inst == "阶段结束") {
				nextStateProcess(json);
			}
			else if (inst == "回合摸牌") {
				touchCardProcess(json);
			}
			else if (inst == "使用手牌") {
				useReceiveProcess(json);
			}
			else if (inst == "结算完成") {
				actionDoneProcess(json);
			}
			else if (inst == "绩点变化") {
				gradeChangeProcess(json);
			}
			else if (inst == "角色挂科") {
				deadOneProcess(json);
			}
			else if (inst == "游戏结束") {
				gameOverProcess(json);
			}
			freeJson(json);

			buf += strlen(buf) + 1;
		}

		memset(buffer, 0, 256);
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
