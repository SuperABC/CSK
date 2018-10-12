#pragma once
#include "killer.h"
#include "card.h"

class CKC_lwyd : public Killer {
public:
	CKC_lwyd(int p) : Killer(KILLER::CKC_LWYD, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CKC_lwyd() {}
};

class CKC_lwx : public Killer {
public:
	CKC_lwx(int p) : Killer(KILLER::CKC_LWX, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CKC_lwx() {}
};

class CKC_zzh : public Killer {
public:
	CKC_zzh(int p) : Killer(KILLER::CKC_ZZH, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CKC_zzh() {}
};

class CKC_zs : public Killer {
public:
	CKC_zs(int p) : Killer(KILLER::CKC_ZS, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CKC_zs() {}
};

class CKC_zcy : public Killer {
public:
	CKC_zcy(int p) : Killer(KILLER::CKC_ZCY, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CKC_zcy() {}
};

class CKC_zsb : public Killer {
public:
	CKC_zsb(int p) : Killer(KILLER::CKC_ZSB, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CKC_zsb() {}
};

class CKC_yty : public Killer {
public:
	CKC_yty(int p) : Killer(KILLER::CKC_YTY, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CKC_yty() {}
};

class CKC_ljw : public Killer {
public:
	CKC_ljw(int p) : Killer(KILLER::CKC_LJW, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CKC_ljw() {}
};

class CKC_swyd : public Killer {
public:
	CKC_swyd(int p) : Killer(KILLER::CKC_SWYD, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CKC_swyd() {}
};

class CKC_wzh: public Killer {
public:
	CKC_wzh(int p) : Killer(KILLER::CKC_WZH, p) {
		health = full = 4;
		steam = back = false;
	}
	virtual ~CKC_wzh() {}
};



