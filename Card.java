public class Card {
	enum Type {
		CT_ORDINARY,
		CT_FUNC,
		CT_EQUIPMENT
	}
	enum Content {
		CC_PREVENT,//别学了(杀)
		CC_DENY,//没学(闪)
		CC_STUDY,//学习(桃)
		CC_STAYUP,//刷夜(酒)
		CC_NONET,//断网(兵粮寸断)
		CC_WEAKSHOW,//卖弱(火攻)
		CC_NIGHTPLAY,//游戏通宵(乐不思蜀)
		CC_WORSHIP,//互膜(决斗)
		CC_TOEAT,//约饭(南蛮入侵)
		CC_TOREVIEW,//约自习(万箭齐发)
		CC_COPY,//抄代码(顺手牵羊)
		CC_CALLROLL,//点名(闪电)
		CC_STEAM,//Steam好友(铁索连环)
		CC_DOWNLOAD,//下载资料(无中生有)
		CC_HACK,//黑客入侵(过河拆桥)
		CC_EXAMLEAK,//考试漏题(五谷丰登)
		CC_NOPROBLEM,//无懈可击(无懈可击)
		CC_FUCK,//盗号约炮(借刀杀人)
		CC_REEXAM,//重考(桃园结义)
	}
	
	private Type type;
	private int number;
	private Content cont;
	
	public Card(int n, int c) {
		number = n;
		switch(c) {
		case 0:
			cont = Content.CC_PREVENT;
			break;
		case 1:
			cont = Content.CC_DENY;
			break;
		case 2:
			cont = Content.CC_STUDY;
			break;
		}
	}
	
	public String getType() {
		switch(type) {
		case CT_ORDINARY:
			return "基本牌";
		case CT_FUNC:
			return "技术牌";
		case CT_EQUIPMENT:
			return "工具牌";
		default:
			return null;
		}
	}
	public int getNum() {
		return number;
	}
	public String getCont() {
		switch(cont) {
		case CC_PREVENT:
			return "别学了";
		case CC_DENY:
			return "没学";
		case CC_STUDY:
			return "学习";
		case CC_STAYUP:
			return "刷夜";
		case CC_NONET:
			return "断网";
		case CC_WEAKSHOW:
			return "卖弱";
		case CC_NIGHTPLAY:
			return "游戏通宵";
		case CC_WORSHIP:
			return "互膜";
		case CC_TOEAT:
			return "约饭";
		case CC_TOREVIEW:
			return "约自习";
		case CC_COPY:
			return "抄代码";
		case CC_CALLROLL:
			return "点名";
		case CC_STEAM:
			return "Steam好友";
		case CC_DOWNLOAD:
			return "下载资料";
		case CC_EXAMLEAK:
			return "考试漏题";
		case CC_HACK:
			return "黑客入侵";
		case CC_NOPROBLEM:
			return "无懈可击";
		case CC_FUCK:
			return "盗号约炮";
		case CC_REEXAM:
			return "重考";
		default:
			return null;
		}
	}
}
