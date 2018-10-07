#pragma once
#include "card.h"

enum KILLER {
	NO_KILLER,

	CS_GTX,
	CS_GS,
	CS_CZZ,
	CS_SZL,
	CS_ZRS,
	CS_ZS,
	CS_WYL,
	CS_YZY,
	CS_HWN,
	CS_BS,
	CS_HYSB,

	SE_YNL,
	SE_WAMY,
	SE_MYS,
	SE_MSL,
	SE_MS,
	SE_MWZ,
	SE_HHW,
	SE_SD,
	SE_YJC,
	SE_CFC,

	CKC_LWYD,
	CKC_LWX,
	CKC_ZZH,
	CKC_ZS,
	CKC_ZCY,
	CKC_ZSB,
	CKC_YTY,
	CKC_LJW,
	CKC_SWYD,
	CKC_WZH,

	OT_GY,
	OT_SMQ,
	OT_YXTR,
	OT_ZY,
	OT_YS,
	OT_ZH,
	OT_YX,
	OT_LZL,
	OT_SH,
	OT_ZJS,

	KILLER_END
};
enum ROLE {
	ROLE_MASTER,
	ROLE_MINISTER,
	ROLE_INVADER,
	ROLE_TRAITOR
};

const char *killerName[];
extern const char *killerDetail[];

class Killer {
protected:
	KILLER killer;
	string name;

	unsigned int full, health;
	bool steam, back;

	Deck handCards, equipCards, judgeCards, funcCards;

public:
	int position;
	bool dead;

	Killer(KILLER k, int p) : killer(k), position(p) {
		equipCards.cont = vector<Card>(4);

		name = "";
		health = full = 5;
		steam = back = dead = false;
	}
	~Killer() {}

	KILLER getKiller() { return killer; }
	void setName(string name) { this->name = name; }
	string getName() { return name; }
	int getFull() { return full; }
	int getHealthl() { return health; }

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

};
