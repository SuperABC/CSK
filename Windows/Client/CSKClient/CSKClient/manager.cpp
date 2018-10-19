#include "manager.h"
#include <ctime>
#include <iostream>
#include <string>

Manager::Manager(vector<Killer *> p, int pos) {
	for (auto p : p) {
		players.push_back(p);
	}
	playerPos = pos;
}
Manager::~Manager() {
	for (auto k : players) {
		delete k;
	}
}
