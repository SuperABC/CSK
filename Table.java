import java.util.Scanner;

public class Table {
	public static Commander[] player = new Commander[8];
	public static int num = 2;
	public static Deck newDeck = new Deck();
	public static Deck exDeck = new Deck();
	
	public static Card action = null;
	public static int obj = -1;
	public static int dying = -1;
	
	public static int tmpPlayer = 0;
	
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		System.out.println("Welcome to CS Killer, now choose a commander.");
		System.out.println("0.GTX    1.ZRS");
		int role = s.nextInt();
		switch(role) {
		case 0:
			player[0] = new Commander(0, 0);
			player[1] = new Commander(1, 1);
			break;
		case 1:
			player[0] = new Commander(0, 1);
			player[1] = new Commander(1, 0);
			break;
		default:
			System.out.println("Wrong input!");
			break;
		}
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
			if(!j.have(4)){
				player[tmpPlayer].getCard(newDeck.pop());
				player[tmpPlayer].getCard(newDeck.pop());
			}
			while(true) {
				 player[tmpPlayer].useCard();
				 exeAction();
				 if(player[tmpPlayer].endUse())break;
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
		if(action == null)return;
		switch(action.getIdx()) {
		case 0:
			player[obj].receiveKill();
			break;
		case 4:
			player[obj].receiveJudge(action);
			break;
		case 5:
			player[obj].showCard();
			if(player[tmpPlayer].weakThrow()) {
				player[obj].lessBlood();
			}
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
