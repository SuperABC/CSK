#include "winsgl.h"

SOCKET server;

void layoutWidgets() {
	easyWidget(SG_LABEL, "address", 40, 40, 0, 0, "·þÎñÆ÷¶Ë¿Ú£º4497", NULL);
	easyWidget(SG_OUTPUT, "connection", 40, 80, 560, 360, "", NULL);
}

void sgSetup() {
	initWindow(640, 480, "CSK Server", BIT_MAP);
	server = createServer(4497);

	layoutWidgets();
}
void sgLoop() {
	static int i = 0;
	debugf("%d\n", i++);
	return;
}