#include "main.h"
#include "killer.h"
#include <vector>
#include <mutex>

SOCKET client;

enum PROCSTATUS status;

extern vector<int> waitingList;

NEW_THREAD_FUNC(msgRecv) {
	char buffer[256] = { 0 };
	char *buf;
	while (socketReceive(client, buffer, 256) != SG_CONNECTION_FAILED) {
		buf = buffer;
		while (buf[0]) {
			struct JSON *json = readJson(buf);
			struct JSON_Item *item = getContent(json, "inst");
			std::string inst = item ? item->data.json_string : "";

			if (inst == "��¼�ɹ�") {
				loginProcess(json);
				freeJson(json);
			}
			else if (inst == "�����ɹ�") {
				reloginProcess(json);
				freeJson(json);
			}
			else if (inst == "�ӷ��ɹ�") {
				roomProcess(json);
				freeJson(json);
			}
			else if (inst == "���佫��") {
				killerProcess(json);
				freeJson(json);
			}

			if (inst == "�������") {
				waitingList.pop_back();
				freeJson(json);
			}
			else if (inst == "������Ϸ") {
				gameInitProcess(json);
				freeJson(json);
			}
			else if (inst == "��ʼ����") {
				cardInitProcess(json);
				freeJson(json);
			}
			else if (inst == "�׶ν���") {
				nextStateProcess(json);
				freeJson(json);
			}
			else if (inst == "�������") {
				touchCardProcess(json);
				freeJson(json);
			}
			else if (inst == "��ɫ�ҿ�") {
				deadOneProcess(json);
				freeJson(json);
			}
			else if (inst == "��Ϸ����") {
				gameOverProcess(json);
				freeJson(json);
			}

			else if (inst == "ʹ������") {
				createThread(useReceiveProcess, json);
			}
			else if (inst == "����仯") {
				createThread(gradeChangeProcess, json);
			}
			
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
