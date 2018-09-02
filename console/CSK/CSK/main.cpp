#include "main.h"
#include "manager.h"
#include <windows.h>
#include <iostream>

using namespace std;

Manager *manager;

int main() {
	cout << "��ӭ������Ժɱ��" << endl;
	cout << "��ѡ��ģʽ��\n1. ��ݳ�\n2.һ��һ\n3.Ժս" << endl;

	int mode, num;
	cin >> mode;
	while (mode < 1 || mode > 3) {
		cout << "ģʽѡ������������ѡ��" << endl;
		cout << "��ѡ��ģʽ��\n1. ��ݳ�\n2.һ��һ\n3.Ժս" << endl;
		cin >> mode;
	}
	switch (mode) {
	case 1:
		cout << "��ǰѡ��Ϊ��ݳ���" << endl;
		cout << "��������Ϸ������4-8����" << endl;
		cin >> num;
		while (num < 4 || num > 8) {
			cout << "��Ϸ���������������������룡" << endl;
			cout << "��������Ϸ������4-8����" << endl;
			cin >> num;
		}
		break;
	case 2:
		cout << "��ǰѡ��Ϊһ��һ��" << endl;
		num = 2;
		break;
	case 3:
		cout << "��ǰѡ��ΪԺս��" << endl;
		cout << "��δ������ɡ�" << endl;
		break;
	default:
		break;
	}

	vector<ROLE> roles;
	roles.push_back(ROLE_MASTER);
	roles.push_back(ROLE_INVADER);
	roles.push_back(ROLE_TRAITOR);
	if (num > 3)roles.push_back(ROLE_MINISTER);
	if (num > 4)roles.push_back(ROLE_INVADER);
	if (num > 5)roles.push_back(ROLE_INVADER);
	if (num > 6)roles.push_back(ROLE_MINISTER);
	if (num > 7)roles.push_back(ROLE_INVADER);

	vector<Killer *> p;
	for (int i = 0; i < num; i++) {
		p.push_back(new Killer(CSK_NULL, i, roles[i]));
	}

	cout << "��Ϸ��ʼ��" << endl;

	manager = new Manager(p);

	createTable();

	while (true) {
		manager->next();
		Sleep(500);
	}
}
