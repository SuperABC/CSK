#pragma once
#include "main.h"
#include "user.h"
#include "killer.h"
#include "manager.h"
#include <vector>

enum ROOMSTATUS {
	RS_WAITING,
	RS_PLAYING
};

class Room {
public:
	ROOMSTATUS status;
	int roomId;
	vector<Roommate *> users;

	Manager *manager;

	Room(int roomId) : status(RS_WAITING), roomId(roomId) {}
	bool waiting() {
		return status == RS_WAITING && users.size() < 8;
	}
	void comein(User *user) {
		user->status = US_ROOM;
		user->roomId = roomId;
		users.push_back(new Roommate(user));

		if (users.size() == 3) {
			status = RS_PLAYING;
			chooseKiller(roomId);
		}
	}
	void assign(int id, enum KILLER killer) {
		for (auto &m : users) {
			if (m->userId == id) {
				m->killer = killer;
				break;
			}
		}
		for (auto m : users) {
			if (m->killer == NO_KILLER)return;
		}
		enterTable(roomId);
	}
};
