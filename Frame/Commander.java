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
 		return masterName.toString();
 	}
 	
 	protected int chooseOne() {
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
 			System.out.println("�ж�" + judgeCard.cont.get(i).getCont() + ":");
 			if(Table.askProblem()) {
 				if(judgeCard.cont.get(i).getIdx() == Card.Content.CC_CALLROLL) {
 					for(int k = 1; k <= Table.num; k++) {
 						if(Table.player[(seatNum + k)%Table.num]==null ||
 							Table.player[(seatNum + k)%Table.num].judgeCard.have(Card.Content.CC_CALLROLL))continue;
 						Table.player[(seatNum + k)%Table.num].receiveJudge(judgeCard.cont.get(i));
 					}
 				}
 				continue;
 			}
 			
 			Card j = Table.exeJudge();
 			
 			switch(judgeCard.cont.get(i).getIdx()){
 			case CC_NONET:
 				if(j.getColor()!="÷��") {
 					rt.push(judgeCard.cont.get(i));
 					System.out.println("�����ɹ���");
 				}
 				else {
 					System.out.println("����������");
 				}
 				break;
 			case CC_NIGHTPLAY:
 				if(j.getColor()!="����") {
 					rt.push(judgeCard.cont.get(i));
 	 				System.out.println("˯���ˣ�");
 				}
 				else {
 					System.out.println("��˯����");
 				}
 				break;
 			case CC_CALLROLL:
 				if(j.getColor()=="����" && j.getNum() >= 2 &&j.getNum() <= 9) {
 					rt.push(judgeCard.cont.get(i));
 	 				System.out.println("��������");
 	 				lessBlood(3);
 				}
 				else {
 					for(int k = 1; k <= Table.num; k++) {
 						if(Table.player[(seatNum + k)%Table.num]==null ||
 							Table.player[(seatNum + k)%Table.num].judgeCard.have(Card.Content.CC_CALLROLL))continue;
 						Table.player[(seatNum + k)%Table.num].receiveJudge(judgeCard.cont.get(i));
 					}
 					System.out.println("�������£�");
 				}
 				
 				break;
 			case CC_REF:
 				if(j.getColor()=="��Ƭ") {
 					rt.push(judgeCard.cont.get(i));
 	 				System.out.println("�Ͻ�����");
 				}
 				else {
 					System.out.println("��ѽ�����ˣ�");
 				}
			default:
				break;
 			}
 		}
 		judgeCard = new Deck();
 		return rt;
 	}
	public void getEquip() {
		if(equipCard.cont.get(0) != null)
			System.out.println("����: " + equipCard.cont.get(0).getCont());
		if(equipCard.cont.get(1) != null)
			System.out.println("����: " + equipCard.cont.get(1).getCont());
		if(equipCard.cont.get(2) != null)
			System.out.println("-1: " + equipCard.cont.get(2).getCont());
		if(equipCard.cont.get(3) != null)
			System.out.println("+1: " + equipCard.cont.get(3).getCont());
	}
 	public void startTurn() {
 		
 	}
	public void getCard(Card c) {
		handCard.push(c);
	}
	public Card lostCard(int n) {
		if(n<handCard.tmpNum)
			return handCard.pop(n);
		else {
			int en = n-handCard.tmpNum;
			for(int i = 0; i < 4; i++) {
				if(equipCard.getCard(i)!=null) {
					if(en==0) return lostEquip(i);
					en--;
				}
			}
			return null;
		}
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
		if(c==handCard.tmpNum) {
			if(equipCard.cont.get(0).getIdx()==Card.Content.CC_SPINPEN) {
				int a = chooseOne();
				Table.real.push(handCard.pop(a));
				int b = chooseOne();
				Table.real.push(handCard.pop(b));
				Table.action = new Card(0, Card.Content.CC_PREVENT.ordinal(), Card.Color.CC_NONE.ordinal());
				spin();
				return;
			}
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
		killed = false;
		return true;
	}
	public int cardNum() {
		int ec = 0;
		for(int i = 0; i < 4; i++){
			if(equipCard.getCard(i)!=null)ec++;
		}
		return handCard.tmpNum + ec;
	}
	public void beObj() {
		
	}
	public void endObj() {
		
	}
	public void showCard() {
		System.out.println("����Ҫչʾһ������: ");
		int c = chooseOne();
		Table.action = handCard.cont.get(c);
	}
	public boolean weakThrow() {
		System.out.println("չʾ����Ϊ: " +
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
	public Card changeJudge() {
		return null;
	}
	public Card lostEquip(int idx) {
		if(idx==1&&equipCard.cont.get(1)!=null &&equipCard.cont.get(1).getIdx() == Card.Content.CC_DBELEPHANT) {
			moreBlood();
			System.out.println(masterName.toString() + "ʧ���ˣ�������ߣ�Ϊ" + tmpBlood);
		}
		if(idx==1&&equipCard.cont.get(1)!=null &&equipCard.cont.get(1).getIdx() == Card.Content.CC_GLASSES) {
			if(tmpBlood==0) {
				System.out.println(masterName.toString() + "ʧȥ�˺ڿ��۾����������ˡ�");
				Table.dying = seatNum;
			}
		}
		Card rt = equipCard.cont.get(idx);
		equipCard.cont.set(0, null);
		return rt;
	}
	public boolean failKill() {
		if(equipCard.have(Card.Content.CC_PTA)) {
			System.out.println("�Ƿ��¼PTA?");
			int a = chooseOne();
			if(a==-1)return false;
			int b = chooseOne();
			if(b==-1)return false;
			handCard.pop(a);
			handCard.pop(b);
			Table.action = new Card(0, 0, 0);
			Table.kill = Effect.CE_NODENY;
			return true;
		}
		return false;
	}
	public void succeedKill(int obj) {
		Scanner s = new Scanner(System.in);
		if(equipCard.cont.get(0) != null && equipCard.cont.get(0).getIdx()==Card.Content.CC_LINUX) {
			System.out.println("�Ƿ������װ��ϵͳ��");
			if(s.nextInt()!=-1) {
				System.out.println("��������ʽ����ʽ���ˣ�");
				System.out.println("The one you choose have " + Table.player[obj].cardNum() + " card(s).");
				Table.player[obj].moreBlood();
				Table.player[obj].lostCard(hackFile(Table.player[obj].cardNum()));
				Table.player[obj].lostCard(hackFile(Table.player[obj].cardNum()));
			}
		}
		if(equipCard.cont.get(0) != null && equipCard.cont.get(0).getIdx()==Card.Content.CC_GUARD) {
			System.out.println("�Ƿ�Ҫװ�ɱ�������");
			if(s.nextInt()!=-1) {
				System.out.println("�峡�ˣ�");
				System.out.println("Choose 1 for +1 or -1 for -1.");
				if(s.nextInt()==-1) {
					if(Table.player[obj].equipCard.cont.get(2)!=null)
						Table.player[obj].lostEquip(2);
				}
				if(s.nextInt()==1) {
					if(Table.player[obj].equipCard.cont.get(3)!=null)
						Table.player[obj].lostEquip(3);
				}
			}
		}
	}
	public void moreKill() {
		
	}
	public boolean receiveKill() {
		int c;
		Scanner s = new Scanner(System.in);
		switch(Table.action.getIdx()) {
		case CC_PREVENT:
			System.out.println("" + Table.pro + "��λ:" + masterName.toString() + " ��ѧ�ˣ�");
			if(equipCard.cont.get(1) != null && equipCard.cont.get(1).getIdx()==Card.Content.CC_KEYBOARD &&
					!(Table.player[Table.pro].equipCard.have(Card.Content.CC_XILINX))) {
				System.out.println("�Ƿ�ʹ�ú�����̣�");
				if(s.nextInt()!=-1) {
					Card j = Table.exeJudge();
					if(j.getColor()=="����"||j.getColor()=="��Ƭ")return false;
				}
			}
			c = chooseOne();
			if(c==-1) {
				lessBlood();
				return true;
			}
			if(handCard.cont.get(c).getIdx()==Card.Content.CC_DENY){
				System.out.println(masterName.toString() + ": " + handCard.cont.get(c).getCont());
				handCard.pop(c);
			}
			break;
		case CC_TOREVIEW:
			System.out.println("" + Table.pro + "��λ: " + masterName.toString() + "һ����ϰȥ��");
			if(equipCard.cont.get(1) != null && equipCard.cont.get(1).getIdx()==Card.Content.CC_KEYBOARD &&
					!(Table.player[Table.pro].equipCard.have(Card.Content.CC_XILINX))) {
				System.out.println("�Ƿ�ʹ�ú�����̣�");
				if(s.nextInt()!=-1) {
					Card j = Table.exeJudge();
					if(j.getColor()=="����"||j.getColor()=="��Ƭ")return false;
				}
			}
			c = chooseOne();
			if(c==-1) {
				lessBlood();
				return true;
			}
			if(handCard.cont.get(c).getIdx()==Card.Content.CC_DENY){
				System.out.println(masterName.toString() + ": " + handCard.cont.get(c).getCont());
				handCard.pop(c);
			}
			break;
		default:
			break;
		}
		return false;
	}
	public boolean receiveKillFrom(Effect e) {
		int c;
		Scanner s = new Scanner(System.in);
		if(equipCard.cont.get(1) != null && equipCard.cont.get(1).getIdx()==Card.Content.CC_GTX &&
			!(Table.player[Table.pro].equipCard.have(Card.Content.CC_XILINX))) {
			if(Table.action.getColor()=="����" || Table.action.getColor()=="÷��")
				return false;
		}
		
		if((masterSex==Sex.CS_BOY&&Table.player[Table.pro].masterSex==Sex.CS_GIRL) ||
			(masterSex==Sex.CS_GIRL&&Table.player[Table.pro].masterSex==Sex.CS_BOY)) {
			System.out.println("Ůװ�ܺÿ��ǰɣ���ѡ����һ���ƻ��߶Է���һ����(-1):");
			int ch = chooseOne();
			if(ch==-1) {
				Table.player[Table.pro].getCard(Table.newDeck.pop());
			}
			else {
				handCard.pop(ch);
			}
		}
		
		switch(e){
		case CE_DISPOSEONE:
			switch(Table.action.getIdx()) {
			case CC_PREVENT:
				System.out.println("" + Table.pro + "��λ:" + masterName.toString() + " ��ѧ�ˣ�");
				break;
			case CC_TOREVIEW:
				System.out.println("" + Table.pro + "��λ: " + masterName.toString() + "һ����ϰȥ��");
				break;
			default:
				break;
			}
			if(equipCard.cont.get(1) != null && equipCard.cont.get(1).getIdx()==Card.Content.CC_KEYBOARD &&
					!(Table.player[Table.pro].equipCard.have(Card.Content.CC_XILINX))) {
				System.out.println("�Ƿ�ʹ�ú�����̣�");
				if(s.nextInt()!=-1) {
					Card j = Table.exeJudge();
					if(j.getColor()=="����"||j.getColor()=="��Ƭ")return false;
				}
			}
			c = chooseOne();
			if(c==-1) {
				lessBlood();
				return true;
			}
			handCard.pop(c);
			c = chooseOne();
			if(c==-1) {
				lessBlood();
				return true;
			}
			if(handCard.cont.get(c).getIdx()==Card.Content.CC_DENY){
				System.out.println(masterName.toString() + ": " + handCard.cont.get(c).getCont());
				handCard.pop(c);
			}
			break;
		case CE_NODENY:
			lessBlood();
			return true;
		default:
			return receiveKill();
		}
		return false;
	}
	public void receiveJudge(Card c) {
		judgeCard.push(c);
	}
	public boolean needKill(){
		int c;
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
			System.out.println("" + Table.pro + "��λ: " + masterName.toString() + "һ��Է�ȥ��");
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
		System.out.println("����͸���ˣ���ѡ������Ҫ�ġ�");
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
	public boolean beFucked() {
		System.out.println(Table.player[Table.pro].masterName + " wang to fuck you.");
		int c = chooseOne();
		if(c!=-1 && handCard.cont.get(c).getIdx() == Card.Content.CC_PREVENT) {
			handCard.pop(c);
			return true;
		}
		return false;
	}
	public boolean askProblem(){
		System.out.println(masterName.toString() + "�Ƿ���������");
		int c = chooseOne();
		if(c==-1)return false;
		if(handCard.cont.get(c).getIdx()==Card.Content.CC_NOPROBLEM) {
			System.out.println("����");
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
		if(equipCard.cont.get(1)!=null &&equipCard.cont.get(1).getIdx() == Card.Content.CC_DBELEPHANT &&
				!(Table.player[Table.pro].equipCard.have(Card.Content.CC_XILINX))) {
			tmpBlood-=1;
			System.out.println(masterName.toString() + "�õ��˶���İ�ο����ʧ��Ϊ1��Ŀǰ����Ϊ" + tmpBlood);
		}
		else {
			tmpBlood-=n;
		}
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
		
		if(killed&&!equipCard.have(Card.Content.CC_SCRIPT)) {
			System.out.println("����Ϊ���Ǹ���ѽ�������ѧ�˱�ѧ�˵ġ�");
			return;
		}
		
		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		if(handCard.tmpNum==1 && equipCard.cont.get(0) != null &&
				equipCard.cont.get(0).getIdx() == Card.Content.CC_CHICKEN) {
			if((o=s.nextInt()) != -1) {
				Table.con = o;
				if((o=s.nextInt()) != -1) {
					Table.chk = o;
				}
			}
		}
		if(Table.calDist(seatNum, o)>Table.killDist(equipCard.cont.get(0))){
			System.out.println("Too far away!");
			Table.action = null;
			Table.obj = -1;
			return;
		}
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("��ѧ�ˣ�");
		handCard.pop(c);
		
		killed = true;
 	}
 	protected void spin() {
		Scanner s = new Scanner(System.in);
		int o;
		
		if(killed&&!equipCard.have(Card.Content.CC_SCRIPT)) {
			System.out.println("����Ϊ���Ǹ���ѽ�������ѧ�˱�ѧ�˵ġ�");
			return;
		}
		
		o = s.nextInt();
		Table.obj = o;
		if(Table.calDist(seatNum, o)>Table.killDist(equipCard.cont.get(0))){
			System.out.println("Too far away!");
			Table.action = null;
			Table.obj = -1;
			return;
		}
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("��ѧ�ˣ�");
		
		killed = true;
 	}
 	protected void study(int c) {
		if(tmpBlood<fullBlood) {
			tmpBlood++;
			handCard.pop(c);
		}
		else {
			System.out.println("�㶼5.0�ˣ���׼��ѧ�ˣ�");
		}
 	}
 	protected void nonet(int c) {
		Scanner s = new Scanner(System.in);
		int o;
		
		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		if(Table.calDist(seatNum, o)>1){
			System.out.println("Too far away!");
			Table.action = null;
			Table.obj = -1;
			return;
		}
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("������");
		handCard.pop(c);
 	}
 	protected void weakshow(int c) {
		Scanner s = new Scanner(System.in);
		int o;
		
		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("������");
		handCard.pop(c);
 	}
 	protected void nightplay(int c) {
		Scanner s = new Scanner(System.in);
		int o;
		
		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("��Ϸͨ����");
		handCard.pop(c);
 	}
 	protected void worship(int c) {
		Scanner s = new Scanner(System.in);
		int o;
		
		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("����̫ǿ�ˣ�");
		handCard.pop(c);
 	}
 	protected void toeat(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("��������һ��ȥ�Ը�����");
		handCard.pop(c);
 	}
 	protected void toreview(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("����ϰ�ˣ�");
		handCard.pop(c);
 	}
 	protected void copy(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		if(Table.player[o].cardNum()==0)return;
		Table.obj = o;
		if(Table.calDist(seatNum, o)>1){
			System.out.println("Too far away!");
			Table.action = null;
			Table.obj = -1;
			return;
		}
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("������ҳ�һ�£�");
		handCard.pop(c);
 	}
 	protected void callroll(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("������");
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
			System.out.println("������Steam���ܸ�����~��");
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
		System.out.println("��ĵ����ѱ����֣�");
		handCard.pop(c);
 	}
 	protected void examleak(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("��ʦ͸������");
		handCard.pop(c);
 	}
 	protected void reexam(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("�ϴο������ϣ���׼���ؿ���");
		handCard.pop(c);
 	}
 	protected void ref(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("�����С����");
		handCard.pop(c);
 	}
 	protected void fuck(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		if(Table.player[o].equipCard.cont.get(0)==null) {
			System.out.println("��û���ߣ���Լ��Ҳû�á�");
			Table.action = null;
			return;
		}
		o = s.nextInt();
		Table.con= o;
		System.out.println(masterName.toString() + ":");
		System.out.println("�ѵ��š�");
		handCard.pop(c);
 	}
 	protected void weapon(int c) {
		System.out.println(handCard.cont.get(c).getCont() + "Equiped.");
		if(equipCard.cont.get(0) !=null &&
				equipCard.cont.get(0).getIdx().ordinal()>=20&&
				equipCard.cont.get(0).getIdx().ordinal()<=27)
			lostEquip(0);
		equipCard.cont.set(0, handCard.cont.get(c));
		handCard.pop(c);
 	}
 	protected void defender(int c) {
		System.out.println(handCard.cont.get(c).getCont() + "Equiped.");
		if(equipCard.cont.get(1) !=null &&
				equipCard.cont.get(1).getIdx().ordinal()>=28&&
				equipCard.cont.get(1).getIdx().ordinal()<=32)
			lostEquip(1);
		equipCard.cont.set(1, handCard.cont.get(c));
		handCard.pop(c);
 	}
 	protected void decdist(int c) {
		System.out.println(handCard.cont.get(c).getCont() + "Equiped.");
		if(equipCard.cont.get(2) !=null &&
				equipCard.cont.get(2).getIdx().ordinal()>=33&&
				equipCard.cont.get(2).getIdx().ordinal()<=34)
			lostEquip(2);
		equipCard.cont.set(2, handCard.cont.get(c));
		handCard.pop(c);
 	}
 	protected void incdist(int c) {
		System.out.println(handCard.cont.get(c).getCont() + "Equiped.");
		if(equipCard.cont.get(3) !=null &&
				equipCard.cont.get(3).getIdx().ordinal()>=35&&
				equipCard.cont.get(3).getIdx().ordinal()<=36)
			lostEquip(3);
		equipCard.cont.set(3, handCard.cont.get(c));
		handCard.pop(c);
 	}

}
