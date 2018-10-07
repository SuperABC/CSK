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

class Roommate : public User {
public:
	enum KILLER killer;

	Roommate(User *user) : killer(NO_KILLER), User(*user) {}
};

class Manager {
private:
	vector<Killer *> players;

	unsigned int tmpPlayer = 0;
	STEP tmpStep = CSK_INIT;

	Deck untouch, used;

public:
	Manager(vector<Roommate *> p) {
		int i = 0;
		for (auto p : p) {
			players.push_back(new Killer(p->killer, i++));
		}
		untouch = newDeck();
	}
	~Manager() {
		for (auto k : players) {
			delete k;
		}
	}

	vector<Killer *> getPlayer() { return players; }
	Card touchCard() {
		Card ret = untouch.cont.back();
		untouch.cont.pop_back();
		return ret;
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

};