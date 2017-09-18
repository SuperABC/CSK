public class Card {
	enum Type {
		CT_ORDINARY,
		CT_FUNC,
		CT_EQUIPMENT
	}
	enum Content {
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
		CC_NOPROBLEM,//��и�ɻ�(��и�ɻ�)
		CC_FUCK,//����Լ��(�赶ɱ��)
		CC_REEXAM,//�ؿ�(��԰����)
	}
	
	private Type type;
	private int number;
	private Content cont;
	
	public Card(int n, int c) {
		number = n;
		switch(c) {
		case 0:
			cont = Content.CC_PREVENT;
			break;
		case 1:
			cont = Content.CC_DENY;
			break;
		case 2:
			cont = Content.CC_STUDY;
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
}
