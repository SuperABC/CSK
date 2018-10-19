#pragma once
#include "killer.h"
#include "card.h"

class SE_ynl : public Killer {
public:
	SE_ynl(int p) : Killer(KILLER::SE_YNL, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~SE_ynl() {}
};

class SE_wamy : public Killer {
public:
	SE_wamy(int p) : Killer(KILLER::SE_WAMY, p) {
		health = full = 3;
		steam = back = false;
	}
	virtual ~SE_wamy() {}
};

class SE_mys : public Killer {
public:
	SE_mys(int p) : Killer(KILLER::SE_MYS, p) {
		health = full = 3;
		steam = back = false;
	}
	virtual ~SE_mys() {}
};

class SE_msl : public Killer {
public:
	SE_msl(int p) : Killer(KILLER::SE_MSL, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~SE_msl() {}
};

class SE_ms : public Killer {
public:
	SE_ms(int p) : Killer(KILLER::SE_MS, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~SE_ms() {}
};

class SE_mwz : public Killer {
public:
	SE_mwz(int p) : Killer(KILLER::SE_MWZ, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~SE_mwz() {}
};

class SE_hhw : public Killer {
public:
	SE_hhw(int p) : Killer(KILLER::SE_HHW, p) {
		health = full = 5;
		steam = back = false;
	}
	virtual ~SE_hhw() {}
};

class SE_sd : public Killer {
public:
	SE_sd(int p) : Killer(KILLER::SE_SD, p) {
		health = full = 3;
		steam = back = false;
	}
	virtual ~SE_sd() {}
};

class SE_yjc : public Killer {
public:
	SE_yjc(int p) : Killer(KILLER::SE_YJC, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~SE_yjc() {}
};

class SE_cfc : public Killer {
public:
	SE_cfc(int p) : Killer(KILLER::SE_CFC, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~SE_cfc() {}
};


