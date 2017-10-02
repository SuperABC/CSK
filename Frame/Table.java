package Frame;

import java.util.Scanner;

import Frame.Commander.Effect;
import Killer.GTX;
import Killer.ZRS;

public class Table {
	public static Commander[] player = new Commander[8];
	public static int num = 2;
	public static Deck newDeck = new Deck();
	public static Deck exDeck = new Deck();
	private static int state = 0;
	
	public static Deck real = new Deck();
	public static Card action = null;
	public static int pro = -1;
	public static int obj = -1;
	public static int con = -1;
	public static int chk = -1;
	public static Effect kill = Commander.Effect.CE_NOEFFECT;
	public static Effect review = Commander.Effect.CE_NOEFFECT;
	
	public static boolean judge = true, get = true, use = true, dispose = true;
	public static int dying = -1;
	
	public static int tmpPlayer = 0;
	
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		System.out.println("Welcome to CS Killer, now choose a commander.");
		System.out.println("0.GTX    1.ZRS    2.CZZ    3.SZL");
		int role;
		role= s.nextInt();
		switch(role) {
		case 0:
			player[0] = new GTX(0, 0);
			break;
		case 1:
			player[0] = new ZRS(1, 0);
			break;
		default:
			System.out.println("Wrong input!");
			break;
		}
		System.out.println("Seat 0 is " + player[0].getName());
		System.out.println("Now choose another commander.");
		System.out.println("0.GTX    1.ZRS    2.CZZ    3.SZL");
		role = s.nextInt();
		switch(role) {
		case 0:
			player[1] = new GTX(0, 1);
			break;
		case 1:
			player[1] = new ZRS(1, 1);
			break;
		default:
			System.out.println("Wrong input!");
			break;
		}
		System.out.println("Seat 1 is " + player[1].getName());
		newDeck.shuffleAll();
		for(int i = 0; i < 8; i++) {
			if(player[i]!=null) {
				for(int j = 0; j < 4; j++) {
					player[i].getCard(newDeck.pop());
				}
			}
		}
		
		while(notEnd()) {
			state = 0;
			player[tmpPlayer].startTurn();
			
			state = 1;
			Deck j = new Deck();
			if(judge)
				j = player[tmpPlayer].exeJudge();
			if(j.have(Card.Content.CC_CALLROLL)) {
				player[tmpPlayer].lessBlood(3);
			}
			askSave();
			if(j.have(Card.Content.CC_REF)) {
				player[tmpPlayer].getCard(newDeck.pop());
				player[tmpPlayer].getCard(newDeck.pop());
			}
			if(j.have(Card.Content.CC_NONET)) {
				get = false;
			}
			if(j.have(Card.Content.CC_NIGHTPLAY)) {
				use = false;
			}
			if(get == true) {
				player[tmpPlayer].getCard(newDeck.pop());
				player[tmpPlayer].getCard(newDeck.pop());
			}
			else get = true;
			
			state = 2;
			if(use == true){
				while(true) {
					 player[tmpPlayer].useCard();
					 exeAction();
					 if(player[tmpPlayer].endTmp == true)break;
				}
			}
			else {
				use = true;
				player[tmpPlayer].endTmp = true;
			}
			
			state = 3;
			player[tmpPlayer].endUse();
			
			state = 4;
			do {
				tmpPlayer = (tmpPlayer+1)%2;
			}while(player[tmpPlayer]==null);
		}
	}
	static boolean notEnd() {
		int playerLeft = 0;
		for(int i = 0; i < 8; i++) {
			if(player[i]!=null)playerLeft++;
		}
		if(playerLeft>1)return true;
		else return false;
	}
 	static void exeAction() {
		int n, idx;
		if(action == null)return;
		
		pro = tmpPlayer;
		if(obj != -1)
			player[obj].beObj();
		if(con != -1)
			player[con].beObj();
		if(chk != -1)
			player[con].beObj();
		
		switch(action.getIdx()) {
		case CC_PREVENT:
			if(obj==-1)break;
			if(!player[obj].receiveKillFrom(kill)) {
				if(player[tmpPlayer].failKill())
					exeAction();
			}
			else {
				player[tmpPlayer].succeedKill(obj);
			}
			kill = Commander.Effect.CE_NOEFFECT;
			player[tmpPlayer].moreKill();
			if(con!=-1) {
				if(!player[con].receiveKillFrom(kill)) {
					if(player[tmpPlayer].failKill())
						exeAction();
				}
				else {
					player[tmpPlayer].succeedKill(con);
				}
			}
			kill = Commander.Effect.CE_NOEFFECT;
			player[tmpPlayer].moreKill();
			if(chk!=-1) {
				if(!player[chk].receiveKillFrom(kill)) {
					if(player[tmpPlayer].failKill())
						exeAction();
				}
				else {
					player[tmpPlayer].succeedKill(chk);
				}
			}
			break;
		case CC_NONET:
			if(obj==-1)break;
			player[obj].receiveJudge(action);
			break;
		case CC_WEAKSHOW:
			if(obj==-1)break;
			if(askProblem())break;
			player[obj].showCard();
			if(player[tmpPlayer].weakThrow()) {
				player[obj].lessBlood();
			}
			break;
		case CC_NIGHTPLAY:
			if(obj==-1)break;
			player[obj].receiveJudge(action);
			break;
		case CC_WORSHIP:
			if(obj==-1)break;
			if(askProblem())break;
			while(true){
				if(player[obj].needKill()==false)break;
				if(player[tmpPlayer].needKill()==false)break;
			}
			break;
		case CC_TOEAT:
			for(int i = 0; i < num; i++){
				if(player[i]==null)continue;
				if(i==tmpPlayer)continue;
				player[i].beObj();
				if(askProblem())continue;
				player[i].needKill();
				player[i].endObj();
			}
			break;
		case CC_TOREVIEW:
			for(int i = 0; i < num; i++){
				if(player[i]==null)continue;
				if(i==tmpPlayer)continue;
				player[i].beObj();
				if(askProblem())continue;
				player[i].receiveKillFrom(review);
				player[i].endObj();
			}
			break;
		case CC_COPY:
			if(obj==-1)break;
			if(askProblem())break;
			n = player[obj].cardNum();
			idx = player[tmpPlayer].copyCode(n);
			player[tmpPlayer].handCard.push(player[obj].handCard.pop(idx));
			break;
		case CC_CALLROLL:
			player[tmpPlayer].receiveJudge(action);
			break;
		case CC_STEAM:
			if(obj!=-1) {
				player[obj].beObj();
				if(!askProblem()) {
					player[obj].changeSteam();
					player[obj].endObj();
				}
			}
			if(con!=-1) {
				player[con].beObj();
				if(!askProblem()) {
					player[con].changeSteam();
					player[con].endObj();
				}
			}
			break;
		case CC_DOWNLOAD:
			if(askProblem())break;
			player[tmpPlayer].handCard.push(Table.newDeck.pop());
			player[tmpPlayer].handCard.push(Table.newDeck.pop());
			break;
		case CC_HACK:
			if(obj==-1)break;
			if(askProblem())break;
			n = player[obj].cardNum();
			idx = player[tmpPlayer].copyCode(n);
			player[obj].handCard.pop(idx);
			break;
		case CC_EXAMLEAK:
			n = 0;
			for(int i = 0; i < num; i++)
				if(player[i] != null)n++;
			Deck d = new Deck();
			for(int i = 0; i < n; i++)
				d.push(newDeck.pop());
			for(int i = 0; i < num; i++) {
				if(player[i] != null) {
					player[i].beObj();
					if(askProblem())continue;
					player[i].getCard(d.pop(player[i].examLeak(d)));
					player[i].endObj();
				}
			}
			break;
		case CC_REEXAM:
			for(int i = 0; i < num; i++) {
				if(player[i] != null) {
					player[i].beObj();
					if(askProblem())continue;
					player[i].moreBlood();
					player[i].endObj();
				}
			}
			break;
		case CC_REF:
			player[obj].receiveJudge(action);
			break;
		case CC_FUCK:
			if(askProblem())break;

			if(player[obj].beFucked()) {
				pro = obj;
				player[con].receiveKillFrom(kill);
			}
			else {
				player[tmpPlayer].getCard(player[obj].equipCard.getCard(0));
				player[obj].equipCard.cont.set(0, null);
			}
		default:
			break;
		}
		askSave();

		if(obj != -1)
			player[obj].endObj();
		if(con != -1)
			player[con].endObj();
		
		kill = Commander.Effect.CE_NOEFFECT;
		review = Commander.Effect.CE_NOEFFECT;
		real = new Deck();
		action = null;
		obj = -1;
		con = -1;
		chk = -1;
	}
	static Card exeJudge() {
		Card rt, tmp;
		System.out.println("判定结果为：" + (rt = newDeck.pop()));
		for(int i = 0; i < num; i++) {
			if(player[(tmpPlayer + i)%8]!=null) {
				if((tmp = player[i].changeJudge())!=null) {
					rt = tmp;
				}
			}
		}
		return rt;
	}
 	static int calDist(int pro, int obj) {
		int dist = 0;
		int left = pro, right = pro;
		while(left!=obj && right!=obj) {
			while(player[left = (left+num-1)%num]==null);
			while(player[right = (right+1)%num]==null);
			dist++;
		}
		if(player[obj].equipCard.cont.get(3)!=null)dist++;
		if(player[pro].equipCard.cont.get(2)!=null)dist--;
		return dist;
	}
 	static int killDist(Card c) {
 		if(c==null)return 1;
		switch(c.getIdx()){
		case CC_SCRIPT:
			return 1;
		case CC_XILINX:
			return 2;
		case CC_SPINPEN:
			return 3;
		case CC_PTA:
			return 3;
		case CC_CHICKEN:
			return 4;
		case CC_CLOTHES:
			return 2;
		case CC_LINUX:
			return 2;
		case CC_GUARD:
			return 5;
		default:
			return 1;
		}
 	}
	static void askSave() {
		if(dying==-1)return;
		else {
			int i;
			for(i = 0; i < num; i++) {
				if(player[(tmpPlayer + i)%num].askSave()) {
					   if(player[dying].moreBlood() > 0)
						   break;
				}
			}
			if(i==num) {
				player[dying].dieAnyway();
			}
			dying = -1;
		}
	} 
	static boolean askProblem() {
		int fuck;
		for(fuck= 0; fuck < num; fuck++){
			if(player[(tmpPlayer + fuck)%num] != null)
				if(player[(tmpPlayer + fuck)%num].askProblem())break;
		}
		if(fuck<num)return !askProblem();
		else return false;
	}
	static void dieOne(int seat) {
		if(player[seat] != null)player[seat] = null;
	}
}
