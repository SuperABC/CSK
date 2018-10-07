#pragma once
#include "main.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

enum Type {
	CT_ORDINARY,
	CT_FUNC,
	CT_EQUIPMENT,
	CT_NULL
};
enum Content {
	CC_PREVENT,//��ѧ��(ɱ)0
	CC_COMMERCE,//��ҵ����(��ɱ)1
	CC_PARTY,//����ѹ��(��ɱ)2
	CC_DENY,//ûѧ(��)3
	CC_STUDY,//ѧϰ(��)4
	CC_STAYUP,//ˢҹ(��)5

	CC_HACK,//�ڿ�����(���Ӳ���)6
	CC_COPY,//������(˳��ǣ��)7
	CC_DOWNLOAD,//��������(��������)8
	CC_WORSHIP,//��Ĥ(����)9
	CC_HURRY,//�������(�赶ɱ��)10
	CC_FUCK,//Լ��(�������)11
	CC_REEXAM,//�ؿ�(��԰����)12
	CC_EXAMLEAK,//��ʦ©��(��ȷ��)13
	CC_TOREVIEW,//Լ��ϰ(��������)14
	CC_TOEAT,//Լ��(����뷢)15
	CC_DUPLICATE,//����(��)16
	CC_STEAM,//Steam����(��������)17
	CC_GOAWAY,//��(��и�ɻ�)18
	CC_NIGHTPLAY,//��Ϸͨ��(�ֲ�˼��)19
	CC_NONET,//����(�������)20
	CC_REF,//С��(��������)21
	CC_CALLROLL,//����(����)22

	CC_SCRIPT,//�����ű�(�������1)23
	CC_LOLI,//ˮ�ַ�(���۽�2)24
	CC_VIRUS,//����(���۽�2)25
	CC_LINE,//����(���G��2)26
	CC_OFFLINE,//����ϵͳ(������2)27
	CC_BOOM,//������Ƶ(�������µ�3)28
	CC_SPINPEN,//תת��(�ɰ�ì3)29
	CC_PTA,//�����˺�(��ʯ��3)30
	CC_CHICKEN,//����ɱ(���컭�4)31
	CC_CHAIRMAN,//��ϯ��¼(��ȸ����4)32
	CC_GUARD,//�����Ʒ�(���빭5)33
	CC_KEYBOARD,//�������(������)34
	CC_FLYING,//����ģʽ(���G��)35
	CC_GLASSES,//�ڿ��۾�(����)36
	CC_GTX,//�����Կ�(������)37
	CC_DBELEPHANT,//����(����ʨ��)38
	CC_MOTOR,//С��(-1��)39
	CC_BUS,//У��(-1��)40
	CC_ARM,//���(-1��)41
	CC_LAKE,//�����(+1��)42
	CC_MOUNTAIN,//�Ϻ�ɽ(+1��)43
	CC_BUILDING,//����¥(+1��)44
	CC_FOREST,//У����(+1��)45
	CC_NULL
};
enum Color {
	CS_HEART,
	CS_SQUARE,
	CS_SPADE,
	CS_CLUB,
	CS_NULL
};
class Card {
public:
	int num;
	Color color;
	Content cont;

	Card() : num(0), cont(CC_NULL), color(CS_NULL) {}
	Card(int num, int cont, int color) :
		num(num), cont(Content(cont)), color(Color(color)) {}
};

class Deck {
public:
	vector<Card> cont;
};

string cardName(Card c);
Type cardType(Card c);
int weaponDist(Card c);
Deck newDeck();
