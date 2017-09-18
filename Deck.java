import java.util.ArrayList;
import java.util.Collections;

public class Deck {
	static final int TOTAL_CARD_NUM = 104;
	
	private ArrayList<Card> cont = new ArrayList<Card>();
	private int tmpNum;
	
	public void shuffleAll() {
		for(int i = 0; i < TOTAL_CARD_NUM; i++) {
			cont.add(new Card((int)(13*Math.random()), (int)(3*Math.random())));
		}
		Collections.shuffle(cont);
	}
	
	public Card getTop() {
		return cont.get(0);
	}
	public Card getBottom() {
		return cont.get(tmpNum-1);
	}
	public Card getCard(int i) {
		if(i < 0 || i >= tmpNum)return null;
		else return cont.get(i);
	}
	public Card pop() {
		Card rt = cont.remove(--tmpNum);
		if(tmpNum==0)shuffleAll();
		return rt;
	}
	public void push(Card c) {
		tmpNum++;
		cont.add(c);
	}
}
