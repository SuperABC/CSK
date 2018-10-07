#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "killer.h"
#include "card.h"

class ZRS : public Killer {
public:
	ZRS(int p) : Killer(CS_ZRS, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~ZRS() {}
};