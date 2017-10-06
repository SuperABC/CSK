package Frame;

public class Card {
	public enum Type {
		CT_ORDINARY,
		CT_FUNC,
		CT_EQUIPMENT
	}
	public enum Content {
		CC_PREVENT,//��ѧ��(ɱ)0
		CC_DENY,//ûѧ(��)1
		CC_STUDY,//ѧϰ(��)2
		CC_STAYUP,//ˢҹ(��)3
		CC_NONET,//����(�������)4
		CC_WEAKSHOW,//����(��)5
		CC_NIGHTPLAY,//��Ϸͨ��(�ֲ�˼��)6
		CC_WORSHIP,//��Ĥ(����)7
		CC_TOEAT,//Լ��(��������)8
		CC_TOREVIEW,//Լ��ϰ(����뷢)9
		CC_COPY,//������(˳��ǣ��)10
		CC_CALLROLL,//����(����)11
		CC_STEAM,//Steam����(��������)12
		CC_DOWNLOAD,//��������(��������)13
		CC_HACK,//�ڿ�����(���Ӳ���)14
		CC_EXAMLEAK,//����©��(��ȷ��)15
		CC_NOPROBLEM,//��(��и�ɻ�)16
		CC_REEXAM,//�ؿ�(��԰����)17
		CC_REF,//С��(�¼ӽ���)18
		CC_FUCK,//����Լ��(�赶ɱ��)19
		CC_SCRIPT,//�����ű�(�������1)20
		CC_XILINX,//����˹(���G��2)21
		CC_SPINPEN,//תת��(�ɰ�ì3)22
		CC_PTA,//�����˺�(��ʯ��3)23
		CC_CHICKEN,//����ɱ(���컭�4)24
		CC_CLOTHES,//Ůװ(���۽�2)25
		CC_LINUX,//��ϵͳ(������2)26
		CC_GUARD,//�����Ʒ�(���빭5)27
		CC_KEYBOARD,//�������(������)28
		CC_GTX,//GTX�Կ�(������)29
		CC_DBELEPHANT,//����(����ʨ��)30
		CC_GLASSES,//�ڿ��۾�(����)31
		CC_FLYING,//����ģʽ(���G��)32
		CC_MOTOR,//С��(-1��)33
		CC_BUS,//У��(-1��)34
		CC_LAKE,//�����(+1��)35
		CC_MOUNTAIN,//�Ϻ�ɽ(+1��)36
	}
	public enum Color {
		CC_HEART,
		CC_SQUARE,
		CC_SPADE,
		CC_CLUB,
		CC_NONE
	}
	
	private Type type;
	private int number;
	private Content cont;
	private Color color;
	
	public Card(int n, int cont, int color) {
		number = n-1;
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
		case 6:
			this.cont = Content.CC_NIGHTPLAY;
			break;
		case 7:
			this.cont = Content.CC_WORSHIP;
			break;
		case 8:
			this.cont = Content.CC_TOEAT;
			break;
		case 9:
			this.cont = Content.CC_TOREVIEW;
			break;
		case 10:
			this.cont = Content.CC_COPY;
			break;
		case 11:
			this.cont = Content.CC_CALLROLL;
			break;
		case 12:
			this.cont = Content.CC_STEAM;
			break;
		case 13:
			this.cont = Content.CC_DOWNLOAD;
			break;
		case 14:
			this.cont = Content.CC_HACK;
			break;
		case 15:
			this.cont = Content.CC_EXAMLEAK;
			break;
		case 16:
			this.cont = Content.CC_NOPROBLEM;
			break;
		case 17:
			this.cont = Content.CC_REEXAM;
			break;
		case 18:
			this.cont = Content.CC_REF;
			break;
		case 19:
			this.cont = Content.CC_FUCK;
			break;
		case 20:
			this.cont = Content.CC_SCRIPT;
			break;
		case 21:
			this.cont = Content.CC_XILINX;
			break;
		case 22:
			this.cont = Content.CC_SPINPEN;
			break;
		case 23:
			this.cont = Content.CC_PTA;
			break;
		case 24:
			this.cont = Content.CC_CHICKEN;
			break;
		case 25:
			this.cont = Content.CC_CLOTHES;
			break;
		case 26:
			this.cont = Content.CC_LINUX;
			break;
		case 27:
			this.cont = Content.CC_GUARD;
			break;
		case 28:
			this.cont = Content.CC_KEYBOARD;
			break;
		case 29:
			this.cont = Content.CC_GTX;
			break;
		case 30:
			this.cont = Content.CC_DBELEPHANT;
			break;
		case 31:
			this.cont = Content.CC_GLASSES;
			break;
		case 32:
			this.cont = Content.CC_FLYING;
			break;
		case 33:
			this.cont = Content.CC_MOTOR;
			break;
		case 34:
			this.cont = Content.CC_BUS;
			break;
		case 35:
			this.cont = Content.CC_LAKE;
			break;
		case 36:
			this.cont = Content.CC_MOUNTAIN;
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
			return "��";
		case CC_REEXAM:
			return "�ؿ�";
		case CC_REF:
			return "С��";
		case CC_FUCK:
			return "����Լ��";
		case CC_SCRIPT:
			return "�����ű�";
		case CC_XILINX:
			return "XILINX";
		case CC_SPINPEN:
			return "תת��";
		case CC_PTA:
			return "�����˺�";
		case CC_CHICKEN:
			return "����ɱ";
		case CC_CLOTHES:
			return "Ůװ";
		case CC_LINUX:
			return "��ϵͳ";
		case CC_GUARD:
			return "�����Ʒ�";
		case CC_KEYBOARD:
			return "�������";
		case CC_GTX:
			return "GTX�Կ�";
		case CC_DBELEPHANT:
			return "����";
		case CC_GLASSES:
			return "�ڿ��۾�";
		case CC_FLYING:
			return "����ģʽ";
		case CC_MOTOR:
			return "С��";
		case CC_BUS:
			return "У��";
		case CC_LAKE:
			return "�����";
		case CC_MOUNTAIN:
			return "�Ϻ�ɽ";
		default:
			return null;
		}
	}
	public Content getIdx() {
		return cont;
	}
	public String toString() {
		return getColor() + number + getCont();
	}
}