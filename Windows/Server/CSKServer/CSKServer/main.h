#pragma once
#include "winsgl.h"
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Card;


void loginProcess(struct JSON *recv, SOCKET socket);
void roomProcess(struct JSON *recv, SOCKET socket);
void killerProcess(struct JSON *recv, SOCKET socket);

void chooseKiller(int roomId);
void enterTable(int roomId);


NEW_THREAD_FUNC(gameLoop);

void stateProcess(int room);
void useProcess(struct JSON *json, int room);
void dropProcess(struct JSON *json, int room);
void cardProcess(char *recv, int room, int pos, char *cont);
void replyProcess(char *recv, int room, int pos, char *cont);
void lossProcess(char *recv, int room, int pos, Card card);
void doneProcess(int room, int pos);
void gradeProcess(char *recv, int room, int pos, int amount);

template<typename T>
void shuffleVector(vector<T> &v) {
	vector<T> tmp = v;

	srand((unsigned)time(NULL));
	for (auto &element : v) {
		int idx = rand() % tmp.size();
		element = tmp[idx];
		tmp[idx] = tmp.back();
		tmp.pop_back();
	}

	return;

}
