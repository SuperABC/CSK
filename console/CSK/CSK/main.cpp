#include "main.h"
#include "manager.h"
#include <windows.h>
#include <iostream>

using namespace std;

Manager *manager;

int main() {
	cout << "欢迎来到妓院杀！" << endl;
	cout << "请选择模式：\n1. 身份场\n2.一对一\n3.院战" << endl;

	int mode, num;
	cin >> mode;
	while (mode < 1 || mode > 3) {
		cout << "模式选择有误，请重新选择！" << endl;
		cout << "请选择模式：\n1. 身份场\n2.一对一\n3.院战" << endl;
		cin >> mode;
	}
	switch (mode) {
	case 1:
		cout << "当前选择为身份场。" << endl;
		cout << "请输入游戏人数（4-8）：" << endl;
		cin >> num;
		while (num < 4 || num > 8) {
			cout << "游戏人数输入有误，请重新输入！" << endl;
			cout << "请输入游戏人数（4-8）：" << endl;
			cin >> num;
		}
		break;
	case 2:
		cout << "当前选择为一对一。" << endl;
		num = 2;
		break;
	case 3:
		cout << "当前选择为院战。" << endl;
		cout << "暂未开发完成。" << endl;
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

	cout << "游戏开始！" << endl;

	manager = new Manager(p);

	createTable();

	while (true) {
		manager->next();
		Sleep(500);
	}
}
