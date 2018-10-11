#pragma once
#include "killer.h"
#include "card.h"

class CS_gtx : public Killer {
public:
	CS_gtx(int p) : Killer(KILLER::CS_GTX, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CS_gtx() {}
};

class CS_gs : public Killer {
public:
	CS_gs(int p) : Killer(KILLER::CS_GS, p) {
		health = full = 3;
		steam = back = false;
	}
	virtual ~CS_gs() {}
};

class CS_czz : public Killer {
public:
	CS_czz(int p) : Killer(KILLER::CS_CZZ, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CS_czz() {}
};

class CS_szl : public Killer {
public:
	CS_szl(int p) : Killer(KILLER::CS_SZL, p) {
		health = full = 3;
		steam = back = false;
	}
	virtual ~CS_szl() {}
};

class CS_zrs : public Killer {
public:
	CS_zrs(int p) : Killer(KILLER::CS_ZRS, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CS_zrs() {}
};

class CS_zs : public Killer {
public:
	CS_zs(int p) : Killer(KILLER::CS_ZS, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CS_zs() {}
};

class CS_wyl : public Killer {
public:
	CS_wyl(int p) : Killer(KILLER::CS_WYL, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CS_wyl() {}
};

class CS_yzy : public Killer {
public:
	CS_yzy(int p) : Killer(KILLER::CS_YZY, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CS_yzy() {}
};

class CS_hwn : public Killer {
public:
	CS_hwn(int p) : Killer(KILLER::CS_HWN, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CS_hwn() {}
};

class CS_bs : public Killer {
public:
	CS_bs(int p) : Killer(KILLER::CS_BS, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CS_bs() {}
};

class CS_hysb : public Killer {
public:
	CS_hysb(int p) : Killer(KILLER::CS_HYSB, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CS_hysb() {}
};

