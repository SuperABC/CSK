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
	CSK_FINISH,
	CSK_ASKING
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
	vector<vector<int>> waitingList;

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

	vector<Card> tmpCard;

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
	void logInfo() {
		for (auto p : players) {
			std::cout << p->position << " " << p->getHealth() << "/" << p->getFull() << std::endl;
		}
	}

	int waitingLevel() {
		return waitingList.size();
	}
	void waitFor(vector<int> list) {
		if (list.empty())return;
		waitingList.push_back(list);
	}
	void responseCome(int r) {
		vector<int> &list = waitingList.back();
		for (unsigned int i = 0; i < list.size(); i++) {
			if (list[i] == r) {
				list[i] = list.back();
				list.pop_back();
				break;
			}
		}
		if (list.empty())
			waitingList.pop_back();
	}
	bool isWaiting(unsigned int level = 0) {
		return waitingList.size() > level;
	}

	int getPlayer() { return tmpPlayer; }
	Card touchCard() {
		if (untouch.cont.size() == 0) {
			untouch.cont = used.cont;
			used.cont.clear();
			shuffleVector(untouch.cont);
		}
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
	int gradeChange(int pos, int amount) {
		if (amount < 0)
			return players[pos]->hurtHealth(-amount);
		else
			return players[pos]->recureHealth(amount);
	}
};