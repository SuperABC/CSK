#pragma once
#include "main.h"
#include "card.h"
#include "killer.h"
#include <vector>

using std::vector;

enum STEP {
	CSK_INIT,
	CSK_START,
	CSK_GET,
	CSK_USE,
	CSK_DROP,
	CSK_END,
	CSK_FINISH
};

class Manager {
private:
	vector<Killer *> players;
	unsigned int playerPos = 0;

	unsigned int tmpPlayer = 0;
	STEP tmpStep = CSK_INIT;

public:
	int dying = -1;

	Manager(vector<Killer *> p, int pos);
	~Manager();

	vector<Killer *> getPlayer() { return players; }
	int getPosition() { return playerPos; }
	Killer *getSelf() { return players[playerPos]; }
	bool myTurn() { return tmpPlayer == playerPos; }
	int calDist(unsigned int i, unsigned int j) {
		int live = 0, di = 0, dj = 0;
		for (unsigned int k = 0; k < players.size(); k++) {
			if (players[k]->dead) {
				if (k < i)di++;
				if (k < j)dj++;
			}
			else live++;
		}
		i -= di;
		j -= dj;

		int left = (j - i + live) % live;
		int right = (i - j + live) % live;
		int dist = left < right ? left : right;

		if (players[i]->getEquipCards().cont[ET_VEHICLE].cont != CC_NULL)
			dist--;
		if (players[j]->getEquipCards().cont[ET_BARRIER].cont != CC_NULL)
			dist++;

		if (dist < 1)dist = 1;
		return dist;
	}
	STEP nextState() {
		switch (tmpStep) {
		case CSK_INIT:
			tmpPlayer = 0;
			tmpStep = CSK_START;
			break;
		case CSK_START:
			tmpStep = CSK_GET;
			break;
		case CSK_GET:
			tmpStep = CSK_USE;
			break;
		case CSK_USE:
			tmpStep = CSK_DROP;
			break;
		case CSK_DROP:
			tmpStep = CSK_END;
			break;
		case CSK_END:
			tmpStep = CSK_START;
			tmpPlayer = (tmpPlayer + 1) % players.size();
			while (players[tmpPlayer]->dead)
				tmpPlayer = (tmpPlayer + 1) % players.size();
			break;
		default:
			break;
		}

		return tmpStep;
	}
	void deadOne(int pos) {
		players[pos]->dead = true;
	}
};