public class Card {
	public enum Type {
		CT_ORDINARY,
		CT_FUNC,
		CT_EQUIPMENT
	}
	public enum Content {
		CC_PREVENT,//��ѧ��(ɱ)
		CC_DENY,//ûѧ(��)
		CC_STUDY,//ѧϰ(��)
		CC_STAYUP,//ˢҹ(��)
		CC_NONET,//����(�������)
		CC_WEAKSHOW,//����(��)
		CC_NIGHTPLAY,//��Ϸͨ��(�ֲ�˼��)
		CC_WORSHIP,//��Ĥ(����)
		CC_TOEAT,//Լ��(��������)
		CC_TOREVIEW,//Լ��ϰ(����뷢)
		CC_COPY,//������(˳��ǣ��)
		CC_CALLROLL,//����(����)
		CC_STEAM,//Steam����(��������)
		CC_DOWNLOAD,//��������(��������)
		CC_HACK,//�ڿ�����(���Ӳ���)
		CC_EXAMLEAK,//����©��(��ȷ��)
		CC_NOPROBLEM,//��(��и�ɻ�)
		CC_FUCK,//����Լ��(�赶ɱ��)
		CC_REEXAM,//�ؿ�(��԰����)
		CC_REF,//С��(�¼ӽ���)
	}
	public enum Color {
		CC_HEART,
		CC_SQUARE,
		CC_SPADE,
		CC_CLUB
	}
	
	private Type type;
	private int number;
	private Content cont;
	private Color color;
	
	public Card(int n, int cont, int color) {
		number = n;
		switch(color){
		case 0:
			this.color = Color.CC_HEART;
			break;
		case 1:
			this.color = Color.CC_SQUARE;
			break;
		case 2:
			this.color = Color.CC_SPADE;
			break;
		case 3:
			this.color = Color.CC_CLUB;
			break;
		}
		switch(cont) {
		case 0:
			this.cont = Content.CC_PREVENT;
			break;
		case 1:
			this.cont = Content.CC_DENY;
			break;
		case 2:
			this.cont = Content.CC_STUDY;
			break;
		case 3:
			this.cont = Content.CC_STAYUP;
			break;
		case 4:
			this.cont = Content.CC_NONET;
			break;
		case 5:
			this.cont = Content.CC_WEAKSHOW;
			break;
		}
	}
	
	public String getType() {
		switch(type) {
		case CT_ORDINARY:
			return "������";
		case CT_FUNC:
			return "������";
		case CT_EQUIPMENT:
			return "������";
		default:
			return null;
		}
	}
	public int getNum() {
		return number;
	}
	public String getColor() {
		switch(color){
		case CC_HEART:
			return "����";
		case CC_SQUARE:
			return "��Ƭ";
		case CC_SPADE:
			return "����";
		case CC_CLUB:
			return "÷��";
		}
		return null;
	}
	public String getCont() {
		switch(cont) {
		case CC_PREVENT:
			return "��ѧ��";
		case CC_DENY:
			return "ûѧ";
		case CC_STUDY:
			return "ѧϰ";
		case CC_STAYUP:
			return "ˢҹ";
		case CC_NONET:
			return "����";
		case CC_WEAKSHOW:
			return "����";
		case CC_NIGHTPLAY:
			return "��Ϸͨ��";
		case CC_WORSHIP:
			return "��Ĥ";
		case CC_TOEAT:
			return "Լ��";
		case CC_TOREVIEW:
			return "Լ��ϰ";
		case CC_COPY:
			return "������";
		case CC_CALLROLL:
			return "����";
		case CC_STEAM:
			return "Steam����";
		case CC_DOWNLOAD:
			return "��������";
		case CC_EXAMLEAK:
			return "����©��";
		case CC_HACK:
			return "�ڿ�����";
		case CC_NOPROBLEM:
			return "��и�ɻ�";
		case CC_FUCK:
			return "����Լ��";
		case CC_REEXAM:
			return "�ؿ�";
		default:
			return null;
		}
	}
	public int getIdx(){
		return cont.ordinal();
	}
}
