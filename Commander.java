public class Commander {
	enum Name {
		CN_GTX,
		CN_ZRS
	}
	enum Group {
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
	private int seatNum;
	
	public Commander(int n, int seat) {
		switch(n) {
		case 0:
			masterName = Name.CN_GTX;
			masterGroup = Group.CG_COMPUTER;
			fullBlood = 4;
			tmpBlood = 4;
			handCard = new Deck();
			equipCard = new Deck();
			seatNum = seat;
			break;
		case 1:
			masterName = Name.CN_ZRS;
			masterGroup = Group.CG_COMPUTER;
			fullBlood = 4;
			tmpBlood = 4;
			handCard = new Deck();
			equipCard = new Deck();
			seatNum = seat;
			break;
		}
	}
	
	public void getCard(Card c) {
		handCard.push(c);
	}
	public void useCard() {
		System.out.println(masterName.toString() + " is using card.");
	}
	public boolean endUse() {
		while(handCard.tmpNum>tmpBlood){
			handCard.pop();
		}
		System.out.println(masterName.toString() + " end.");
		return true;
	}
	public void receiveKill() {
		
	}
}
