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
		ret += "红桃";
		break;
	case CS_SQUARE:
		ret += "方片";
		break;
	case CS_SPADE:
		ret += "黑桃";
		break;
	case CS_CLUB:
		ret += "草花";
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
		ret += "别学了";
		break;
	case CC_COMMERCE:
		ret += "商业阻挠";
		break;
	case CC_PARTY:
		ret += "党性压制";
		break;
	case CC_DENY:
		ret += "没学";
		break;
	case CC_STUDY:
		ret += "学习";
		break;
	case CC_STAYUP:
		ret += "刷夜";
		break;
	case CC_HACK:
		ret += "黑客入侵";
		break;
	case CC_COPY:
		ret += "抄代码";
		break;
	case CC_DOWNLOAD:
		ret += "下载资料";
		break;
	case CC_WORSHIP:
		ret += "互膜";
		break;
	case CC_HURRY:
		ret += "督导检查";
		break;
	case CC_FUCK:
		ret += "约炮";
		break;
	case CC_REEXAM:
		ret += "重考";
		break;
	case CC_EXAMLEAK:
		ret += "老师透题";
		break;
	case CC_TOREVIEW:
		ret += "约自习";
		break;
	case CC_TOEAT:
		ret += "约饭";
		break;
	case CC_DUPLICATE:
		ret += "查重";
		break;
	case CC_STEAM:
		ret += "Steam好友";
		break;
	case CC_GOAWAY:
		ret += "滚";
		break;
	case CC_NIGHTPLAY:
		ret += "游戏通宵";
		break;
	case CC_NONET:
		ret += "断网";
		break;
	case CC_REF:
		ret += "小抄";
		break;
	case CC_CALLROLL:
		ret += "点名";
		break;
	case CC_SCRIPT:
		ret += "卖弱脚本";
		break;
	case CC_LOLI:
		ret += "水手服";
		break;
	case CC_VIRUS:
		ret += "病毒";
		break;
	case CC_LINE:
		ret += "网线";
		break;
	case CC_OFFLINE:
		ret += "盗版系统";
		break;
	case CC_BOOM:
		ret += "抖音视频";
		break;
	case CC_SPINPEN:
		ret += "转转笔";
		break;
	case CC_PTA:
		ret += "互评账号";
		break;
	case CC_CHICKEN:
		ret += "大逃杀";
		break;
	case CC_CHAIRMAN:
		ret += "主席语录";
		break;
	case CC_GUARD:
		ret += "保安制服";
		break;
	case CC_KEYBOARD:
		ret += "红轴键盘";
		break;
	case CC_FLYING:
		ret += "飞行模式";
		break;
	case CC_GLASSES:
		ret += "黑框眼镜";
		break;
	case CC_GTX:
		ret += "集成显卡";
		break;
	case CC_DBELEPHANT:
		ret += "对象";
		break;
	case CC_MOTOR:
		ret += "小龟";
		break;
	case CC_BUS:
		ret += "校车";
		break;
	case CC_ARM:
		ret += "翅膀";
		break;
	case CC_LAKE:
		ret += "启真湖";
		break;
	case CC_MOUNTAIN:
		ret += "老和山";
		break;
	case CC_BUILDING:
		ret += "行政楼";
		break;
	case CC_FOREST:
		ret += "校友林";
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

	//28张别学了
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

	//9张商业阻挠
	ret.cont.push_back(Card(4, 1, 2));
	ret.cont.push_back(Card(5, 1, 2));
	ret.cont.push_back(Card(6, 1, 2));
	ret.cont.push_back(Card(7, 1, 2));
	ret.cont.push_back(Card(8, 1, 2));
	ret.cont.push_back(Card(5, 1, 3));
	ret.cont.push_back(Card(6, 1, 3));
	ret.cont.push_back(Card(7, 1, 3));
	ret.cont.push_back(Card(8, 1, 3));

	//5张党性压制
	ret.cont.push_back(Card(3, 2, 0));
	ret.cont.push_back(Card(7, 2, 0));
	ret.cont.push_back(Card(10, 2, 0));
	ret.cont.push_back(Card(4, 2, 1));
	ret.cont.push_back(Card(5, 2, 1));

	//22张没学
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

	//12张学习
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

	//5张刷夜
	ret.cont.push_back(Card(3, 5, 2));
	ret.cont.push_back(Card(9, 5, 2));
	ret.cont.push_back(Card(3, 5, 3));
	ret.cont.push_back(Card(9, 5, 3));
	ret.cont.push_back(Card(9, 5, 1));

	//6张黑客入侵
	ret.cont.push_back(Card(12, 6, 0));
	ret.cont.push_back(Card(3, 6, 2));
	ret.cont.push_back(Card(4, 6, 2));
	ret.cont.push_back(Card(12, 6, 2));
	ret.cont.push_back(Card(3, 6, 3));
	ret.cont.push_back(Card(4, 6, 3));

	//5张抄代码
	ret.cont.push_back(Card(3, 7, 1));
	ret.cont.push_back(Card(4, 7, 1));
	ret.cont.push_back(Card(3, 7, 2));
	ret.cont.push_back(Card(4, 7, 2));
	ret.cont.push_back(Card(11, 7, 2));

	//4张下载资料
	ret.cont.push_back(Card(7, 8, 0));
	ret.cont.push_back(Card(8, 8, 0));
	ret.cont.push_back(Card(9, 8, 0));
	ret.cont.push_back(Card(11, 8, 0));

	//3张互膜
	ret.cont.push_back(Card(1, 9, 1));
	ret.cont.push_back(Card(1, 9, 2));
	ret.cont.push_back(Card(1, 9, 3));

	//1张督导检查
	ret.cont.push_back(Card(12, 10, 3));

	//1张约炮
	ret.cont.push_back(Card(13, 11, 3));

	//1张重考
	ret.cont.push_back(Card(1, 12, 0));

	//2张老师透题
	ret.cont.push_back(Card(3, 13, 0));
	ret.cont.push_back(Card(4, 13, 0));

	//3张约自习
	ret.cont.push_back(Card(7, 14, 2));
	ret.cont.push_back(Card(13, 14, 2));
	ret.cont.push_back(Card(7, 14, 3));

	//1张约饭
	ret.cont.push_back(Card(1, 15, 0));

	//3张查重
	ret.cont.push_back(Card(2, 16, 0));
	ret.cont.push_back(Card(4, 16, 0));
	ret.cont.push_back(Card(12, 16, 1));

	//5张steam好友
	ret.cont.push_back(Card(11, 17, 2));
	ret.cont.push_back(Card(12, 17, 2));
	ret.cont.push_back(Card(11, 17, 3));
	ret.cont.push_back(Card(12, 17, 3));
	ret.cont.push_back(Card(13, 17, 3));

	//7张滚
	ret.cont.push_back(Card(1, 18, 0));
	ret.cont.push_back(Card(13, 18, 0));
	ret.cont.push_back(Card(10, 18, 1));
	ret.cont.push_back(Card(11, 18, 2));
	ret.cont.push_back(Card(13, 18, 2));
	ret.cont.push_back(Card(12, 18, 3));
	ret.cont.push_back(Card(13, 18, 3));

	//3张游戏通宵
	ret.cont.push_back(Card(6, 19, 0));
	ret.cont.push_back(Card(6, 19, 2));
	ret.cont.push_back(Card(6, 19, 3));

	//2张断网
	ret.cont.push_back(Card(10, 20, 2));
	ret.cont.push_back(Card(4, 20, 3));

	//1张小抄
	ret.cont.push_back(Card(10, 21, 3));

	//2张点名
	ret.cont.push_back(Card(10, 22, 1));
	ret.cont.push_back(Card(1, 22, 2));

	//2张卖弱脚本
	ret.cont.push_back(Card(1, 23, 1));
	ret.cont.push_back(Card(1, 23, 3));

	//1张水手服
	ret.cont.push_back(Card(2, 24, 2));

	//1张病毒
	ret.cont.push_back(Card(1, 25, 2));

	//1张网线
	ret.cont.push_back(Card(6, 26, 2));

	//1张盗版系统
	ret.cont.push_back(Card(10, 27, 2));

	//1张抖音视频
	ret.cont.push_back(Card(5, 28, 2));

	//1张转转笔
	ret.cont.push_back(Card(12, 29, 2));

	//1张互评账号
	ret.cont.push_back(Card(5, 30, 1));

	//1张大逃杀
	ret.cont.push_back(Card(12, 31, 1));

	//1张主席语录
	ret.cont.push_back(Card(1, 32, 1));

	//1张保安制服
	ret.cont.push_back(Card(5, 33, 0));

	//2张红轴键盘
	ret.cont.push_back(Card(2, 34, 2));
	ret.cont.push_back(Card(2, 34, 3));

	//1张飞行模式
	ret.cont.push_back(Card(2, 35, 3));

	//1张黑框眼镜
	ret.cont.push_back(Card(2, 36, 2));

	//1张集成显卡
	ret.cont.push_back(Card(10, 37, 2));

	//1张对象
	ret.cont.push_back(Card(1, 38, 3));

	//1张小龟
	ret.cont.push_back(Card(5, 39, 0));

	//1张校车
	ret.cont.push_back(Card(13, 40, 2));

	//1张翅膀
	ret.cont.push_back(Card(13, 41, 1));

	//1张启真湖
	ret.cont.push_back(Card(5, 42, 2));

	//1张老和山
	ret.cont.push_back(Card(5, 43, 3));

	//1张行政楼
	ret.cont.push_back(Card(13, 44, 0));

	//1张校友林
	ret.cont.push_back(Card(13, 45, 1));

	shuffleVector(ret.cont);
	return ret;
}
