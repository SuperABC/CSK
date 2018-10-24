#pragma once
#include "winsgl.h"

enum PROCSTATUS {
	PS_START,
	PS_LOGIN,
	PS_ROOM,
	PS_WAITING,
	PS_KILLER,
	PS_PLAYING
};

void loginProcess(struct JSON *json);
void reloginProcess(struct JSON *json);
void roomProcess(struct JSON *json);
void killerProcess(struct JSON *json);

void gameInitProcess(struct JSON *json);
void cardInitProcess(struct JSON *json);
void nextStateProcess(struct JSON *json);
void touchCardProcess(struct JSON *json);
void deadOneProcess(struct JSON *json);
void gameOverProcess(struct JSON *json);

NEW_THREAD_FUNC(useReceiveProcess);
NEW_THREAD_FUNC(gradeChangeProcess);

void layoutStart();
void clearStart();
void layoutLogin();
void clearLogin();
void layoutRoom();
void clearRoom();
void layoutWaiting();
void clearWaiting();
void layoutKiller();
void clearKiller();
void layoutPlaying();
void clearPlaying();

void lockTable();
void unlockTable();
void tableLoop();
