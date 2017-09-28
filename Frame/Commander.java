package Frame;

import java.util.Scanner;

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
	
	Name masterName;
	Group masterGroup;
	private int fullBlood;
	private int tmpBlood;
	public Deck handCard;
	public Deck equipCard;
	public Deck judgeCard;
	private int seatNum;
	
	public boolean steam;
	public boolean endTmp;
	
 	public Commander(int n, int seat) {
		switch(n) {
		case 0:
			masterName = Name.CN_GTX;
			masterGroup = Group.CG_COMPUTER;
			fullBlood = 4;
			tmpBlood = 4;
			break;
		case 1:
			masterName = Name.CN_ZRS;
			masterGroup = Group.CG_COMPUTER;
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
		
		equipCard.push(null);
		equipCard.push(null);
		equipCard.push(null);
		equipCard.push(null);
	}
 	public String getName() {
 		return masterName.toString();
 	}
 	
 	private int chooseOne() {
		System.out.println("Now you have card(s):");
		for(int i = 0; i < handCard.tmpNum; i++) {
			System.out.println("" + i + ". " + 
					handCard.cont.get(i).getColor() + handCard.cont.get(i).getNum() + handCard.cont.get(i).getCont());
		}
		System.out.println("Which one to Use(-1 for end)?");
		Scanner s = new Scanner(System.in);
		return s.nextInt();
 	}
 	
 	public Deck exeJudge() {
 		Deck rt = new Deck();
 		for(int i = 0; i < judgeCard.tmpNum; i++){
 			System.out.println("判定" + judgeCard.cont.get(i).getCont() + ":");
 			Card j = Table.newDeck.pop();
 			System.out.println("结果为: " + j.getColor() + j.getNum() + j.getCont());
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
 				}
 				else {
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
 			}
 		}
 		judgeCard = new Deck();
 		return rt;
 	}
	public void getEquip() {
		if(equipCard.cont.get(0) != null)
			System.out.println("武器: " + equipCard.cont.get(0).getCont());
		if(equipCard.cont.get(1) != null)
			System.out.println("防具: " + equipCard.cont.get(1).getCont());
		if(equipCard.cont.get(2) != null)
			System.out.println("-1: " + equipCard.cont.get(2).getCont());
		if(equipCard.cont.get(3) != null)
			System.out.println("+1: " + equipCard.cont.get(3).getCont());
	}
 	public void getCard(Card c) {
		handCard.push(c);
	}
	public void useCard() {
		endTmp = false;
		System.out.println(masterName.toString() + " is using card.");
		System.out.println("Your life is " + tmpBlood + " .");
		System.out.println("You have equipment: ");
		getEquip();
		int c = chooseOne();
		if(c==-1) {
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
		if(endTmp != true)return false;
		while(handCard.tmpNum>tmpBlood) {
			System.out.println("Now you have card(s):");
			for(int i = 0; i < handCard.tmpNum; i++) {
				System.out.println("" + i + ". " + 
						handCard.cont.get(i).getColor() + handCard.cont.get(i).getNum() + handCard.cont.get(i).getCont());
			}
			System.out.println("Choose card index to dispose:");
			Scanner s = new Scanner(System.in);
			int idx = s.nextInt();
			if(idx < 0 || idx >= handCard.tmpNum){
				System.out.println("Illegal input.");
				idx = s.nextInt();
			}
			handCard.pop(idx);
		}
		System.out.println(masterName.toString() + " end.");
		endTmp = false;
		return true;
	}
	public int cardNum() {
		return handCard.tmpNum + equipCard.tmpNum;
	}
	public Card lostCard(int n) {
		if(n<handCard.tmpNum)
			return handCard.pop(n);
		else return equipCard.pop(n-handCard.tmpNum);
	}
	public void showCard() {
		System.out.println("你需要展示一张手牌: ");
		int c = chooseOne();
		Table.action = handCard.cont.get(c);
	}
	public boolean weakThrow() {
		System.out.println("展示手牌为: " +
			Table.action.getColor() +Table.action.getNum() + Table.action.getCont());
		int c = chooseOne();
		if(c==-1)return false;
		else {
			if(handCard.cont.get(c).getColor()==Table.action.getColor()) {
				handCard.pop(c);
				return true;
			}
			else return false;
		}
	}
	public void receiveKill() {
		int c;
		System.out.println(masterName.toString() + "请出没学。");
		switch(Table.action.getIdx()) {
		case CC_PREVENT:
			System.out.println("" + Table.tmpPlayer + "号位:" + masterName.toString() + " 别学了！");
			c = chooseOne();
			if(c==-1) {
				lessBlood();
				return;
			}
			if(handCard.cont.get(c).getIdx()==Card.Content.CC_DENY){
				System.out.println(masterName.toString() + ": " + handCard.cont.get(c).getCont());
				handCard.pop(c);
			}
			break;
		case CC_TOREVIEW:
			System.out.println("" + Table.tmpPlayer + "号位: " + masterName.toString() + "一起自习去！");
			c = chooseOne();
			if(c==-1) {
				lessBlood();
				return;
			}
			if(handCard.cont.get(c).getIdx()==Card.Content.CC_DENY){
				System.out.println(masterName.toString() + ": " + handCard.cont.get(c).getCont());
				handCard.pop(c);
			}
			break;
		default:
			break;
		}
	}
	public void receiveKillFrom(Commander.Name n) {
		int c;
		switch(n){
		case CN_GTX:
			switch(Table.action.getIdx()) {
			case CC_PREVENT:
				System.out.println("" + Table.tmpPlayer + "号位:" + masterName.toString() + " 别学了！");
				c = chooseOne();
				if(c==-1) {
					lessBlood();
					return;
				}
				handCard.pop(c);
				c = chooseOne();
				if(c==-1) {
					lessBlood();
					return;
				}
				if(handCard.cont.get(c).getIdx()==Card.Content.CC_DENY){
					System.out.println(masterName.toString() + ": " + handCard.cont.get(c).getCont());
					handCard.pop(c);
				}
				break;
			case CC_TOREVIEW:
				System.out.println("" + Table.tmpPlayer + "号位: " + masterName.toString() + "一起自习去！");
				c = chooseOne();
				if(c==-1) {
					lessBlood();
					return;
				}
				handCard.pop(c);
				c = chooseOne();
				if(c==-1) {
					lessBlood();
					return;
				}
				if(handCard.cont.get(c).getIdx()==Card.Content.CC_DENY){
					System.out.println(masterName.toString() + ": " + handCard.cont.get(c).getCont());
					handCard.pop(c);
				}
				break;
			default:
				break;
			}
			break;
		default:
			receiveKill();
		}
	}
	public void receiveJudge(Card c) {
		judgeCard.push(c);
	}
	public boolean needKill(){
		int c;
		System.out.println(masterName.toString() + "请出别学了。");
		switch(Table.action.getIdx()) {
		case CC_WORSHIP:
			c = chooseOne();
			if(c==-1) {
				lessBlood();
				return false;
			}
			else if(handCard.cont.get(c).getIdx()==Card.Content.CC_PREVENT){
				System.out.println(masterName.toString() + ": " + handCard.cont.get(c).getCont());
				handCard.pop(c);
				return true;
			}
			else {
				lessBlood();
				return false;
			}
		case CC_TOEAT:
			System.out.println("" + Table.tmpPlayer + "号位: " + masterName.toString() + "一起吃饭去！");
			c = chooseOne();
			if(c==-1) {
				lessBlood();
				return false;
			}
			else if(handCard.cont.get(c).getIdx()==Card.Content.CC_PREVENT){
				System.out.println(masterName.toString() + ": " + handCard.cont.get(c).getCont());
				handCard.pop(c);
				return true;
			}
			else {
				lessBlood();
				return false;
			}
		default:
			return false;
		}
	}
	public int copyCode(int n) {
		System.out.println("Choose the card index that you want to copy: The one you choose have " + n + " card(s).");
		Scanner s = new Scanner(System.in);
		int rt;
		while(true) {
			rt = s.nextInt();
			if(rt>=0 && rt<n)break;
			System.out.println("Out of range!");
		}
		return rt;
	}
	public int hackFile(int n){
		System.out.println("Choose the card index that you want to delete: The one you choose have " + n + " card(s).");
		Scanner s = new Scanner(System.in);
		int rt;
		while(true) {
			rt = s.nextInt();
			if(rt>=0 && rt<n)break;
			System.out.println("Out of range!");
		}
		return rt;
	}
	public void changeSteam() {
		steam = !steam;
	}
	public int examLeak(Deck d) {
		System.out.println("考试透题了，请选择你想要的。");
		for(int i = 0; i < d.tmpNum; i++) {
			System.out.println("" + i + ". " + 
					d.cont.get(i).getColor() + d.cont.get(i).getNum() + d.cont.get(i).getCont());
		}
		Scanner s = new Scanner(System.in);
		int rt;
		while(true) {
			rt = s.nextInt();
			if(rt >= 0 && rt < d.tmpNum)break;
			System.out.println("Out of range!");
		}
		return rt;
	}
	public boolean askProblem(){
		System.out.println("是否让他滚？");
		int c = chooseOne();
		if(c==-1)return false;
		if(handCard.cont.get(c).getIdx()==Card.Content.CC_NOPROBLEM) {
			System.out.println("滚！");
			handCard.pop(c);
			return true;
		}
		return false;
	}
	public boolean askSave() {
		System.out.println("" + Table.dying + " is dying, save him?");
		int c = chooseOne();
		if(c==-1)return false;
		switch(handCard.cont.get(c).getIdx()){
		case CC_STUDY:
			handCard.pop(c);
			return true;
		case CC_STAYUP:
			if(Table.dying==seatNum) {
				handCard.pop(c);
				return true;
			}
		default:
			break;
		}
		return false;
	}
 	public int moreBlood() {
		if(tmpBlood >= fullBlood)return fullBlood;
		else tmpBlood++;
		return tmpBlood;
	}
	public int lessBlood() {
		tmpBlood--;
		System.out.println(masterName.toString() + " is hurt.");
		System.out.println("Now " + tmpBlood + " left.");
		if(tmpBlood <= 0)Table.dying = seatNum;
		return tmpBlood;
	}
	public int lessBlood(int n) {
		tmpBlood-=n;
		System.out.println(masterName.toString() + " is hurt.");
		System.out.println("Now " + tmpBlood + " left.");
		if(tmpBlood <= 0)Table.dying = seatNum;
		return tmpBlood;
	}
 	public void dieAnyway() {
		 System.out.println(masterName.toString() + " died.");
	}
 	
 	protected void prevent(int c) {
		Scanner s = new Scanner(System.in);
		int o;
		
		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("别学了！");
		handCard.pop(c);
 	}
 	protected void study(int c) {
		if(tmpBlood<fullBlood) {
			tmpBlood++;
			handCard.pop(c);
		}
		else {
			System.out.println("你都5.0了，不准再学了！");
		}
 	}
 	protected void nonet(int c) {
		Scanner s = new Scanner(System.in);
		int o;
		
		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("断网！");
		handCard.pop(c);
 	}
 	protected void weakshow(int c) {
		Scanner s = new Scanner(System.in);
		int o;
		
		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("卖弱！");
		handCard.pop(c);
 	}
 	protected void nightplay(int c) {
		Scanner s = new Scanner(System.in);
		int o;
		
		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("游戏通宵！");
		handCard.pop(c);
 	}
 	protected void worship(int c) {
		Scanner s = new Scanner(System.in);
		int o;
		
		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("大佬太强了！");
		handCard.pop(c);
 	}
 	protected void toeat(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("来来来，一起去吃个饭！");
		handCard.pop(c);
 	}
 	protected void toreview(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("来自习了！");
		handCard.pop(c);
 	}
 	protected void copy(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		if(Table.player[o].cardNum()==0)return;
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("代码给我抄一下！");
		handCard.pop(c);
 	}
 	protected void callroll(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("点名！");
		handCard.pop(c);
 	}
 	protected void steam(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		if(o==-1) {
			handCard.push(Table.newDeck.pop());
			handCard.pop(c);
		}
		else {
			Table.obj = o;
			o = s.nextInt();
			Table.con= o;
			System.out.println(masterName.toString() + ":");
			System.out.println("给你们Steam介绍个好友~！");
			handCard.pop(c);
		}
 	}
 	protected void download(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		handCard.pop(c);
 	}
 	protected void hack(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		if(Table.player[o].cardNum()==0)return;
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("你的电脑已被入侵！");
		handCard.pop(c);
 	}
 	protected void examleak(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("老师透题啦！");
		handCard.pop(c);
 	}
 	protected void reexam(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("上次考试作废，请准备重考！");
		handCard.pop(c);
 	}
 	protected void ref(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("给你个小抄！");
		handCard.pop(c);
 	}
 	protected void fuck(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		o = s.nextInt();
		Table.con= o;
		System.out.println(masterName.toString() + ":");
		System.out.println("已盗号。");
		handCard.pop(c);
 	}
 	protected void weapon(int c) {
		System.out.println(handCard.cont.get(c).getCont() + "Equiped.");
		if(equipCard.cont.get(0) !=null &&
				equipCard.cont.get(0).getIdx().ordinal()>=20&&
				equipCard.cont.get(0).getIdx().ordinal()<=27)
			equipCard.cont.set(0, null);
		equipCard.cont.set(0, handCard.cont.get(c));
		handCard.pop(c);
 	}
 	protected void defender(int c) {
		System.out.println(handCard.cont.get(c).getCont() + "Equiped.");
		if(equipCard.cont.get(1) !=null &&
				equipCard.cont.get(1).getIdx().ordinal()>=28&&
				equipCard.cont.get(1).getIdx().ordinal()<=32)
			equipCard.cont.set(1, null);
		equipCard.cont.set(1, handCard.cont.get(c));
		handCard.pop(c);
 	}
 	protected void decdist(int c) {
		System.out.println(handCard.cont.get(c).getCont() + "Equiped.");
		if(equipCard.cont.get(2) !=null &&
				equipCard.cont.get(2).getIdx().ordinal()>=33&&
				equipCard.cont.get(2).getIdx().ordinal()<=34)
			equipCard.cont.set(2, null);
		equipCard.cont.set(2, handCard.cont.get(c));
		handCard.pop(c);
 	}
 	protected void incdist(int c) {
		System.out.println(handCard.cont.get(c).getCont() + "Equiped.");
		if(equipCard.cont.get(3) !=null &&
				equipCard.cont.get(3).getIdx().ordinal()>=35&&
				equipCard.cont.get(3).getIdx().ordinal()<=36)
			equipCard.cont.set(3, null);
		equipCard.cont.set(3, handCard.cont.get(c));
		handCard.pop(c);
 	}

}
