#pragma once
#include "winsgl.h"

enum PROCSTATUS {
	PS_START,
	PS_ENTERING,
	PS_WAITING,
	PS_KILLER,
	PS_GAMING
};

void loginProcess(struct JSON *json);
void reloginProcess(struct JSON *json);
void roomProcess(struct JSON *json);
void killerProcess(struct JSON *json);

void gameInitProcess(struct JSON *json);
void cardInitProcess(struct JSON *json);
void getCardProcess(struct JSON *json);
void nextStateProcess(struct JSON *json);

void layoutStart();
void clearStart();
void layoutEntering();
void clearEntering();
void layoutWaiting();
void clearWaiting();
void layoutKiller();
void clearKiller();
void layoutGaming();
void clearGaming();

void tableLoop();
