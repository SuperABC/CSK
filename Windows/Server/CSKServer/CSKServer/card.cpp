#include "card.h"

struct JSON *Card::toJson() {
	struct JSON *json = createJson();
	setIntContent(json, "cont", cont);
	setIntContent(json, "color", color);
	setIntContent(json, "num", num);
	return json;
}

EQUIPTYPE equipType(Card c) {
	switch (c.cont) {
	case CC_SCRIPT:
	case CC_LOLI:
	case CC_VIRUS:
	case CC_LINE:
	case CC_OFFLINE:
	case CC_BOOM:
	case CC_SPINPEN:
	case CC_PTA:
	case CC_CHICKEN:
	case CC_CHAIRMAN:
	case CC_GUARD:
		return ET_WEAPON;
	case CC_KEYBOARD:
	case CC_FLYING:
	case CC_GLASSES:
	case CC_GTX:
	case CC_DBELEPHANT:
		return ET_DEFENDER;
	case CC_MOTOR:
	case CC_BUS:
	case CC_ARM:
		return ET_VEHICLE;
	case CC_LAKE:
	case CC_MOUNTAIN:
	case CC_BUILDING:
	case CC_FOREST:
		return ET_BARRIER;
	default:
		return ET_WEAPON;
	}
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
Deck newDeck() {
	Deck ret;

	//28�ű�ѧ��
	ret.cont.push_back(Card(10, 0, 0));
	ret.cont.push_back(Card(10, 0, 0));
	ret.cont.push_back(Card(11, 0, 0));
	ret.cont.push_back(Card(6, 0, 1));
	ret.cont.push_back(Card(7, 0, 1));
	ret.cont.push_back(Card(8, 0, 1));
	ret.cont.push_back(Card(9, 0, 1));
	ret.cont.push_back(Card(10, 0, 1));
	ret.cont.push_back(Card(13, 0, 1));
	ret.cont.push_back(Card(7, 0, 2));
	ret.cont.push_back(Card(8, 0, 2));
	ret.cont.push_back(Card(8, 0, 2));
	ret.cont.push_back(Card(9, 0, 2));
	ret.cont.push_back(Card(9, 0, 2));
	ret.cont.push_back(Card(2, 0, 3));
	ret.cont.push_back(Card(3, 0, 3));
	ret.cont.push_back(Card(4, 0, 3));
	ret.cont.push_back(Card(5, 0, 3));
	ret.cont.push_back(Card(6, 0, 3));
	ret.cont.push_back(Card(7, 0, 3));
	ret.cont.push_back(Card(8, 0, 3));
	ret.cont.push_back(Card(8, 0, 3));
	ret.cont.push_back(Card(9, 0, 3));
	ret.cont.push_back(Card(9, 0, 3));
	ret.cont.push_back(Card(10, 0, 3));
	ret.cont.push_back(Card(10, 0, 3));
	ret.cont.push_back(Card(11, 0, 3));
	ret.cont.push_back(Card(11, 0, 3));

	//9����ҵ����
	ret.cont.push_back(Card(4, 1, 2));
	ret.cont.push_back(Card(5, 1, 2));
	ret.cont.push_back(Card(6, 1, 2));
	ret.cont.push_back(Card(7, 1, 2));
	ret.cont.push_back(Card(8, 1, 2));
	ret.cont.push_back(Card(5, 1, 3));
	ret.cont.push_back(Card(6, 1, 3));
	ret.cont.push_back(Card(7, 1, 3));
	ret.cont.push_back(Card(8, 1, 3));

	//5�ŵ���ѹ��
	ret.cont.push_back(Card(3, 2, 0));
	ret.cont.push_back(Card(7, 2, 0));
	ret.cont.push_back(Card(10, 2, 0));
	ret.cont.push_back(Card(4, 2, 1));
	ret.cont.push_back(Card(5, 2, 1));

	//22��ûѧ
	ret.cont.push_back(Card(2, 3, 0));
	ret.cont.push_back(Card(2, 3, 0));
	ret.cont.push_back(Card(8, 3, 0));
	ret.cont.push_back(Card(9, 3, 0));
	ret.cont.push_back(Card(11, 3, 0));
	ret.cont.push_back(Card(12, 3, 0));
	ret.cont.push_back(Card(13, 3, 0));
	ret.cont.push_back(Card(2, 3, 1));
	ret.cont.push_back(Card(2, 3, 1));
	ret.cont.push_back(Card(3, 3, 1));
	ret.cont.push_back(Card(4, 3, 1));
	ret.cont.push_back(Card(5, 3, 1));
	ret.cont.push_back(Card(6, 3, 1));
	ret.cont.push_back(Card(6, 3, 1));
	ret.cont.push_back(Card(7, 3, 1));
	ret.cont.push_back(Card(7, 3, 1));
	ret.cont.push_back(Card(8, 3, 1));
	ret.cont.push_back(Card(8, 3, 1));
	ret.cont.push_back(Card(9, 3, 1));
	ret.cont.push_back(Card(11, 3, 1));
	ret.cont.push_back(Card(11, 3, 1));
	ret.cont.push_back(Card(11, 3, 1));

	//12��ѧϰ
	ret.cont.push_back(Card(3, 4, 0));
	ret.cont.push_back(Card(4, 4, 0));
	ret.cont.push_back(Card(5, 4, 0));
	ret.cont.push_back(Card(6, 4, 0));
	ret.cont.push_back(Card(6, 4, 0));
	ret.cont.push_back(Card(7, 4, 0));
	ret.cont.push_back(Card(8, 4, 0));
	ret.cont.push_back(Card(9, 4, 0));
	ret.cont.push_back(Card(12, 4, 0));
	ret.cont.push_back(Card(2, 4, 1));
	ret.cont.push_back(Card(3, 4, 1));
	ret.cont.push_back(Card(12, 4, 1));

	//5��ˢҹ
	ret.cont.push_back(Card(3, 5, 2));
	ret.cont.push_back(Card(9, 5, 2));
	ret.cont.push_back(Card(3, 5, 3));
	ret.cont.push_back(Card(9, 5, 3));
	ret.cont.push_back(Card(9, 5, 1));

	//6�źڿ�����
	ret.cont.push_back(Card(12, 6, 0));
	ret.cont.push_back(Card(3, 6, 2));
	ret.cont.push_back(Card(4, 6, 2));
	ret.cont.push_back(Card(12, 6, 2));
	ret.cont.push_back(Card(3, 6, 3));
	ret.cont.push_back(Card(4, 6, 3));

	//5�ų�����
	ret.cont.push_back(Card(3, 7, 1));
	ret.cont.push_back(Card(4, 7, 1));
	ret.cont.push_back(Card(3, 7, 2));
	ret.cont.push_back(Card(4, 7, 2));
	ret.cont.push_back(Card(11, 7, 2));

	//4����������
	ret.cont.push_back(Card(7, 8, 0));
	ret.cont.push_back(Card(8, 8, 0));
	ret.cont.push_back(Card(9, 8, 0));
	ret.cont.push_back(Card(11, 8, 0));

	//3�Ż�Ĥ
	ret.cont.push_back(Card(1, 9, 1));
	ret.cont.push_back(Card(1, 9, 2));
	ret.cont.push_back(Card(1, 9, 3));

	//1�Ŷ������
	ret.cont.push_back(Card(12, 10, 3));

	//1��Լ��
	ret.cont.push_back(Card(13, 11, 3));

	//1���ؿ�
	ret.cont.push_back(Card(1, 12, 0));

	//2����ʦ͸��
	ret.cont.push_back(Card(3, 13, 0));
	ret.cont.push_back(Card(4, 13, 0));

	//3��Լ��ϰ
	ret.cont.push_back(Card(7, 14, 2));
	ret.cont.push_back(Card(13, 14, 2));
	ret.cont.push_back(Card(7, 14, 3));

	//1��Լ��
	ret.cont.push_back(Card(1, 15, 0));

	//3�Ų���
	ret.cont.push_back(Card(2, 16, 0));
	ret.cont.push_back(Card(4, 16, 0));
	ret.cont.push_back(Card(12, 16, 1));

	//5��steam����
	ret.cont.push_back(Card(11, 17, 2));
	ret.cont.push_back(Card(12, 17, 2));
	ret.cont.push_back(Card(11, 17, 3));
	ret.cont.push_back(Card(12, 17, 3));
	ret.cont.push_back(Card(13, 17, 3));

	//7�Ź�
	ret.cont.push_back(Card(1, 18, 0));
	ret.cont.push_back(Card(13, 18, 0));
	ret.cont.push_back(Card(10, 18, 1));
	ret.cont.push_back(Card(11, 18, 2));
	ret.cont.push_back(Card(13, 18, 2));
	ret.cont.push_back(Card(12, 18, 3));
	ret.cont.push_back(Card(13, 18, 3));

	//3����Ϸͨ��
	ret.cont.push_back(Card(6, 19, 0));
	ret.cont.push_back(Card(6, 19, 2));
	ret.cont.push_back(Card(6, 19, 3));

	//2�Ŷ���
	ret.cont.push_back(Card(10, 20, 2));
	ret.cont.push_back(Card(4, 20, 3));

	//1��С��
	ret.cont.push_back(Card(10, 21, 3));

	//2�ŵ���
	ret.cont.push_back(Card(10, 22, 1));
	ret.cont.push_back(Card(1, 22, 2));

	//2�������ű�
	ret.cont.push_back(Card(1, 23, 1));
	ret.cont.push_back(Card(1, 23, 3));

	//1��ˮ�ַ�
	ret.cont.push_back(Card(2, 24, 2));

	//1�Ų���
	ret.cont.push_back(Card(1, 25, 2));

	//1������
	ret.cont.push_back(Card(6, 26, 2));

	//1�ŵ���ϵͳ
	ret.cont.push_back(Card(10, 27, 2));

	//1�Ŷ�����Ƶ
	ret.cont.push_back(Card(5, 28, 2));

	//1��תת��
	ret.cont.push_back(Card(12, 29, 2));

	//1�Ż����˺�
	ret.cont.push_back(Card(5, 30, 1));

	//1�Ŵ���ɱ
	ret.cont.push_back(Card(12, 31, 1));

	//1����ϯ��¼
	ret.cont.push_back(Card(1, 32, 1));

	//1�ű����Ʒ�
	ret.cont.push_back(Card(5, 33, 0));

	//2�ź������
	ret.cont.push_back(Card(2, 34, 2));
	ret.cont.push_back(Card(2, 34, 3));

	//1�ŷ���ģʽ
	ret.cont.push_back(Card(2, 35, 3));

	//1�źڿ��۾�
	ret.cont.push_back(Card(2, 36, 2));

	//1�ż����Կ�
	ret.cont.push_back(Card(10, 37, 2));

	//1�Ŷ���
	ret.cont.push_back(Card(1, 38, 3));

	//1��С��
	ret.cont.push_back(Card(5, 39, 0));

	//1��У��
	ret.cont.push_back(Card(13, 40, 2));

	//1�ų��
	ret.cont.push_back(Card(13, 41, 1));

	//1�������
	ret.cont.push_back(Card(5, 42, 2));

	//1���Ϻ�ɽ
	ret.cont.push_back(Card(5, 43, 3));

	//1������¥
	ret.cont.push_back(Card(13, 44, 0));

	//1��У����
	ret.cont.push_back(Card(13, 45, 1));

	shuffleVector(ret.cont);
	return ret;
}
