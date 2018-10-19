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
	CC_PREVENT,//别学了(杀)0
	CC_COMMERCE,//商业阻挠(雷杀)1
	CC_PARTY,//党性压制(火杀)2
	CC_DENY,//没学(闪)3
	CC_STUDY,//学习(桃)4
	CC_STAYUP,//刷夜(酒)5

	CC_HACK,//黑客入侵(过河拆桥)6
	CC_COPY,//抄代码(顺手牵羊)7
	CC_DOWNLOAD,//下载资料(无中生有)8
	CC_WORSHIP,//互膜(决斗)9
	CC_HURRY,//督导检查(借刀杀人)10
	CC_FUCK,//约炮(借盾闪人)11
	CC_REEXAM,//重考(桃园结义)12
	CC_EXAMLEAK,//老师漏题(五谷丰登)13
	CC_TOREVIEW,//约自习(南蛮入侵)14
	CC_TOEAT,//约饭(万箭齐发)15
	CC_DUPLICATE,//查重(火攻)16
	CC_STEAM,//Steam好友(铁索连环)17
	CC_GOAWAY,//滚(无懈可击)18
	CC_NIGHTPLAY,//游戏通宵(乐不思蜀)19
	CC_NONET,//断网(兵粮寸断)20
	CC_REF,//小抄(摸两张牌)21
	CC_CALLROLL,//点名(闪电)22

	CC_SCRIPT,//卖弱脚本(诸葛连弩1)23
	CC_LOLI,//水手服(雌雄剑2)24
	CC_VIRUS,//病毒(雌雄剑2)25
	CC_LINE,//网线(青釭剑2)26
	CC_OFFLINE,//盗版系统(寒冰剑2)27
	CC_BOOM,//抖音视频(青龙偃月刀3)28
	CC_SPINPEN,//转转笔(丈八矛3)29
	CC_PTA,//互评账号(贯石斧3)30
	CC_CHICKEN,//大逃杀(方天画戟4)31
	CC_CHAIRMAN,//主席语录(朱雀羽扇4)32
	CC_GUARD,//保安制服(麒麟弓5)33
	CC_KEYBOARD,//红轴键盘(八卦阵)34
	CC_FLYING,//飞行模式(青釭盾)35
	CC_GLASSES,//黑框眼镜(续命)36
	CC_GTX,//集成显卡(仁王盾)37
	CC_DBELEPHANT,//对象(白银狮子)38
	CC_MOTOR,//小龟(-1马)39
	CC_BUS,//校车(-1马)40
	CC_ARM,//翅膀(-1马)41
	CC_LAKE,//启真湖(+1马)42
	CC_MOUNTAIN,//老和山(+1马)43
	CC_BUILDING,//行政楼(+1马)44
	CC_FOREST,//校友林(+1马)45
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
