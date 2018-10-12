#pragma once
#include "killer.h"
#include "card.h"

class OT_gy : public Killer {
public:
	OT_gy(int p) : Killer(KILLER::OT_GY, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~OT_gy() {}
};

class OT_smq : public Killer {
public:
	OT_smq(int p) : Killer(KILLER::OT_SMQ, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~OT_smq() {}
};

class OT_yxtr : public Killer {
public:
	OT_yxtr(int p) : Killer(KILLER::OT_YXTR, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~OT_yxtr() {}
};

class OT_zy : public Killer {
public:
	OT_zy(int p) : Killer(KILLER::OT_ZY, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~OT_zy() {}
};

class OT_ys : public Killer {
public:
	OT_ys(int p) : Killer(KILLER::OT_YS, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~OT_ys() {}
};

class OT_zh : public Killer {
public:
	OT_zh(int p) : Killer(KILLER::OT_ZH, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~OT_zh() {}
};

class OT_yx : public Killer {
public:
	OT_yx(int p) : Killer(KILLER::OT_YX, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~OT_yx() {}
};

class OT_lzl : public Killer {
public:
	OT_lzl(int p) : Killer(KILLER::OT_LZL, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~OT_lzl() {}
};

class OT_sh : public Killer {
public:
	OT_sh(int p) : Killer(KILLER::OT_SH, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~OT_sh() {}
};

class OT_zjs : public Killer {
public:
	OT_zjs(int p) : Killer(KILLER::OT_ZJS, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~OT_zjs() {}
};




