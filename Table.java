import java.util.Scanner;

public class Table {
	private static Commander[] player = new Commander[8];
	private static int num = 2;
	private static Deck newDeck;
	private static Deck exDeck;
	
	static int tmpPlayer = 0;
	
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		System.out.println("Welcome to CS Killer, now choose a commander.");
		System.out.println("1.GTX    2.ZRS");
		int role = s.nextInt();
		switch(role) {
		case 1:
			player[0] = new Commander(0, 0);
			player[1] = new Commander(1, 1);
			break;
		case 2:
			player[0] = new Commander(1, 0);
			player[1] = new Commander(0, 1);
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
			player[tmpPlayer].getCard(newDeck.pop());
			player[tmpPlayer].getCard(newDeck.pop());
			while(true) {
				
			}
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
}
