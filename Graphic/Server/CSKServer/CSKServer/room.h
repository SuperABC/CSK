#pragma once
#include "main.h"
#include "user.h"
#include <vector>

enum ROOMSTATUS {
	RS_WAITING,
	RS_PLAYING
};

class Room {
public:
	ROOMSTATUS status;
	int roomId;
	std::vector<User *> users;

	Room(int roomId) : status(RS_WAITING), roomId(roomId) {}
	bool waiting() {
		return status == RS_WAITING && users.size() < 8;
	}
	void comein(User *user) {
		user->status = US_ROOM;
		user->roomId = roomId;
		users.push_back(user);

		if (users.size() == 2) {
			status = RS_PLAYING;
			tableInit(roomId);
		}
	}
};
