#include "poker.h"
#include <string>
#include <vector>

vector<Poker> pokerList;
int pokerMax;

const char *cardInst[] = {
	"��ѧ�ˣ����������ѧ�˺ò��ã�",
	"��ҵ���ӣ���˾�Ĵ��ж���������ѧϰ�˺÷���",
	"����ѹ�ƣ�����ѧ����֯�Ͼ�Ҫ�������ˣ�",
	"ûѧ����ʲôʱ�򿴼�����ѧϰ�ˣ�",
	"ѧϰ���Ͻ�ѧϰһ���������¼��㡣",
	"ˢҹ��Ҫ�ҿ��ˣ�ˢҹˢҹ��",
	"�ڿ����֣��������ϵͳ�ˣ�˳��ɾ�㶫����",
	"�����룺���������ҳ�����",
	"�������ϣ������˺ö�����Դѽ��",
	"��Ĥ����Ҳ̫ǿ�˰ɣ�Ĥ��",
	"������飺���ڸ�ʲô�أ�������ѧϰ��Ҳ�޶����ԣ�",
	"Լ�ڣ�����ѧ�ˣ�������һ����",
	"�ؿ������ӱ���ʦ�ĺ��ӳԵ��ˣ�ֻ���ؿ��ˡ�",
	"��ʦ©�⣺�����ǵ����ϣ���ο��ԾͿ���Щ���ݡ�",
	"Լ��ϰ���ۣ����;���ѧϰ���ǲ���Ҫ�Ͻ���ֹһ�¡�",
	"Լ����������Ҵ�ҳԷ���ʱ���㻹��͵͵ѧϰ��",
	"���أ����ҿ�һ����Ĵ��룬����һ����������ˡ�",
	"Steam���ѣ��������ߣ��ҵ�������Ҳһ����",
	"����������ô��ë�����������ҡ�",
	"��Ϸͨ����������ʹ���Ϸ�ɣ���д�����ˡ�",
	"���������ϣ����޷���ȡ���µ������ˡ�",
	"С��������С����ÿ���Ҷ�����֪������������ˡ�",
	"����������û��ȥ�ϿΣ������㵽˭˭��Ҫ���ˡ�",
	"�����ű��������Ʋ�ס�ҵģ���ѧһ�ٴ��Ҿ�Ҫ��ֹһ�ٴΡ�",
	"ˮ�ַ���С����������ÿ���",
	"������С���������ж��ˣ��Ұ�����һ�£�",
	"���ߣ�����߲����õģ���������ֱ����",
	"����ϵͳ���˲˵�ϵͳ���ҿ��Բ�������ʧ���㣬�����������Ҫû�ˡ�",
	"������Ƶ���Ҷ����Ҷ����������Ϊֹ��",
	"תת�ʣ�һ֧�������ˣ������ݴ���Ϳ�����ֹ��ѧϰ�ˡ�",
	"�����˺ţ������㲻��������ѧ�����ڻ���ϵͳ�ﶼ�����ˡ�",
	"����ɱ����ӿ��ڣ�����������ѧ�ˡ�",
	"��ϯ��¼������������һ�£����Ĺ������ͱ�͵͵ѧ�ˡ�",
	"�����Ʒ���������Υ�潻ͨ���ߺ�·�ϣ�",
	"������̣��㿴����ô�߶˵ļ����ѵ�������ѧϰ�ģ�",
	"����ģʽ���ҿ�����ģʽ�ˣ�����ϵ�����ҡ�",
	"�ڿ��۾������ֿ��Լ�һ����������ù���",
	"�����Կ����Ҷ�����ô�˵���ʾ���ˣ�С��֭���ҡ���Ұɡ�",
	"�������˶���İ�ο���ҵļ���Ͳ����½�̫���ˣ�Ҳ����ȥԼ��Լ��ϰ�ˡ�",
	"С�꣺����ǰ������Ҳ����·Ҫ�졣",
	"У����һ�ֲ�һ����С��Ҫ��Ľ�ͨ���ߡ�",
	"�������������ܷɵ�������",
	"�������������˼����Ҫ�ƹ�����������ҵ��ҡ�",
	"�Ϻ�ɽ����ɽ���۵ģ���������߹�����",
	"����¥������������¥����Ȼ��һԾ��ǧ�",
	"У���֣�����·�߱Ƚϸ��ӣ��߹�ȥҪ�þ��ء�"
};

void mouseMovePoker(widgetObj *w, int x, int y) {
	if (inWidget(w, x, y)) {
		widgetObj *inst = getWidgetByName("instruction");
		strcpy((char *)inst->content, cardInst[w->value]);
		inst->valid = 0;
	}

	mouseMoveDefault(w, x, y);
	w->valid = 0;
}
void mouseClickPoker(widgetObj *w) {
	if (w->hide == 0) {
		w->hide = 1;
		moveWidgetByName(w->name, 0, -20);
	}
	else {
		w->hide = 0;
		moveWidgetByName(w->name, 0, 20);
	}
}

void addPoker(Poker p) {
	p.id = pokerMax++;
	easyWidget(SG_OUTPUT, (string("poker") + std::to_string(p.id)).data(),
		10 + pokerList.size() * 60, 320, 90, 120,
		cardName(Card(p.num, p.cont, p.color)).data(), NULL);
	p.widget = getWidgetByName((string("poker") + std::to_string(p.id)).data());
	p.widget->value = p.cont;
	p.widget->hide = 0;
	p.widget->mouseIn = (mouseMoveCall)mouseMovePoker;
	p.widget->mouseOut = (mouseMoveCall)mouseMovePoker;
	p.widget->mouseUser = (mouseClickUser)mouseClickPoker;
	pokerList.push_back(p);
}
void removePoker(vector<int> idxs) {
	for (auto i : idxs) {
		deleteWidgetByName(pokerList[i].widget->name);
		pokerList[i].widget = NULL;
	}
	unsigned int i = 0;
	while (i < pokerList.size()) {
		if (pokerList[i].widget) {
			moveWidgetByName(pokerList[i].widget->name, 10 + 60 * i - pokerList[i].widget->pos.x, 0);
			setWidgetTop(pokerList[i].widget->name);
			i++;
		}
		else {
			for (unsigned int j = i + 1; j < pokerList.size(); j++) {
				pokerList[j - 1] = pokerList[j];
			}
			pokerList.pop_back();
		}
	}
}