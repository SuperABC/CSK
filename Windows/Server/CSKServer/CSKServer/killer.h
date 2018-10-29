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

class Killer {
protected:
	KILLER killer;

	unsigned int full, health;
	bool steam, back;

	Deck handCards, equipCards, judgeCards, funcCards;

public:
	int position;
	bool dead;

	Killer(KILLER k, int p) : killer(k), position(p) {
		equipCards.cont = vector<Card>(4);

		health = full = 5;
		steam = back = dead = false;
	}
	~Killer() {}

	static Killer *newKiller(KILLER k, int p) {
		Killer *ret = new Killer(k, p);

		switch (k) {
		case CS_GTX:
			ret->full = ret->health = 4;
			break;
		case CS_GS:
			ret->full = ret->health = 3;
			break;
		case CS_CZZ:
			ret->full = ret->health = 4;
			break;
		case CS_SZL:
			ret->full = ret->health = 3;
			break;
		case CS_ZRS:
			ret->full = ret->health = 4;
			break;
		case CS_ZS:
			ret->full = ret->health = 3;
			break;
		case CS_WYL:
			ret->full = ret->health = 3;
			break;
		case CS_YZY:
			ret->full = ret->health = 3;
			break;
		case CS_HWN:
			ret->full = ret->health = 3;
			break;
		case CS_BS:
			ret->full = ret->health = 3;
			break;
		case CS_HYSB:
			ret->full = ret->health = 3;
			break;
		case SE_YNL:
			ret->full = ret->health = 4;
			break;
		case SE_WAMY:
			ret->full = ret->health = 3;
			break;
		case SE_MYS:
			ret->full = ret->health = 3;
			break;
		case SE_MSL:
			ret->full = ret->health = 4;
			break;
		case SE_MS:
			ret->full = ret->health = 4;
			break;
		case SE_MWZ:
			ret->full = ret->health = 4;
			break;
		case SE_HHW:
			ret->full = ret->health = 5;
			break;
		case SE_SD:
			ret->full = ret->health = 3;
			break;
		case SE_YJC:
			ret->full = ret->health = 4;
			break;
		case SE_CFC:
			ret->full = ret->health = 4;
			break;
		case CKC_LWYD:
			ret->full = ret->health = 4;
			break;
		case CKC_LWX:
			ret->full = ret->health = 4;
			break;
		case CKC_ZZH:
			ret->full = ret->health = 4;
			break;
		case CKC_ZS:
			ret->full = ret->health = 4;
			break;
		case CKC_ZCY:
			ret->full = ret->health = 4;
			break;
		case CKC_ZSB:
			ret->full = ret->health = 3;
			break;
		case CKC_YTY:
			ret->full = ret->health = 4;
			break;
		case CKC_LJW:
			ret->full = ret->health = 3;
			break;
		case CKC_SWYD:
			ret->full = ret->health = 3;
			break;
		case CKC_WZH:
			ret->full = ret->health = 4;
			break;
		case OT_GY:
			ret->full = ret->health = 3;
			break;
		case OT_SMQ:
			ret->full = ret->health = 4;
			break;
		case OT_YXTR:
			ret->full = ret->health = 3;
			break;
		case OT_ZY:
			ret->full = ret->health = 3;
			break;
		case OT_YS:
			ret->full = ret->health = 3;
			break;
		case OT_ZH:
			ret->full = ret->health = 7;
			break;
		case OT_YX:
			ret->full = ret->health = 4;
			break;
		case OT_LZL:
			ret->full = ret->health = 4;
			break;
		case OT_SH:
			ret->full = ret->health = 3;
			break;
		case OT_ZJS:
			ret->full = ret->health = 3;
			break;
		case NO_KILLER:
		case KILLER_END:
		default:
			break;
		}
		return ret;
	}

	KILLER getKiller() { return killer; }
	int getFull() { return full; }
	int getHealth() { return health; }

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

	int hurtHealth(int h) {
		health -= h;
		return health;
	}
	int recureHealth(int h) {
		health += h;
		if (health > full)health = full;
		return health;
	}
	Card addEquip(Card c) {
		Card ret = equipCards.cont[equipType(c)];
		equipCards.cont[equipType(c)] = c;
		return ret;
	}
	void removeEquip(EQUIPTYPE t) {
		equipCards.cont[t] = Card();
	}
};

