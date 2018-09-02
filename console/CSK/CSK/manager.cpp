#include "manager.h"
#include <ctime>
#include <iostream>
#include <string>

Manager::Manager(vector<Killer *> p) {
	init();
	shuffle();

	for (auto p : p) {
		players.push_back(p);
	}

	if (p.size() >= 4)players[0]->increaseFull();
}
Manager::~Manager() {
	for (auto k : players) {
		delete k;
	}
}

void Manager::init() {
	//28�ű�ѧ��
	used.cont.push_back(Card(10, 0, 0));
	used.cont.push_back(Card(10, 0, 0));
	used.cont.push_back(Card(11, 0, 0));
	used.cont.push_back(Card(6, 0, 1));
	used.cont.push_back(Card(7, 0, 1));
	used.cont.push_back(Card(8, 0, 1));
	used.cont.push_back(Card(9, 0, 1));
	used.cont.push_back(Card(10, 0, 1));
	used.cont.push_back(Card(13, 0, 1));
	used.cont.push_back(Card(7, 0, 2));
	used.cont.push_back(Card(8, 0, 2));
	used.cont.push_back(Card(8, 0, 2));
	used.cont.push_back(Card(9, 0, 2));
	used.cont.push_back(Card(9, 0, 2));
	used.cont.push_back(Card(2, 0, 3));
	used.cont.push_back(Card(3, 0, 3));
	used.cont.push_back(Card(4, 0, 3));
	used.cont.push_back(Card(5, 0, 3));
	used.cont.push_back(Card(6, 0, 3));
	used.cont.push_back(Card(7, 0, 3));
	used.cont.push_back(Card(8, 0, 3));
	used.cont.push_back(Card(8, 0, 3));
	used.cont.push_back(Card(9, 0, 3));
	used.cont.push_back(Card(9, 0, 3));
	used.cont.push_back(Card(10, 0, 3));
	used.cont.push_back(Card(10, 0, 3));
	used.cont.push_back(Card(11, 0, 3));
	used.cont.push_back(Card(11, 0, 3));

	//9����ҵ����
	used.cont.push_back(Card(4, 1, 2));
	used.cont.push_back(Card(5, 1, 2));
	used.cont.push_back(Card(6, 1, 2));
	used.cont.push_back(Card(7, 1, 2));
	used.cont.push_back(Card(8, 1, 2));
	used.cont.push_back(Card(5, 1, 3));
	used.cont.push_back(Card(6, 1, 3));
	used.cont.push_back(Card(7, 1, 3));
	used.cont.push_back(Card(8, 1, 3));

	//5�ŵ���ѹ��
	used.cont.push_back(Card(3, 2, 0));
	used.cont.push_back(Card(7, 2, 0));
	used.cont.push_back(Card(10, 2, 0));
	used.cont.push_back(Card(4, 2, 1));
	used.cont.push_back(Card(5, 2, 1));

	//22��ûѧ
	used.cont.push_back(Card(2, 3, 0));
	used.cont.push_back(Card(2, 3, 0));
	used.cont.push_back(Card(8, 3, 0));
	used.cont.push_back(Card(9, 3, 0));
	used.cont.push_back(Card(11, 3, 0));
	used.cont.push_back(Card(12, 3, 0));
	used.cont.push_back(Card(13, 3, 0));
	used.cont.push_back(Card(2, 3, 1));
	used.cont.push_back(Card(2, 3, 1));
	used.cont.push_back(Card(3, 3, 1));
	used.cont.push_back(Card(4, 3, 1));
	used.cont.push_back(Card(5, 3, 1));
	used.cont.push_back(Card(6, 3, 1));
	used.cont.push_back(Card(6, 3, 1));
	used.cont.push_back(Card(7, 3, 1));
	used.cont.push_back(Card(7, 3, 1));
	used.cont.push_back(Card(8, 3, 1));
	used.cont.push_back(Card(8, 3, 1));
	used.cont.push_back(Card(9, 3, 1));
	used.cont.push_back(Card(11, 3, 1));
	used.cont.push_back(Card(11, 3, 1));
	used.cont.push_back(Card(11, 3, 1));

	//12��ѧϰ
	used.cont.push_back(Card(3, 4, 0));
	used.cont.push_back(Card(4, 4, 0));
	used.cont.push_back(Card(5, 4, 0));
	used.cont.push_back(Card(6, 4, 0));
	used.cont.push_back(Card(6, 4, 0));
	used.cont.push_back(Card(7, 4, 0));
	used.cont.push_back(Card(8, 4, 0));
	used.cont.push_back(Card(9, 4, 0));
	used.cont.push_back(Card(12, 4, 0));
	used.cont.push_back(Card(2, 4, 1));
	used.cont.push_back(Card(3, 4, 1));
	used.cont.push_back(Card(12, 4, 1));

	//5��ˢҹ
	used.cont.push_back(Card(3, 5, 2));
	used.cont.push_back(Card(9, 5, 2));
	used.cont.push_back(Card(3, 5, 3));
	used.cont.push_back(Card(9, 5, 3));
	used.cont.push_back(Card(9, 5, 1));

	//6�źڿ�����
	used.cont.push_back(Card(12, 6, 0));
	used.cont.push_back(Card(3, 6, 2));
	used.cont.push_back(Card(4, 6, 2));
	used.cont.push_back(Card(12, 6, 2));
	used.cont.push_back(Card(3, 6, 3));
	used.cont.push_back(Card(4, 6, 3));

	//5�ų�����
	used.cont.push_back(Card(3, 7, 1));
	used.cont.push_back(Card(4, 7, 1));
	used.cont.push_back(Card(3, 7, 2));
	used.cont.push_back(Card(4, 7, 2));
	used.cont.push_back(Card(11, 7, 2));

	//4����������
	used.cont.push_back(Card(7, 8, 0));
	used.cont.push_back(Card(8, 8, 0));
	used.cont.push_back(Card(9, 8, 0));
	used.cont.push_back(Card(11, 8, 0));

	//3�Ż�Ĥ
	used.cont.push_back(Card(1, 9, 1));
	used.cont.push_back(Card(1, 9, 2));
	used.cont.push_back(Card(1, 9, 3));

	//1�Ŷ������
	used.cont.push_back(Card(12, 10, 3));

	//1��Լ��
	used.cont.push_back(Card(13, 11, 3));

	//1���ؿ�
	used.cont.push_back(Card(1, 12, 0));

	//2����ʦ͸��
	used.cont.push_back(Card(3, 13, 0));
	used.cont.push_back(Card(4, 13, 0));

	//3��Լ��ϰ
	used.cont.push_back(Card(7, 14, 2));
	used.cont.push_back(Card(13, 14, 2));
	used.cont.push_back(Card(7, 14, 3));

	//1��Լ��
	used.cont.push_back(Card(1, 15, 0));

	//3�Ų���
	used.cont.push_back(Card(2, 16, 0));
	used.cont.push_back(Card(4, 16, 0));
	used.cont.push_back(Card(12, 16, 1));

	//5��steam����
	used.cont.push_back(Card(11, 17, 2));
	used.cont.push_back(Card(12, 17, 2));
	used.cont.push_back(Card(11, 17, 3));
	used.cont.push_back(Card(12, 17, 3));
	used.cont.push_back(Card(13, 17, 3));

	//7�Ź�
	used.cont.push_back(Card(1, 18, 0));
	used.cont.push_back(Card(13, 18, 0));
	used.cont.push_back(Card(10, 18, 1));
	used.cont.push_back(Card(11, 18, 2));
	used.cont.push_back(Card(13, 18, 2));
	used.cont.push_back(Card(12, 18, 3));
	used.cont.push_back(Card(13, 18, 3));

	//3����Ϸͨ��
	used.cont.push_back(Card(6, 19, 0));
	used.cont.push_back(Card(6, 19, 2));
	used.cont.push_back(Card(6, 19, 3));

	//2�Ŷ���
	used.cont.push_back(Card(10, 20, 2));
	used.cont.push_back(Card(4, 20, 3));

	//1��С��
	used.cont.push_back(Card(10, 21, 3));

	//2�ŵ���
	used.cont.push_back(Card(10, 22, 1));
	used.cont.push_back(Card(1, 22, 2));

	//2�������ű�
	used.cont.push_back(Card(1, 23, 1));
	used.cont.push_back(Card(1, 23, 3));

	//1��ˮ�ַ�
	used.cont.push_back(Card(2, 24, 2));

	//1�Ų���
	used.cont.push_back(Card(1, 25, 2));

	//1������
	used.cont.push_back(Card(6, 26, 2));

	//1�ŵ���ϵͳ
	used.cont.push_back(Card(10, 27, 2));

	//1�Ŷ�����Ƶ
	used.cont.push_back(Card(5, 28, 2));

	//1��תת��
	used.cont.push_back(Card(12, 29, 2));

	//1�Ż����˺�
	used.cont.push_back(Card(5, 30, 1));

	//1�Ŵ���ɱ
	used.cont.push_back(Card(12, 31, 1));

	//1����ϯ��¼
	used.cont.push_back(Card(1, 32, 1));

	//1�ű����Ʒ�
	used.cont.push_back(Card(5, 33, 0));

	//2�ź������
	used.cont.push_back(Card(2, 34, 2));
	used.cont.push_back(Card(2, 34, 3));

	//1�ŷ���ģʽ
	used.cont.push_back(Card(2, 35, 3));

	//1�źڿ��۾�
	used.cont.push_back(Card(2, 36, 2));

	//1�ż����Կ�
	used.cont.push_back(Card(10, 37, 2));

	//1�Ŷ���
	used.cont.push_back(Card(1, 38, 3));

	//1��С��
	used.cont.push_back(Card(5, 39, 0));

	//1��У��
	used.cont.push_back(Card(13, 40, 2));

	//1�ų��
	used.cont.push_back(Card(13, 41, 1));

	//1�������
	used.cont.push_back(Card(5, 42, 2));

	//1���Ϻ�ɽ
	used.cont.push_back(Card(5, 43, 3));

	//1������¥
	used.cont.push_back(Card(13, 44, 0));

	//1��У����
	used.cont.push_back(Card(13, 45, 1));
}
void Manager::shuffle() {
	int index;
	srand((unsigned)time(0));
	while (used.cont.size()) {
		index = rand() % used.cont.size();
		untouch.cont.push_back(used.cont[index]);
		used.cont[index] = used.cont[used.cont.size() - 1];
		used.cont.pop_back();
	}
	return;
}
bool Manager::finish() {
	int master = 0, minister = 0, invader = 0, traitor = 0;
	for (auto p : players) {
		if (!p->dead) {
			switch (p->getRole()) {
			case ROLE_MASTER:
				master++;
				break;
			case ROLE_MINISTER:
				minister++;
				break;
			case ROLE_INVADER:
				invader++;
				break;
			case ROLE_TRAITOR:
				traitor++;
				break;
			}
		}
	}
	if (master == 0) {
		if (invader == 0 && minister == 0) {
			std::cout << "ѧ滻�ʤ��" << std::endl;
			return true;
		}
		else {
			std::cout << "ѧ����ʤ��" << std::endl;
			return true;
		}
	}
	else if (invader == 0&&traitor==0) {
		std::cout << "�೤ѧ�Ի�ʤ��" << std::endl;
		return true;
	}
	return false;
}
void Manager::next() {
	if (tmpStep == CSK_FINISH)return;

	if (dying == -1) {
		if (tmpAim == -1) {
			if (players[tmpPlayer]->dead == true) {
				do {
					tmpPlayer++;
					if (tmpPlayer >= players.size())tmpPlayer = 0;
				} while (players[tmpPlayer]->dead == true);
				tmpStep = CSK_START;
				return;
			}
			switch (tmpStep) {
			case CSK_INIT:
				std::cout << "��ʼ���׶Ρ�" << std::endl;
				for (auto p : players) {
					p->incomeCard(untouch.cont.back());
					untouch.cont.pop_back();
					p->incomeCard(untouch.cont.back());
					untouch.cont.pop_back();
					p->incomeCard(untouch.cont.back());
					untouch.cont.pop_back();
					p->incomeCard(untouch.cont.back());
					untouch.cont.pop_back();
				}
				tmpStep = CSK_START;
				break;
			case CSK_START:
				players[tmpPlayer]->exeStart();
				if (players[tmpPlayer]->endStart())
					tmpStep = CSK_GET;
				break;
			case CSK_GET:
				players[tmpPlayer]->exeGet();
				if (players[tmpPlayer]->endGet())
					tmpStep = CSK_USE;
				break;
			case CSK_USE:
				players[tmpPlayer]->exeUse();
				if (players[tmpPlayer]->endUse())
					tmpStep = CSK_DROP;
				break;
			case CSK_DROP:
				players[tmpPlayer]->exeDrop();
				if (players[tmpPlayer]->endDrop())
					tmpStep = CSK_END;
				break;
			case CSK_END:
				players[tmpPlayer]->exeEnd();
				if (players[tmpPlayer]->endEnd()) {
					do {
						tmpPlayer++;
						if (tmpPlayer >= players.size())tmpPlayer = 0;
					} while (players[tmpPlayer]->dead == true);
					tmpStep = CSK_START;
				}
				break;
			default:
				break;
			}
		}
		else {
			switch (tmpUse.cont) {
			case CC_PREVENT:
			case CC_COMMERCE:
			case CC_PARTY:
				if (players[tmpAim]->receivePrevent() == false) {
					players[tmpAim]->hurtGrade();
				}
			default:
				break;
			}
			tmpUse = Card();
			tmpAim = -1;
		}
	}
	else {
		for (unsigned int i = 0; i < players.size(); i++) {
			if (players[(i + tmpPlayer) % players.size()]->askSave(dying)) {
				players[dying]->incomeGrade();
				dying = -1;
				return;
			}
		}

		players[dying]->dead = true;
		for (auto c : players[dying]->getHandCards().cont)dropCard(c);
		for (auto c : players[dying]->getEquipCards().cont)dropCard(c);
		for (auto c : players[dying]->getJudgeCards().cont)dropCard(c);

		std::cout << dying << "��λ" << players[dying]->getName() << "�ѹҿơ�" << std::endl;
		dying = -1;
		if(finish())tmpStep = CSK_FINISH;
	}
}

