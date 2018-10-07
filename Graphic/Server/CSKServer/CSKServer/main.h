#pragma once
#include "winsgl.h"
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

void loginProcess(struct JSON *recv, SOCKET socket);
void roomProcess(struct JSON *recv, SOCKET socket);
void killerProcess(struct JSON *recv, SOCKET socket);
void gameProcess(char *recv, int room, int pos);

void chooseKiller(int roomId);
void enterTable(int roomId);

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
