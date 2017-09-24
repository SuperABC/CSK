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
	
	private Name masterName;
	private Group masterGroup;
	private int fullBlood;
	private int tmpBlood;
	private Deck handCard;
	private Deck equipCard;
	private Deck judgeCard;
	private int seatNum;
	
	public boolean endTmp;
	
 	public Commander(int n, int seat) {
		switch(n) {
		case 0:
			masterName = Name.CN_GTX;
			masterGroup = Group.CG_COMPUTER;
			fullBlood = 4;
			tmpBlood = 4;
			handCard = new Deck();
			equipCard = new Deck();
			judgeCard = new Deck();
			seatNum = seat;
			break;
		case 1:
			masterName = Name.CN_ZRS;
			masterGroup = Group.CG_COMPUTER;
			fullBlood = 4;
			tmpBlood = 4;
			handCard = new Deck();
			equipCard = new Deck();
			judgeCard = new Deck();
			seatNum = seat;
			break;
		}
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
 			case 3:
 				if(j.getColor()=="梅花")rt.push(judgeCard.cont.get(i));
 				System.out.println("断网成功！");
 				break;
 			}
 		}
 		judgeCard = new Deck();
 		return rt;
 	}
	public void getCard(Card c) {
		handCard.push(c);
	}
	public void useCard() {
		endTmp = false;
		System.out.println(masterName.toString() + " is using card.");
		System.out.println("Your life is " + tmpBlood + " .");
		int c = chooseOne();
		if(c==-1) {
			endTmp = true;
			return;
		}
		int o;
		Scanner s = new Scanner(System.in);
		switch(handCard.cont.get(c).getIdx()){
		case 0:
			Table.action = handCard.cont.get(c);
			o = s.nextInt();
			Table.obj = o;
			System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
			System.out.println("别学了！");
			handCard.pop(c);
			break;
		case 2:
			if(tmpBlood<fullBlood) {
				tmpBlood++;
				handCard.pop(c);
			}
			else {
				System.out.println("你都5.0了，不准再学了！");
			}
			break;
		case 4:
			Table.action = handCard.cont.get(c);
			o = s.nextInt();
			Table.obj = o;
			System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
			System.out.println("断网！");
			handCard.pop(c);
			break;
		case 5:
			Table.action = handCard.cont.get(c);
			o = s.nextInt();
			Table.obj = o;
			System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
			System.out.println("卖弱！");
			handCard.pop(c);
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
		return handCard.tmpNum;
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
			if(handCard.cont.get(c).getColor()==Table.action.getColor())return true;
			else return false;
		}
	}
	public void receiveKill() {
		switch(Table.action.getIdx()) {
		case 0:
			System.out.println("" + Table.tmpPlayer + "号位:" + masterName.toString() + " 别学了！");
			int c = chooseOne();
			if(c==-1) {
				tmpBlood--;
				if(tmpBlood==0) {
					Table.dying = seatNum;
				}
				return;
			}
			if(handCard.cont.get(c).getIdx()==1){
				System.out.println(masterName.toString() + ": " + handCard.cont.get(c).getCont());
				handCard.pop(c);
			}
		}
	}
	public void receiveJudge(Card c) {
		judgeCard.push(c);
	}
	public boolean askSave() {
		System.out.println("" + Table.dying + " is dying, save him?");
		int c = chooseOne();
		switch(handCard.cont.get(c).getIdx()){
		case 2:
			handCard.pop(c);
			return true;
		case 3:
			if(Table.dying==seatNum) {
				handCard.pop(c);
				return true;
			}
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
		if(tmpBlood <= 0)Table.dying = seatNum;
		return tmpBlood;
	}
 	public void dieAnyway() {
		 System.out.println(masterName.toString() + " died.");
	}
}
