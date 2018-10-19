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

	Deck untouch, used;

	bool gameOver() {
		int alive = 0;
		for (auto k : players) {
			if (!k->dead)alive++;
		}
		if (alive < 2)return true;
		else return false;
	}
public:
	unsigned int tmpPlayer = 0;
	STEP tmpStep = CSK_INIT;

	Manager(vector<Roommate *> p) {
		int i = 0;
		for (auto p : p) {
			players.push_back(Killer::newKiller(p->killer, i++));
		}
		untouch = newDeck();
	}
	~Manager() {
		for (auto k : players) {
			delete k;
		}
	}

	int getPlayer() { return tmpPlayer; }
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
			while(players[tmpPlayer]->dead)
				tmpPlayer = (tmpPlayer + 1) % players.size();
			break;
		default:
			break;
		}

		return tmpStep;
	}
	void deadOne(int pos) {
		players[pos]->dead = true;

		if (gameOver()) {
			tmpStep = CSK_FINISH;
		}
	}

};