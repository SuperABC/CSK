#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include "main.h"
#include "card.h"
#include "killer.h"
#include "zrs.h"

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

	unsigned int tmpPlayer = 0;
	STEP tmpStep = CSK_INIT;

	Deck untouch, used;

	Card tmpUse = Card();
	int tmpAim = -1;

	void init();
	void shuffle();
	bool finish();

public:
	int dying = -1;

	Manager(vector<Killer *> p);
	~Manager();

	void next();

	vector<Killer *> getPlayer() { return players; }
	Card topCard() {
		if (untouch.cont.size() == 0)shuffle();
		Card ret = untouch.cont.back();
		untouch.cont.pop_back();
		return ret;
	}
	void dropCard(Card c) {
		used.cont.push_back(c);
	}
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

	bool finishSummary() {
		return tmpUse.cont == CC_NULL;
	}
	void preventEnemy(Card c, int aim) {
		tmpUse = c;
		tmpAim = aim;

		dropCard(c);
	}
};