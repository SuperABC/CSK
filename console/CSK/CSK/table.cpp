#include "main.h"
#include "manager.h"
#include <windows.h>
#include <iostream>
#include <string>

using std::string;

extern Manager *manager;

LPWSTR _widenStr(const char *src) {
	int rt;
	LPWSTR rs;

	if (src == NULL)return NULL;

	rt = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
	rs = (LPWSTR)malloc(rt * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, src, -1, rs, rt * sizeof(wchar_t));
	return rs;
}
void debugf(const char *format, ...) {
	va_list ap;
	int idx = 0;
	char *tmp;
	LPWSTR _wd;

	va_start(ap, format);

	tmp = (char *)malloc(2 * strlen(format) + 16);
	while (*format) {
		if (*format == '%') {
			format++;
			switch (*format) {
			case 'c': {
				char valch = va_arg(ap, int);
				tmp[idx++] = valch;
				format++;
				break;
			}
			case 'd': {
				int valint = va_arg(ap, int);
				_itoa(valint, tmp + idx, 10);
				while (tmp[idx++]);
				idx--;
				format++;
				break;
			}
			case 'o': {
				int valint = va_arg(ap, int);
				_itoa(valint, tmp + idx, 8);
				while (tmp[idx++]);
				idx--;
				format++;
				break;
			}
			case 'x': {
				int valint = va_arg(ap, int);
				_itoa(valint, tmp + idx, 16);
				while (tmp[idx++]);
				idx--;
				format++;
				break;
			}
			case 's': {
				char *valstr = va_arg(ap, char *);
				tmp[idx] = '\0';
				strcat(tmp, valstr);
				while (tmp[idx++]);
				idx--;
				format++;
				break;
			}
			case '%': {
				tmp[idx++] = *format++;
			}
			}
		}
		else {
			tmp[idx++] = *format++;
		}
	}

	tmp[idx] = '\0';
	OutputDebugString(_wd = _widenStr(tmp));
	free((void *)_wd);

	free(tmp);
	va_end(ap);
}
DWORD WINAPI _threadFunc(LPVOID pM) {
	HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE);

	while (true) {
		for (auto p : manager->getPlayer()) {
			if (p->dead) {
				debugf("%d号位%s已挂科", p->position, p->getName().data());
			}
			else {
				debugf("%d号位%s, 绩点%d/%d, 手牌数%d\n",
					p->position, p->getName().data(), p->getHealthl(), p->getFull(),
					p->getHandCards().cont.size());
				debugf(" ");
				debugf("\t武器%s, 防具%s, 路障%s, 交通%s",
					p->getEquipCards().cont[0].cont == CC_NULL ?
					"无" : cardName(p->getEquipCards().cont[0]).data(),
					p->getEquipCards().cont[1].cont == CC_NULL ?
					"无" : cardName(p->getEquipCards().cont[1]).data(),
					p->getEquipCards().cont[2].cont == CC_NULL ?
					"无" : cardName(p->getEquipCards().cont[2]).data(),
					p->getEquipCards().cont[3].cont == CC_NULL ?
					"无" : cardName(p->getEquipCards().cont[3]).data()
				);
			}
			debugf("\n");
		}
		debugf("\n");
		Sleep(100);
	}

	return 0;
}
void createTable() {
	HANDLE handle = CreateThread(NULL, 0, _threadFunc, NULL, 0, NULL);
}
