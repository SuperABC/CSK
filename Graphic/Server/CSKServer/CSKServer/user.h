#pragma once
#include <string>

using std::string;

enum USERSTATUS {
	US_LOGIN,
	US_ROOM,
	US_WAITING,
	US_KILLER,
	US_PLAYING
};

class User {
public:
	USERSTATUS status;
	int userId, roomId;
	string name;
	SOCKET socket;

	User(string name, SOCKET socket, int userId, int roomId = -1) :
		status(US_LOGIN), name(name), userId(userId), roomId(roomId), socket(socket) {}
};