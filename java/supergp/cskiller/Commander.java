package supergp.cskiller;

import android.content.Context;
import android.view.WindowManager;
import android.widget.RelativeLayout;
import android.widget.Toast;

public class Commander {
    public enum Name {
        CN_GTX,
        CN_ZRS
    }
    public enum Group {
        CG_COMPUTER,
        CG_SOFTWARE,
        CG_ZKZ,
        CG_OTHER
    }
    public enum Sex {
        CS_UNKNOWN,
        CS_BOY,
        CS_GIRL
    }

    public enum Effect {
        CE_NOEFFECT,
        CE_NODENY,
        CE_DISPOSEONE,
    }

    public Name masterName;
    public Sex masterSex;
    protected Group masterGroup;
    protected int fullBlood;
    protected int tmpBlood;
    public Deck handCard;
    public Deck equipCard;
    public Deck judgeCard;
    protected int seatNum;

    public boolean steam;
    public boolean killed;
    public boolean endTmp;

    public Commander(int n, int seat) {
        switch(n) {
            case 0:
                masterName = Name.CN_GTX;
                masterGroup = Group.CG_COMPUTER;
                masterSex = Sex.CS_BOY;
                fullBlood = 4;
                tmpBlood = 4;
                break;
            case 1:
                masterName = Name.CN_ZRS;
                masterGroup = Group.CG_COMPUTER;
                masterSex = Sex.CS_BOY;
                fullBlood = 4;
                tmpBlood = 4;
                break;
        }
        handCard = new Deck();
        equipCard = new Deck();
        judgeCard = new Deck();
        seatNum = seat;
        endTmp = false;
        steam = false;
        killed = false;

        equipCard.push(null);
        equipCard.push(null);
        equipCard.push(null);
        equipCard.push(null);
    }
    public String getName() {
        switch (masterName){
            case CN_GTX:return "高天祥";
            case CN_ZRS:return "朱瑞昇";
            default:return masterName.toString();
        }
    }

    public void getCard(Card c) {
        RelativeLayout layout = (RelativeLayout)Main.inter.findViewById(R.id.main);

        if(seatNum==0) {
            Main.card[handCard.tmpNum] = new Surface(Main.inter, handCard.tmpNum);
            layout.addView(Main.card[handCard.tmpNum]);

            if(handCard.tmpNum < 3)
                Main.card[handCard.tmpNum].position(handCard.tmpNum*100);
            else {
                for(int i = 0; i <= handCard.tmpNum; i++) {
                    Main.card[i].position(i * 260 / handCard.tmpNum);
                }
            }
            Main.card[handCard.tmpNum].set(c.getIdx().ordinal(), c.getNum()+1, c.color.ordinal());
            handCard.push(c);
        }
    }
    public Card lostCard(int n) {
        RelativeLayout layout = (RelativeLayout)Main.inter.findViewById(R.id.main);

        Card ret;
        if(seatNum==0) {
            layout.removeView(Main.card[n]);
            Main.card[n] = null;
            for(int i = n; i < handCard.tmpNum - 1; i++) {
                Main.card[i] = Main.card[i+1];
            }
            ret = handCard.pop(n);
            if(handCard.tmpNum < 4) {
                for(int i = 0; i < handCard.tmpNum; i++) {
                    Main.card[i].position(i*100);
                }
            }
            else {
                for(int i = 0; i < handCard.tmpNum; i++) {
                    Main.card[i].position(i * 260 / handCard.tmpNum);
                }
            }
        }
        else {
            ret = handCard.pop(n);
        }

        return ret;
    }

    public void startTurn() {

    }
    public Deck exeJudge() {
        Deck rt = new Deck();
        /*for(int i = 0; i < judgeCard.tmpNum; i++){
            System.out.println("判定" + judgeCard.cont.get(i).getCont() + ":");
            if(Main.table.askProblem()) {
                if(judgeCard.cont.get(i).getIdx() == Card.Content.CC_CALLROLL) {
                    for(int k = 1; k <= Main.table.num; k++) {
                        if(Main.table.player[(seatNum + k)%Main.table.num]==null ||
                                Main.table.player[(seatNum + k)%Main.table.num].judgeCard.have(Card.Content.CC_CALLROLL))continue;
                        Main.table.player[(seatNum + k)%Main.table.num].receiveJudge(judgeCard.cont.get(i));
                    }
                }
                continue;
            }

            Card j = Main.table.exeJudge();

            switch(judgeCard.cont.get(i).getIdx()){
                case CC_NONET:
                    if(j.getColor()!="梅花") {
                        rt.push(judgeCard.cont.get(i));
                        System.out.println("断网成功！");
                    }
                    else {
                        System.out.println("网络正常！");
                    }
                    break;
                case CC_NIGHTPLAY:
                    if(j.getColor()!="红桃") {
                        rt.push(judgeCard.cont.get(i));
                        System.out.println("睡起嗨！");
                    }
                    else {
                        System.out.println("早睡早起！");
                    }
                    break;
                case CC_CALLROLL:
                    if(j.getColor()=="黑桃" && j.getNum() >= 2 &&j.getNum() <= 9) {
                        rt.push(judgeCard.cont.get(i));
                        System.out.println("点名啦！");
                        lessBlood(3);
                    }
                    else {
                        for(int k = 1; k <= Main.table.num; k++) {
                            if(Main.table.player[(seatNum + k)%Main.table.num]==null ||
                                    Main.table.player[(seatNum + k)%Main.table.num].judgeCard.have(Card.Content.CC_CALLROLL))continue;
                            Main.table.player[(seatNum + k)%Main.table.num].receiveJudge(judgeCard.cont.get(i));
                        }
                        System.out.println("今日无事！");
                    }

                    break;
                case CC_REF:
                    if(j.getColor()=="方片") {
                        rt.push(judgeCard.cont.get(i));
                        System.out.println("赶紧抄！");
                    }
                    else {
                        System.out.println("哎呀抄错了！");
                    }
                default:
                    break;
            }
        }*/
        judgeCard = new Deck();
        return rt;
    }
    public void useCard() {
        int c = -1;

        endTmp = false;

        if(Main.sel!=-1)c = Main.sel;
        else return;

        if(c==-2) {
            endTmp = true;
            return;
        }
        switch(handCard.cont.get(c).getIdx()){
            case CC_PREVENT:
                prevent(c);
                break;
            case CC_STUDY:
                study(c);
                break;
            case CC_NONET:
                nonet(c);
                break;
            case CC_WEAKSHOW:
                weakshow(c);
                break;
            case CC_NIGHTPLAY:
                nightplay(c);
                break;
            case CC_WORSHIP:
                worship(c);
                break;
            case CC_TOEAT:
                toeat(c);
                break;
            case CC_TOREVIEW:
                toreview(c);
                break;
            case CC_COPY:
                copy(c);
                break;
            case CC_CALLROLL:
                callroll(c);
                break;
            case CC_STEAM:
                steam(c);
                break;
            case CC_DOWNLOAD:
                download(c);
                break;
            case CC_HACK:
                hack(c);
                break;
            case CC_EXAMLEAK:
                examleak(c);
                break;
            case CC_REEXAM:
                reexam(c);
                break;
            case CC_REF:
                ref(c);
                break;
            case CC_FUCK:
                fuck(c);
                break;
            case CC_SCRIPT:
            case CC_XILINX:
            case CC_SPINPEN:
            case CC_PTA:
            case CC_CHICKEN:
            case CC_CLOTHES:
            case CC_LINUX:
            case CC_GUARD:
                weapon(c);
                break;
            case CC_KEYBOARD:
            case CC_GTX:
            case CC_DBELEPHANT:
            case CC_GLASSES:
            case CC_FLYING:
                defender(c);
                break;
            case CC_MOTOR:
            case CC_BUS:
                decdist(c);
                break;
            case CC_LAKE:
            case CC_MOUNTAIN:
                incdist(c);
                break;
            default:
                break;
        }
    }
    public boolean endUse() {
        int c = -1;

        if(Main.sel >= 0)c = Main.sel;
        else return false;


        if(handCard.tmpNum > tmpBlood) {
            Main.lcState = Main.lostCard.LC_REGULAR;
        }
        else {
            endTmp = false;
            killed = false;
            return true;
        }
        return false;
    }

    private void prevent(int c) {
        if(killed&&!equipCard.have(Card.Content.CC_SCRIPT)) {
            /*Toast.makeText(Main.inter, "你以为你是高神呀？天天别学了别学了的。",
                    Toast.LENGTH_SHORT).show();*/
            return;
        }
        Main.action = handCard.cont.get(c);
        int o = 1 - seatNum;
        Main.obj = o;

        if(Main.calDist(seatNum, o)>Main.killDist(equipCard.cont.get(0))){
            Toast.makeText(Main.inter, "太远了你联系不到他。",
                    Toast.LENGTH_SHORT).show();
            Main.action = null;
            Main.obj = -1;
            return;
        }
        /*Toast.makeText(Main.inter, getName() + "对" + Main.player[o].masterName.toString() + ":别学了！",
                Toast.LENGTH_SHORT).show();*/
        Main.lcState = Main.lostCard.LC_USE;

        killed = true;
    }
    protected void study(int c) {

    }
    protected void nonet(int c) {

    }
    protected void weakshow(int c) {

    }
    protected void nightplay(int c) {

    }
    protected void worship(int c) {

    }
    protected void toeat(int c) {

    }
    protected void toreview(int c) {

    }
    protected void copy(int c) {

    }
    protected void callroll(int c) {

    }
    protected void steam(int c) {

    }
    protected void download(int c) {

    }
    protected void hack(int c) {

    }
    protected void examleak(int c) {

    }
    protected void reexam(int c) {

    }
    protected void ref(int c) {

    }
    protected void fuck(int c) {

    }
    protected void weapon(int c) {

    }
    protected void defender(int c) {

    }
    protected void decdist(int c) {

    }
    protected void incdist(int c) {

    }
}
