package Frame;

import java.util.ArrayList;
import java.util.Collections;

public class Deck {
	static final int TOTAL_CARD_NUM = 104;
	
	public ArrayList<Card> cont = new ArrayList<Card>();
	public int tmpNum = 0;
	
	public void shuffleAll() {
		push(new Card(10,0,0));
		push(new Card(10,0,0));
		push(new Card(11,0,0));
		push(new Card(7,0,1));
		push(new Card(8,0,1));
		push(new Card(9,0,1));
		push(new Card(10,0,1));
		push(new Card(13,0,1));
		push(new Card(7,0,2));
		push(new Card(8,0,2));
		push(new Card(8,0,2));
		push(new Card(9,0,2));
		push(new Card(9,0,2));
		push(new Card(10,0,2));
		push(new Card(10,0,2));
		push(new Card(2,0,3));
		push(new Card(3,0,3));
		push(new Card(4,0,3));
		push(new Card(5,0,3));
		push(new Card(6,0,3));
		push(new Card(7,0,3));
		push(new Card(8,0,3));
		push(new Card(8,0,3));
		push(new Card(9,0,3));
		push(new Card(9,0,3));
		push(new Card(10,0,3));
		push(new Card(10,0,3));
		push(new Card(11,0,3));
		push(new Card(11,0,3));

		push(new Card(2,1,0));
		push(new Card(2,1,0));
		push(new Card(13,1,0));
		push(new Card(2,1,1));
		push(new Card(2,1,1));
		push(new Card(3,1,1));
		push(new Card(4,1,1));
		push(new Card(5,1,1));
		push(new Card(6,1,1));
		push(new Card(7,1,1));
		push(new Card(8,1,1));
		push(new Card(9,1,1));
		push(new Card(10,1,1));
		push(new Card(11,1,1));
		push(new Card(11,1,1));

		push(new Card(3,2,0));
		push(new Card(4,2,0));
		push(new Card(6,2,0));
		push(new Card(7,2,0));
		push(new Card(8,2,0));
		push(new Card(9,2,0));
		push(new Card(12,2,0));
		push(new Card(12,2,1));

		push(new Card(9,3,1));

		push(new Card(10,4,2));
		 
		push(new Card(12,5,1));
		 
		push(new Card(6,6,0));
		push(new Card(6,6,2));
		push(new Card(6,6,3));
		 
		push(new Card(1,7,1));
		push(new Card(1,7,2));
		push(new Card(1,7,3));

		push(new Card(7,8,2));
		push(new Card(13,8,2));
		push(new Card(7,8,3));

		push(new Card(1,9,0));

		push(new Card(3,10,1));
		push(new Card(4,10,1));
		push(new Card(3,10,2));
		push(new Card(4,10,2));
		push(new Card(11,10,2));

		push(new Card(1,11,2));
		push(new Card(12,11,0));

		push(new Card(11,12,2));

		push(new Card(7,13,0));
		push(new Card(8,13,0));
		push(new Card(9,13,0));
		push(new Card(11,13,0));

		push(new Card(12,14,0));
		push(new Card(3,14,2));
		push(new Card(4,14,2));
		push(new Card(12,14,2));
		push(new Card(3,14,3));
		push(new Card(4,14,3));
		 
		push(new Card(3,15,0));
		push(new Card(4,15,0));

		push(new Card(12,16,1));
		push(new Card(11,16,2));
		push(new Card(12,16,3));
		push(new Card(13,16,3));

		push(new Card(1,17,0));

		push(new Card(5,18,1));
		push(new Card(5,18,3));

		push(new Card(12,19,3));
		push(new Card(13,19,3));

		push(new Card(1,20,1));
		push(new Card(1,20,3));

		push(new Card(6,21,2));

		push(new Card(12,22,2));

		push(new Card(5,23,1));

		push(new Card(12,24,1));

		push(new Card(2,25,2));

		push(new Card(2,26,2));

		push(new Card(5,27,0));

		push(new Card(2,28,2));
		push(new Card(2,28,3));

		push(new Card(2,29,3));

		push(new Card(1,30,3));

		push(new Card(7,31,0));

		push(new Card(8,32,1));

		push(new Card(5,33,0));

		push(new Card(13,34,2));

		push(new Card(13,35,0));

		push(new Card(5,36,2));
		
		
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
	public boolean have(Card.Content c) {
		for(int i = 0; i < tmpNum; i++) {
			if(cont.get(i).getIdx()==c)return true;
		}
		return false;
	}
}
