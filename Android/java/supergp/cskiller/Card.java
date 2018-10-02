package supergp.cskiller;

public class Card {
    public enum Type {
        CT_ORDINARY,
        CT_FUNC,
        CT_EQUIPMENT
    }
    public enum Content {
        CC_PREVENT,//别学了(杀)0
        CC_DENY,//没学(闪)1
        CC_STUDY,//学习(桃)2
        CC_STAYUP,//刷夜(酒)3
        CC_NONET,//断网(兵粮寸断)4
        CC_WEAKSHOW,//卖弱(火攻)5
        CC_NIGHTPLAY,//游戏通宵(乐不思蜀)6
        CC_WORSHIP,//互膜(决斗)7
        CC_TOEAT,//约饭(南蛮入侵)8
        CC_TOREVIEW,//约自习(万箭齐发)9
        CC_COPY,//抄代码(顺手牵羊)10
        CC_CALLROLL,//点名(闪电)11
        CC_STEAM,//Steam好友(铁索连环)12
        CC_DOWNLOAD,//下载资料(无中生有)13
        CC_HACK,//黑客入侵(过河拆桥)14
        CC_EXAMLEAK,//考试漏题(五谷丰登)15
        CC_NOPROBLEM,//滚(无懈可击)16
        CC_REEXAM,//重考(桃园结义)17
        CC_REF,//小抄(新加锦囊)18
        CC_FUCK,//盗号约炮(借刀杀人)19
        CC_SCRIPT,//卖弱脚本(诸葛连弩1)20
        CC_XILINX,//赛灵斯(青釭剑2)21
        CC_SPINPEN,//转转笔(丈八矛3)22
        CC_PTA,//互评账号(贯石斧3)23
        CC_CHICKEN,//大逃杀(方天画戟4)24
        CC_CLOTHES,//女装(雌雄剑2)25
        CC_LINUX,//新系统(寒冰剑2)26
        CC_GUARD,//保安制服(麒麟弓5)27
        CC_KEYBOARD,//红轴键盘(八卦阵)28
        CC_GTX,//GTX显卡(仁王盾)29
        CC_DBELEPHANT,//对象(白银狮子)30
        CC_GLASSES,//黑框眼镜(续命)31
        CC_FLYING,//飞行模式(青釭盾)32
        CC_MOTOR,//小龟(-1马)33
        CC_BUS,//校车(-1马)34
        CC_LAKE,//启真湖(+1马)35
        CC_MOUNTAIN,//老和山(+1马)36
    }
    public enum Color {
        CC_HEART,
        CC_SQUARE,
        CC_SPADE,
        CC_CLUB,
        CC_NONE
    }

    private Type type;
    private int number;
    private Content cont;
    public Color color;

    public Card(int n, int cont, int color) {
        number = n-1;
        switch(color){
            case 0:
                this.color = Color.CC_HEART;
                break;
            case 1:
                this.color = Color.CC_SQUARE;
                break;
            case 2:
                this.color = Color.CC_SPADE;
                break;
            case 3:
                this.color = Color.CC_CLUB;
                break;
        }
        switch(cont) {
            case 0:
                this.cont = Content.CC_PREVENT;
                break;
            case 1:
                this.cont = Content.CC_DENY;
                break;
            case 2:
                this.cont = Content.CC_STUDY;
                break;
            case 3:
                this.cont = Content.CC_STAYUP;
                break;
            case 4:
                this.cont = Content.CC_NONET;
                break;
            case 5:
                this.cont = Content.CC_WEAKSHOW;
                break;
            case 6:
                this.cont = Content.CC_NIGHTPLAY;
                break;
            case 7:
                this.cont = Content.CC_WORSHIP;
                break;
            case 8:
                this.cont = Content.CC_TOEAT;
                break;
            case 9:
                this.cont = Content.CC_TOREVIEW;
                break;
            case 10:
                this.cont = Content.CC_COPY;
                break;
            case 11:
                this.cont = Content.CC_CALLROLL;
                break;
            case 12:
                this.cont = Content.CC_STEAM;
                break;
            case 13:
                this.cont = Content.CC_DOWNLOAD;
                break;
            case 14:
                this.cont = Content.CC_HACK;
                break;
            case 15:
                this.cont = Content.CC_EXAMLEAK;
                break;
            case 16:
                this.cont = Content.CC_NOPROBLEM;
                break;
            case 17:
                this.cont = Content.CC_REEXAM;
                break;
            case 18:
                this.cont = Content.CC_REF;
                break;
            case 19:
                this.cont = Content.CC_FUCK;
                break;
            case 20:
                this.cont = Content.CC_SCRIPT;
                break;
            case 21:
                this.cont = Content.CC_XILINX;
                break;
            case 22:
                this.cont = Content.CC_SPINPEN;
                break;
            case 23:
                this.cont = Content.CC_PTA;
                break;
            case 24:
                this.cont = Content.CC_CHICKEN;
                break;
            case 25:
                this.cont = Content.CC_CLOTHES;
                break;
            case 26:
                this.cont = Content.CC_LINUX;
                break;
            case 27:
                this.cont = Content.CC_GUARD;
                break;
            case 28:
                this.cont = Content.CC_KEYBOARD;
                break;
            case 29:
                this.cont = Content.CC_GTX;
                break;
            case 30:
                this.cont = Content.CC_DBELEPHANT;
                break;
            case 31:
                this.cont = Content.CC_GLASSES;
                break;
            case 32:
                this.cont = Content.CC_FLYING;
                break;
            case 33:
                this.cont = Content.CC_MOTOR;
                break;
            case 34:
                this.cont = Content.CC_BUS;
                break;
            case 35:
                this.cont = Content.CC_LAKE;
                break;
            case 36:
                this.cont = Content.CC_MOUNTAIN;
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
    public String getColor() {
        switch(color){
            case CC_HEART:
                return "红桃";
            case CC_SQUARE:
                return "方片";
            case CC_SPADE:
                return "黑桃";
            case CC_CLUB:
                return "梅花";
        }
        return null;
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
                return "滚";
            case CC_REEXAM:
                return "重考";
            case CC_REF:
                return "小抄";
            case CC_FUCK:
                return "盗号约炮";
            case CC_SCRIPT:
                return "卖弱脚本";
            case CC_XILINX:
                return "XILINX";
            case CC_SPINPEN:
                return "转转笔";
            case CC_PTA:
                return "互评账号";
            case CC_CHICKEN:
                return "大逃杀";
            case CC_CLOTHES:
                return "女装";
            case CC_LINUX:
                return "新系统";
            case CC_GUARD:
                return "保安制服";
            case CC_KEYBOARD:
                return "红轴键盘";
            case CC_GTX:
                return "GTX显卡";
            case CC_DBELEPHANT:
                return "对象";
            case CC_GLASSES:
                return "黑框眼镜";
            case CC_FLYING:
                return "飞行模式";
            case CC_MOTOR:
                return "小龟";
            case CC_BUS:
                return "校车";
            case CC_LAKE:
                return "启真湖";
            case CC_MOUNTAIN:
                return "老和山";
            default:
                return null;
        }
    }
    public Content getIdx() {
        return cont;
    }
    public String toString() {
        return getColor() + number + getCont();
    }
}
