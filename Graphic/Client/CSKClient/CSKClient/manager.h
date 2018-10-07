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
	Manager(vector<Killer *> p, int pos);
	~Manager();

	vector<Killer *> getPlayer() { return players; }
	int getPosition() { return playerPos; }
	Killer *getSelf() { return players[playerPos]; }
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

		if (players[i]->getEquipCards().cont[3].cont != CC_NULL)
			dist--;
		if (players[j]->getEquipCards().cont[2].cont != CC_NULL)
			dist++;

		if (dist < 1)dist = 1;
		return dist;
	}

};