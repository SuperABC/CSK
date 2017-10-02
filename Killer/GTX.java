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
			System.out.println("你以为你是高神呀？天天别学了别学了的。");
			return;
		}
		
		Table.action = handCard.cont.get(c);
		o = s.nextInt();
		Table.obj = o;
		System.out.println(masterName.toString() + " to " + Table.player[o].masterName.toString() + ":");
		System.out.println("别学了！");
		handCard.pop(c);
		
		Table.kill = Effect.CE_DISPOSEONE;
		System.out.println("我是高神，求求你别学了！");
		
		killed = true;
 	}
	protected void toreview(int c) {
		Scanner s = new Scanner(System.in);
		int o;

		Table.action = handCard.cont.get(c);
		System.out.println(masterName.toString() + ":");
		System.out.println("来自习了！");
		handCard.pop(c);
		
		Table.review = Effect.CE_DISPOSEONE;
		System.out.println("我是高神，求求你别学了！");
 	}
 	public void beObj() {
 		if((Table.action.getColor()=="黑桃"||Table.action.getColor()=="草花")&&Table.con==-1) {
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
 	 		System.out.println("神的世界，你们不会理解。");
 		}
 	}
 	public void dieAnyway() {
		 System.out.println(masterName.toString() + " died.");
		 System.out.println("你们这群偷着学习不要脸的人！");
	}
}
