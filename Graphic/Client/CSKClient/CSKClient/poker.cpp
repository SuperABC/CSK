#include "poker.h"
#include <string>
#include <vector>

vector<Poker> pokerList;
int pokerMax;

const char *cardInst[] = {
	"别学了：我求求你别学了好不好？",
	"商业阻挠：公司的大佬都发现你在学习了好伐？",
	"党性压制：你再学，组织上就要批判你了！",
	"没学：你什么时候看见我在学习了？",
	"学习：赶紧学习一波，提升下绩点。",
	"刷夜：要挂科了？刷夜刷夜。",
	"黑客入侵：进入你的系统了，顺手删点东西。",
	"抄代码：来来来给我抄抄。",
	"下载资料：发现了好多新资源呀。",
	"互膜：你也太强了吧，膜！",
	"督导检查：你在干什么呢？有人在学习你也无动于衷？",
	"约炮：来别学了，跟我来一发。",
	"重考：卷子被老师的孩子吃掉了，只能重考了。",
	"老师漏题：给你们点资料，这次考试就考这些内容。",
	"约自习：哇，大型聚众学习？那不是要赶紧阻止一下。",
	"约饭：别告诉我大家吃饭的时候你还在偷偷学习。",
	"查重：给我看一下你的代码，发现一样的你就完了。",
	"Steam好友：上线上线，我掉绩点你也一样。",
	"滚：哪来那么多毛病，别来烦我。",
	"游戏通宵：今晚你就打游戏吧，别写代码了。",
	"断网：诶呦，你无法获取最新的资料了。",
	"小抄：有了小抄，每次我都可以知道更多的内容了。",
	"点名：反正没人去上课，点名点到谁谁就要挂了。",
	"卖弱脚本：你限制不住我的，你学一百次我就要阻止一百次。",
	"水手服：小哥哥我这样好看吗？",
	"病毒：小姐姐你电脑中毒了，我帮你修一下？",
	"网线：你防具不管用的，我是网线直连。",
	"盗版系统：菜菜的系统，我可以不让你损失绩点，不过你的资料要没了。",
	"抖音视频：我抖，我抖到你掉绩点为止。",
	"转转笔：一支笔有两端，那两份代码就可以阻止你学习了。",
	"互评账号：诶呦你不承认你在学？我在互评系统里都看到了。",
	"大逃杀：组队开黑！你们三个别学了。",
	"主席语录：让我照着念一下，党的光辉下你就别偷偷学了。",
	"保安制服：哪来的违规交通工具和路障？",
	"红轴键盘：你看我这么高端的键盘难道是用来学习的？",
	"飞行模式：我开飞行模式了，你联系不到我。",
	"黑框眼镜：这种可以加一秒的神器，用过吗？",
	"集成显卡：我都用这么菜的显示器了，小火汁你就摇了我吧。",
	"对象：有了对象的安慰，我的绩点就不会下降太快了，也不会去约饭约自习了。",
	"小龟：龟速前进，但也比走路要快。",
	"校车：一种不一定比小龟要快的交通工具。",
	"翅膀：人造翅膀真的能飞的起来？",
	"启真湖：不好意思你需要绕过这个湖才能找到我。",
	"老和山：爬山很累的，你真的能走过来？",
	"行政楼：先来到行政楼顶，然后一跃解千愁。",
	"校友林：好像路线比较复杂，走过去要好久呢。"
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
	widgetObj *poker = getWidgetByName((string("poker") + std::to_string(p.id)).data());
	poker->value = p.cont;
	poker->hide = 0;
	poker->mouseIn = (mouseMoveCall)mouseMovePoker;
	poker->mouseOut = (mouseMoveCall)mouseMovePoker;
	poker->mouseUser = (mouseClickUser)mouseClickPoker;
	pokerList.push_back(p);
}