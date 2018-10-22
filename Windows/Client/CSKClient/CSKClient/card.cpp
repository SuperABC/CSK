#include "card.h"
#include "manager.h"

struct JSON *Card::toJson() {
	struct JSON *json = createJson();
	setIntContent(json, "cont", cont);
	setIntContent(json, "color", color);
	setIntContent(json, "num", num);
	return json;
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
