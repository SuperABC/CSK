#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "card.h"
#include <iostream>
#include <string>

using std::string;
using std::vector;

enum KILLER {
	CSK_NULL,
	CSK_ZRS,
	CSK_MWZ,
	CSK_WZH,
	CSK_ZH,
};
enum ROLE {
	ROLE_MASTER,
	ROLE_MINISTER,
	ROLE_INVADER,
	ROLE_TRAITOR
};

class Judge {
public:
	vector<ROLE> roles;
};
class Killer {
protected:
	KILLER killer;
	string name;

	ROLE role;
	Judge judge;

	unsigned int full, health;
	bool steam, back;

	Deck handCards, equipCards, judgeCards, funcCards;

public:
	int position;
	bool dead;

	bool start = false, get = false, use = false, drop = false, end = false;

	Killer(KILLER k, int p, ROLE r) : killer(k), position(p), role(r) {
		equipCards.cont = vector<Card>(4);

		name = "¿Õ°×";
		health = full = 5;
		steam = back = dead = false;

		judge.roles.push_back(ROLE_MASTER);
		judge.roles.push_back(ROLE_INVADER);
		judge.roles.push_back(ROLE_TRAITOR);
		judge.roles.push_back(ROLE_MINISTER);
		judge.roles.push_back(ROLE_INVADER);
		judge.roles.push_back(ROLE_INVADER);
		judge.roles.push_back(ROLE_MINISTER);
		judge.roles.push_back(ROLE_INVADER);
	}
	~Killer() {}

	string getName() { return name; }
	int getFull() { return full; }
	int getHealthl() { return health; }
	ROLE getRole() { return role; }

	Deck getHandCards() {
		return handCards;
	}
	Deck getEquipCards() {
		return equipCards;
	}
	Deck getJudgeCards() {
		return judgeCards;
	}
	Deck getFuncCards() {
		return funcCards;
	}

	virtual void incomeCard(Card c);

	virtual void exeStart();
	virtual void exeGet();
	virtual void exeUse();
	virtual void exeDrop();
	virtual void exeEnd();
	virtual bool endStart();
	virtual bool endGet();
	virtual bool endUse();
	virtual bool endDrop();
	virtual bool endEnd();

	virtual void hurtGrade(int g = 1);
	virtual void looseGrade(int g = 1);
	virtual void incomeGrade();
	virtual void increaseFull();
	virtual bool askSave(int p);
	virtual bool receivePrevent();
};

string roleName(ROLE r);