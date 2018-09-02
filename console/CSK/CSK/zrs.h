#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "killer.h"
#include "card.h"

class ZRS : public Killer {
public:
	ZRS(int p, ROLE r) : Killer(CSK_ZRS, p, r) {
		name = "ZRS";
		health = full = 4;
		steam = back = false;
	}
	virtual ~ZRS() {}
};