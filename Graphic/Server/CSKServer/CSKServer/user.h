#pragma once
#include <string>

enum USERSTATUS {
	US_LOGIN,
	US_ROOM,
	US_PLAYING
};

class User {
public:
	USERSTATUS status;
	int userId, roomId;
	std::string name;
	SOCKET socket;

	User(std::string name, SOCKET socket, int userId, int roomId = -1) :
		status(US_LOGIN), name(name), userId(userId), roomId(roomId), socket(socket) {}
};