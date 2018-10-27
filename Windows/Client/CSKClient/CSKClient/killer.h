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

class CS_gtx;
class CS_gs;
class CS_czz;
class CS_szl;
class CS_zrs;
class CS_zs;
class CS_wyl;
class CS_yzy;
class CS_hwn;
class CS_bs;
class CS_hysb;

class SE_tnl;
class SE_wamy;
class SE_mys;
class SE_msl;
class SE_ms;
class SE_mwz;
class SE_hhw;
class SE_sd;
class SE_yjc;
class SE_cfc;

class CKC_lwyd;
class CKC_lwx;
class CKC_zzh;
class CKC_zs;
class CKC_zcy;
class CKC_zsb;
class CKC_yty;
class CKC_ljw;
class CKC_swyd;
class CKC_wzh;

class OT_gy;
class OT_smq;
class OT_yxtr;
class OT_zy;
class OT_ys;
class OT_zh;
class OT_yx;
class OT_lzl;
class OT_sh;
class OT_zjs;

class Killer {
protected:
	KILLER killer;
	string name;

	int full, health;
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

	static Killer *newKiller(KILLER k, int p);

	KILLER getKiller() { return killer; }
	void setName(string name) { this->name = name; }
	string getName() { return name; }
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
};

void addEquip(Card c, int playerPos, int deltaPos);
void removeEquip(int type, int pos);
