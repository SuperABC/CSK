package Killer;

import java.util.Scanner;

import Frame.Card;
import Frame.Commander;
import Frame.Table;

public class GTX extends Commander {
	private boolean oneCard = false;
	
	public GTX(int n, int seat) {
		super(n, seat);
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
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("��ѧ�ˣ�");
		handCard.pop(c);
		
		Table.kill = Effect.CE_DISPOSEONE;
		System.out.println("���Ǹ����������ѧ�ˣ�");
		
		killed = true;
 	}
	protected void toreview(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("����ϰ�ˣ�");
		handCard.pop(c);
		
		Table.review = Effect.CE_DISPOSEONE;
		System.out.println("���Ǹ����������ѧ�ˣ�");
 	}
 	public void beObj() {
 		if((Table.action.getColor()=="����"||Table.action.getColor()=="�ݻ�")&&Table.con==-1) {
	 		switch(Table.action.getIdx()) {
	 		case CC_WORSHIP:
	 		case CC_COPY:
	 		case CC_STEAM:
	 		case CC_HACK:
	 		case CC_FUCK:
	 			oneCard = true;
	 			break;
	 		case CC_TOEAT:
	 			if(Table.num==2)oneCard = true;
	 			break;
 			default:
 				break;
	 		}
 		}
 	}
 	public void endObj() {
 		if(oneCard) {
 			getCard(Table.newDeck.pop());
 	 		System.out.println("������磬���ǲ�����⡣");
 		}
 	}
 	public void dieAnyway() {
		 System.out.println(masterName.toString() + " died.");
		 System.out.println("������Ⱥ͵��ѧϰ��Ҫ�����ˣ�");
	}
}
