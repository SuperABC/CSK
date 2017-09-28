package Frame;

import java.util.Scanner;
import Killer.GTX;
import Killer.ZRS;

public class Table {
	public static Commander[] player = new Commander[8];
	public static int num = 2;
	public static Deck newDeck = new Deck();
	public static Deck exDeck = new Deck();
	
	public static Card action = null;
	public static int obj = -1;
	public static int con = -1;
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
			Deck j = player[tmpPlayer].exeJudge();
			if(j.have(Card.Content.CC_CALLROLL)) {
				player[tmpPlayer].lessBlood(3);
			}
			askSave();
			if(!j.have(Card.Content.CC_NONET)) {
				player[tmpPlayer].getCard(newDeck.pop());
				player[tmpPlayer].getCard(newDeck.pop());
			}
			if(j.have(Card.Content.CC_REF)) {
				player[tmpPlayer].getCard(newDeck.pop());
				player[tmpPlayer].getCard(newDeck.pop());
			}
			if(!j.have(Card.Content.CC_NIGHTPLAY)){
				while(true) {
					 player[tmpPlayer].useCard();
					 exeAction();
					 if(player[tmpPlayer].endUse())break;
				}
			}
			else {
				player[tmpPlayer].endTmp = true;
				player[tmpPlayer].endUse();
			}
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
		int n, idx, fuck;
		if(action == null)return;
		switch(action.getIdx()) {
		case CC_PREVENT:
			player[obj].receiveKillFrom(player[tmpPlayer].masterName);
			break;
		case CC_NONET:
			player[obj].receiveJudge(action);
			break;
		case CC_WEAKSHOW:
			for(fuck= 0; fuck < num; fuck++){
				if(player[fuck] != null)
					if(player[fuck].askProblem())break;
			}
			if(fuck<num)break;
			player[obj].showCard();
			if(player[tmpPlayer].weakThrow()) {
				player[obj].lessBlood();
			}
			break;
		case CC_NIGHTPLAY:
			player[obj].receiveJudge(action);
			break;
		case CC_WORSHIP:
			for(fuck= 0; fuck < num; fuck++){
				if(player[fuck] != null)
					if(player[fuck].askProblem())break;
			}
			if(fuck<num)break;
			while(true){
				if(player[obj].needKill()==false)break;
				if(player[tmpPlayer].needKill()==false)break;
			}
			break;
		case CC_TOEAT:
			for(int i = 0; i < num; i++){
				if(player[i]==null)continue;
				if(i==tmpPlayer)continue;
				for(fuck= 0; fuck < num; fuck++){
					if(player[fuck] != null)
						if(player[fuck].askProblem())break;
				}
				if(fuck<num)continue;
				player[i].needKill();
			}
		case CC_TOREVIEW:
			for(int i = 0; i < num; i++){
				if(player[i]==null)continue;
				if(i==tmpPlayer)continue;
				for(fuck= 0; fuck < num; fuck++){
					if(player[fuck] != null)
						if(player[fuck].askProblem())break;
				}
				if(fuck<num)continue;
				player[i].receiveKill();
			}
			break;
		case CC_COPY:
			for(fuck= 0; fuck < num; fuck++){
				if(player[fuck] != null)
					if(player[fuck].askProblem())break;
			}
			if(fuck<num)break;
			n = player[obj].cardNum();
			idx = player[tmpPlayer].copyCode(n);
			player[tmpPlayer].handCard.push(player[obj].handCard.pop(idx));
			break;
		case CC_CALLROLL:
			player[tmpPlayer].receiveJudge(action);
			break;
		case CC_STEAM:
			if(obj!=-1) {
				for(fuck= 0; fuck < num; fuck++){
					if(player[fuck] != null)
						if(player[fuck].askProblem())break;
				}
				if(fuck==num)
					player[obj].changeSteam();
			}
			if(con!=-1) {
				for(fuck= 0; fuck < num; fuck++){
					if(player[fuck] != null)
						if(player[fuck].askProblem())break;
				}
				if(fuck==num)
					player[obj].changeSteam();
			}
			break;
		case CC_DOWNLOAD:
			for(fuck= 0; fuck < num; fuck++){
				if(player[fuck] != null)
					if(player[fuck].askProblem())break;
			}
			if(fuck<num)break;
			player[tmpPlayer].handCard.push(Table.newDeck.pop());
			player[tmpPlayer].handCard.push(Table.newDeck.pop());
			break;
		case CC_HACK:
			for(fuck= 0; fuck < num; fuck++){
				if(player[fuck] != null)
					if(player[fuck].askProblem())break;
			}
			if(fuck<num)break;
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
					for(fuck= 0; fuck < num; fuck++) {
						if(player[fuck] != null)
							if(player[fuck].askProblem())break;
					}
					if(fuck<num)continue;
					player[i].getCard(d.pop(player[i].examLeak(d)));
				}
			}
			break;
		case CC_REEXAM:
			for(int i = 0; i < num; i++) {
				if(player[i] != null) {
					for(fuck= 0; fuck < num; fuck++){
						if(player[fuck] != null)
							if(player[fuck].askProblem())break;
					}
					if(fuck<num)continue;
					player[i].moreBlood();
				}
			}
			break;
		case CC_REF:
			player[obj].receiveJudge(action);
			break;
		default:
			break;
		}
		askSave();
		action = null;
		obj = -1;
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
	public void dieOne(int seat) {
		if(player[seat] != null)player[seat] = null;
	}
}
