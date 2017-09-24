import java.util.ArrayList;
import java.util.Collections;

public class Deck {
	static final int TOTAL_CARD_NUM = 104;
	
	public ArrayList<Card> cont = new ArrayList<Card>();
	public int tmpNum = 0;
	
	public void shuffleAll() {
		 for(int i = 0; i < TOTAL_CARD_NUM; i++) {
			push(new Card((int)(13*Math.random()), (int)(6*Math.random()), (int)(4*Math.random())));
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
	public Card pop(int idx) {
		if(idx < 0 || idx >= tmpNum)return null;
		Card rt = cont.remove(idx);
		tmpNum--;
		return rt;
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
	public boolean have(int c) {
		for(int i = 0; i < tmpNum; i++) {
			if(cont.get(i).getIdx()==c)return true;
		}
		return false;
	}
}
