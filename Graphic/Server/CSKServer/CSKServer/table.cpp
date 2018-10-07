#include "main.h"
#include "user.h"
#include "room.h"
#include "killer.h"
#include "manager.h"

extern vector<User *> userList;
extern vector<Room *> roomList;

void gameProcess(char *recv, int room, int pos) {
	for (unsigned int i = 0; i < roomList[room]->users.size(); i++) {
		if (pos == i)continue;
		socketSend(roomList[room]->users[i]->socket, recv);
	}
}
