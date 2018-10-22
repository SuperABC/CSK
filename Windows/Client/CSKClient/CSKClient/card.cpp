#include "card.h"
#include "manager.h"

struct JSON *Card::toJson() {
	struct JSON *json = createJson();
	setIntContent(json, "cont", cont);
	setIntContent(json, "color", color);
	setIntContent(json, "num", num);
	return json;
}

string cardName(Card c) {
	string ret = "";
	switch (c.color) {
	case CS_HEART:
		ret += "����";
		break;
	case CS_SQUARE:
		ret += "��Ƭ";
		break;
	case CS_SPADE:
		ret += "����";
		break;
	case CS_CLUB:
		ret += "�ݻ�";
		break;
	default:
		break;
	}
	switch (c.num) {
	case 1:
		ret += "A";
		break;
	case 2:
		ret += "2";
		break;
	case 3:
		ret += "3";
		break;
	case 4:
		ret += "4";
		break;
	case 5:
		ret += "5";
		break;
	case 6:
		ret += "6";
		break;
	case 7:
		ret += "7";
		break;
	case 8:
		ret += "8";
		break;
	case 9:
		ret += "9";
		break;
	case 10:
		ret += "10";
		break;
	case 11:
		ret += "J";
		break;
	case 12:
		ret += "Q";
		break;
	case 13:
		ret += "K";
		break;
	default:
		break;
	}
	switch (c.cont) {
	case CC_PREVENT:
		ret += "��ѧ��";
		break;
	case CC_COMMERCE:
		ret += "��ҵ����";
		break;
	case CC_PARTY:
		ret += "����ѹ��";
		break;
	case CC_DENY:
		ret += "ûѧ";
		break;
	case CC_STUDY:
		ret += "ѧϰ";
		break;
	case CC_STAYUP:
		ret += "ˢҹ";
		break;
	case CC_HACK:
		ret += "�ڿ�����";
		break;
	case CC_COPY:
		ret += "������";
		break;
	case CC_DOWNLOAD:
		ret += "��������";
		break;
	case CC_WORSHIP:
		ret += "��Ĥ";
		break;
	case CC_HURRY:
		ret += "�������";
		break;
	case CC_FUCK:
		ret += "Լ��";
		break;
	case CC_REEXAM:
		ret += "�ؿ�";
		break;
	case CC_EXAMLEAK:
		ret += "��ʦ͸��";
		break;
	case CC_TOREVIEW:
		ret += "Լ��ϰ";
		break;
	case CC_TOEAT:
		ret += "Լ��";
		break;
	case CC_DUPLICATE:
		ret += "����";
		break;
	case CC_STEAM:
		ret += "Steam����";
		break;
	case CC_GOAWAY:
		ret += "��";
		break;
	case CC_NIGHTPLAY:
		ret += "��Ϸͨ��";
		break;
	case CC_NONET:
		ret += "����";
		break;
	case CC_REF:
		ret += "С��";
		break;
	case CC_CALLROLL:
		ret += "����";
		break;
	case CC_SCRIPT:
		ret += "�����ű�";
		break;
	case CC_LOLI:
		ret += "ˮ�ַ�";
		break;
	case CC_VIRUS:
		ret += "����";
		break;
	case CC_LINE:
		ret += "����";
		break;
	case CC_OFFLINE:
		ret += "����ϵͳ";
		break;
	case CC_BOOM:
		ret += "������Ƶ";
		break;
	case CC_SPINPEN:
		ret += "תת��";
		break;
	case CC_PTA:
		ret += "�����˺�";
		break;
	case CC_CHICKEN:
		ret += "����ɱ";
		break;
	case CC_CHAIRMAN:
		ret += "��ϯ��¼";
		break;
	case CC_GUARD:
		ret += "�����Ʒ�";
		break;
	case CC_KEYBOARD:
		ret += "�������";
		break;
	case CC_FLYING:
		ret += "����ģʽ";
		break;
	case CC_GLASSES:
		ret += "�ڿ��۾�";
		break;
	case CC_GTX:
		ret += "�����Կ�";
		break;
	case CC_DBELEPHANT:
		ret += "����";
		break;
	case CC_MOTOR:
		ret += "С��";
		break;
	case CC_BUS:
		ret += "У��";
		break;
	case CC_ARM:
		ret += "���";
		break;
	case CC_LAKE:
		ret += "�����";
		break;
	case CC_MOUNTAIN:
		ret += "�Ϻ�ɽ";
		break;
	case CC_BUILDING:
		ret += "����¥";
		break;
	case CC_FOREST:
		ret += "У����";
		break;
	default:
		break;
	}
	return ret;
}
Type cardType(Card c) {
	if (c.cont >= CC_PREVENT && c.cont <= CC_STAYUP)return CT_ORDINARY;
	if (c.cont >= CC_HACK && c.cont <= CC_CALLROLL)return CT_FUNC;
	if (c.cont >= CC_SCRIPT && c.cont <= CC_FOREST)return CT_EQUIPMENT;
	return CT_NULL;
}
int weaponDist(Card c) {
	switch (c.cont) {
	case CC_SCRIPT:
		return 1;
	case CC_LOLI:
		return 2;
	case CC_VIRUS:
		return 2;
	case CC_LINE:
		return 2;
	case CC_OFFLINE:
		return 2;
	case CC_BOOM:
		return 3;
	case CC_SPINPEN:
		return 3;
	case CC_PTA:
		return 3;
	case CC_CHICKEN:
		return 4;
	case CC_CHAIRMAN:
		return 4;
	case CC_GUARD:
		return 5;
	default:
		return 1;
	}
}
