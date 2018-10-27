#include "killer.h"
#include "cs.h"
#include "se.h"
#include "ckc.h"
#include "ot.h"

const char *killerName[] = {
	"ѧ��",

	"������",
	"����",
	"��չ�",
	"��ռ��",
	"����N",
	"����",
	"������",
	"������",
	"��ΰ�",
	"����",
	"����˼��",
	"������",
	"���",
	"���",
	"ë˳��",
	"ë��",
	"���Ć�",
	"�麣��",
	"�ζ�",
	"Ҷ���",
	"�·���",
	"κҫ��",
	"��ΰ��",
	"��پ��",
	"����",
	"�ų���",
	"������",
	"������",
	"¡����",
	"���ݵ�",
	"�⳯��",
	"����",
	"������",
	"��������",
	"��ң",
	"ң��",
	"֣��",
	"����",
	"������",
	"�պ�",
	"��Zɭ"
};

const char *killerDetail[] = {
	"��ͨѧ����û�м��ܡ�",

	"������(�߹�������������)��ӵ�м��ܸ���þ���\n\n\
�������������������ɫ����Ļغ���Ҫʹ��һ��ûѧʱ������������һ�����ơ�\n\
�þ������㱻��ɫ������ָ��ΪĿ��ʱ��������ɺ��������һ���ơ�\n\
���ӣ��೤����һ���ƿƽ�ɫ�����ڻغϽ���֮��������X���ƣ�XΪ��غ���ʹ������ɫ������ٹҿ�״̬�Ľ�ɫ��������",
	
	"����(���ƣ��߷���)��ӵ�м��ܿ��С���Ŀ��\n\n\
���У��غϿ�ʼʱ������Խ�һ����ɫ��ȫ�����������佫���ϣ����غϽ�����ʱ��ý�ɫ�����Щ�ơ�\n\
��Ŀ�������������޷���Ϊ�����������㵱ǰ����Ľ�ɫ����ѧ�ˡ��͡���������Ŀ�ꡣ",

	"��չ�(Ⱥ���˺������ö�����)��ӵ�м���ѧ�ԡ��񾺡�\n\n\
ѧ�ԣ����ƽ׶���һ�Σ������ָ��һ���乥����Χ�ڰ������Լ���������ɫ���ý�ɫ�����ʹ��һ�ű�ѧ�ˣ�������������һ���ơ�\n\
�񾺣��޶�����������ƽ׶Σ����㲻Ϊ�����������ѡ������������ɫ����Щ��ɫ����Ծ����������һ����ɫʹ��һ�ű�ѧ�ˣ���������ʧһ�����㡣",
	
	"��ռ��(�������ƣ�����ظ�����)��ӵ�м��ܿ�ѧ��͵ѧ��������\n\n\
��ѧ��ÿ�غ���һ�Σ�����Խ�һ�ź����Ƶ���ˢҹʹ�á�\n\
͵ѧ������غϽ���ʱ�����㲻Ϊ����������Զ�������һ�����ƣ�����һ�����㡣\n\
�����������������ƽ׶Σ����������ˣ����������X���ƣ�XΪ������ʧ������ֵ����",

	"����N(�������ˣ�Ⱥ���˺�)��ӵ�м��ܳ��顢���㡢��顣\n\n\
��ʣ��������������ʱ�Լ��������ж�ʱ����Ϊ�ж�ʧЧ��\n\
���飺ʼ����Ϊ�ж���\n\
���㣺�޶��������ƽ׶Σ������չʾһ�ź����ƣ����������н�ɫѡ��һ�\n\
	��������װ����\n\
	ʧȥһ������\n\
��飺�೤����������ٹҿƵ�ʱ�򣬿����������ƿƵĽ�ɫ����ʹ��һ��ˢҹ��",

	"����(�����ж�����ö�������)��ӵ�м�����ʡ����ᡣ\n\n\
���٣�����ļ����ܵ��˺�ʱ�������������������������ֵ��ȡ���������װ���ƣ�������Խ�������������ɫ��װ�����ڡ�\n\
���᣺����Ļغϣ���������ɫ�������ڽ�����ɽ������ƶ�ǰ������Ի�ô��ơ�",

	"������(ʹ�ö������ƣ����ƾ���)��ӵ�м��ܾ�����������\n\n\
������ÿ�غ���һ�Σ����������һ���ƣ�Ȼ��ѡ��һ����ɫ�����ƣ�����Ϊ���������ƣ�����Ϊ��ʹ�ô��ƣ���������������ƶѡ�\n\
�����������������Խ�ɫ����������ʼ�� + 1������Ů�Խ�ɫ�������ʼ�� - 1��",

	"������(�������ܶ���)��ӵ�м��ܷ�˼�����㡣\n\n\
��˼��������������ļ��㷢���仯ʱ������û�н�����ٹҿ�״̬������1���ơ�\n\
���㣺�غϽ����׶Σ�����Է����ƶѶ�1 + X���ƣ�ȡ�����е���֮�Ͳ�����13���ƣ�չʾ�����������������Ƽ������ƻ򽻸�������ɫ�������������ƣ�XΪ������ʧ������ֵ����",

	"��ΰ�(�������ƣ��ͷ�������)��ӵ�м������ˡ����̡���ǡ�\n\n\
���ˣ���������ʹ��ҿƵĽ�ɫ���������е��ơ�\n\
���̣����غϿ�ʼʱ������������Ϊȫ�����ٻ�֮һ������Զ��������ơ�\n\
��ǣ�����Ļغ��⣬�����˶�������ɫ�ļ���������˺������������һ���ƣ�ʹ��ûغϵ��������� - 1��",
	
	"����(����Ŀ�꣬���ö�����)��ӵ�м��ܾ��㡢������\n\n\
���㣺����غϳ��ƽ׶Σ�����ʹ����һ��ָ����������ɫ�ķ���ʱ�����ƣ�����Դ�����Ч����ѡ��һ�\n\
	����ָ��һ��Ŀ��\n\
	��ָ��һ��Ŀ��\n\
�����������ܵ��˺�ʱ�������������������������ɫ��һ���ơ�",

	"����˼��(�����������ƣ��߷���)��ӵ�м����⽻�����⡣\n\n\
�⽻�����ƽ׶���һ�Σ�����Խ�������������ɫ���ƻ�ĳһ�����ڵ��ƣ����ܵ�ʧȥ�����϶�Ľ�ɫ������ɵ�X�����˺���XΪ������ֵ��һ�벢������ȡ������\n\
���⣺����ļ����ܵ��˺�ʱ������Խ���һ���ж��������Ϊ��ɫ��������һ�����㣬�����Ϊ��ɫ���˺���Դ������һ���ơ�",


	"������(�ҿƼ���)��ӵ�м��ܲ��͡��ܱʡ�\n\n\
���ͣ�����غϽ����׶ο�ʼʱ�������佫����û���ƣ�����Խ�����������÷������������佫���ϣ���Ϊ�����͡������н�ɫ������ٹҿ�״̬ʱ�����������һ�š����͡�����Ϊ��ʹ����һ�š�ˢҹ����\n\
�ܱʣ����������غϿ�ʼʱ�鿴����佫�ƣ�������û�С����͡�������Զ�����һ���ƣ���������С����͡�����غ��ڵĵ�һ�ű�ѧ�����Ӿ��롣",
	
	"���(�������ƣ��˺���Դ����)��ӵ�м�����������ġ�\n\n\
�����������ɫ���ƽ׶ν���ʱ�������ѡ������ĳһ��ɫ���ƣ����֮���߽��佻��ԭ��ɫ��\n\
���ģ��������������ܵ��˺�ʱ������˺���Դ���档",

	"���(�������ƣ�����)��ӵ�м�����������֡�\n\n\
�����������ɫ���ƽ׶ν���ʱ�������ѡ������ĳһ��ɫ���ƣ����֮���߽��佻��ԭ��ɫ��\n\
���֣������ʹ�������ɫ�����ڵ��ƴ����ж��ơ�",

	"ë˳��(���⹥��)��ӵ�м��ܿ�Ĥ����ˮ��\n\n\
��Ĥ������Ļغ��⣬������Ҫ���һ�ű�ѧ�˵�ʱ�򣬿��Խ���һ���ж�������Ϊ���ң�����Ϊ������һ�ű�ѧ�ˡ�\n\
��ˮ�����ƽ׶Σ������ָ��һ����ɫ������X���ƣ�Ȼ����ý�ɫѡ��һ�\n\
	����X����\n\
	�ܵ�һ���㵳��ѹ��",

	"ë��(���⹥��������ѹ��)��ӵ�м��ܿ�Ĥ����Ĥ��֧����\n\n\
��Ĥ������Ļغ��⣬������Ҫ���һ�ű�ѧ�˵�ʱ�򣬿��Խ���һ���ж�������Ϊ���ң�����Ϊ������һ�ű�ѧ�ˡ�\n\
��Ĥ�������������һ����ɫ���Լ��Ļغ϶�������ɫ�ļ�����ɵ��𺦣������������һ�����ƣ���Ϊ������һ�Ż�Ĥ��",

	"���Ć�(�������ƣ�����)��ӵ�м��ܸ�����ɨ�ס�ͳһ��\n\n\
�������غϿ�ʼ�׶Σ�����Խ���һ���ж�����Ϊ���ң������������ƣ�Ȼ���������ƽ�������������ɫ��\n\
ɨ�ף���һ���ж�����Чǰ������Է����ƶѶ�һ���ƴ���ԭ�е��ж��ơ�\n\
ͳһ���೤������������ɫ������һ���ж��׶ν���֮�󽻸���һ���ơ�",

	"�麣��(��������)��ӵ�м���Ĥ��\n\n\
Ĥ�򣺳��ƽ׶���һ�Σ������ʧȥһ�����㲢��һ���ƣ�Ȼ��ʹ��һ����ɫ����һ�������������һ���������ޡ�",

	"�ζ�(�������ƣ�ת���˺�)��ӵ�м��ܲ�ѧ��������\n\n\
��ѧ�����ƽ׶ο�ʼʱ������Է������ƣ���Ϊչʾ�ƶѶ�5���ƣ�֮��������ÿ�ֻ�ɫ���Ƹ�һ�ţ�������������ƶѡ�\n\
����������һ�����Խ�ɫ����ָ��ΪΨһĿ��ʱ�����������һ�����ƣ�Ȼ�󽫴�Ŀ��ת�Ƹ���һ���㹥����Χ�ڵ��������Խ�ɫ��",

	"Ҷ���(�������ƣ�װ��ת��)��ӵ�м���Ҷ�䡢��ҵ��\n\n\
Ҷ�䣺�����ܵ��˺�ʱ������ѡ����һ���ƣ�������װ��������ͬʱ����һ��װ���Ʋ�������һ���ơ�\n\
��ҵ������ʧȥװ�����ڵ���ʱ������Խ����������һ��ɫ��װ�����ڡ�",

	"�·���(�߹������߷���)��ӵ�м��ܹ�ȡ�\n\n\
��ȣ�����������������˺�ʱ�����䲻���㹥����Χ�ڣ����˺� + 1��",


	"κҫ��(���⹥������С����)��ӵ�м���ͼ�ۡ����档\n\n\
ͼ�ۣ����ƽ׶���һ�Σ�����Խ�����������ɫָ��Ϊsteam���ѣ�Ȼ�󱾻غ����������˵ľ������Ϊ��������������Сֵ��\n\
���棺����ʹ�ñ�ѧ�˻�Ĥ��һ����ɫ�ļ�������˺�ʱ�����������һ�Ż����ƣ�Ȼ���һ����֮������ͬ�Ľ�ɫ�ļ������һ���˺���",

	"��ΰ��(�߷�����ʹ����ͨ��)��ӵ�м�����˵�����Ρ�\n\n\
��˵�����㵱ǰ��ΪSteam���ѣ�����Լ���Steam����������ͬ��ɫ���Ƶ���ûѧʹ�á�\n\
���Σ����㵱ǰΪSteam���ѣ�������˳�Steam������һ�����Ƶ�����Ϸͨ��ʹ�á�",

	"��پ��(���⹥��)��ӵ�м������塢��硢�쵼��\n\n\
���壺���㱻������ɫ�ı�ѧ��ָ��ΪĿ��ʱ��������ɺ����������һ�Ż����ƣ���Ϊ������һ�ű�ѧ�ˡ�\n\
��磺���Ѽ�������غϽ���ʱ����������ֵΪȫ�����ٻ�֮һ�������һ�㼨�����ޣ�����һ�����㣬���Ҵ�ȫ���������н�ɫ�õ�һ���ƣ�֮������佫�Ʒ��棬�������� + 2��\n\
�쵼���೤����������ƽ�ɫ���������ûѧ��",

	"����(��ö��ּ���)��ӵ�м������塢������\n\n\
���壺�غϽ���ʱ�����㱾�غϱ�������ɫ�ı�ѧ��ָ��ΪĿ�꣬����Զ�����һ�ű�ѧ�ˡ�\n\
�����������ܵ��˺�ʱ������Լ���һ�㼨�����ޣ�Ȼ�����˺���Դ��һ�����ܡ�",

	"�ų���(���ж��ƣ�����������)��ӵ�м�����������ү��\n\n\
��������������ɫ����ʱ���������ж�ʧЧʱ������Ի�øü����ơ�\n\
��ү������Խ�һ�ż����Ƶ�����ʹ�á�",

	"������(�߷�����װ��ת��)��ӵ�м��ܾ��ġ����ȡ�\n\n\
���ģ�ÿ�غ���һ�Σ�����Խ�һ��װ�����ڵ��Ƶ���һ�Ż�����ʹ�û�����\n\
���ȣ�������ɫ��һ�ű�ѧ�˶�����Ч�����ű�ѧ����Ϊһ�ű�ѧ�ˣ����ű�ѧ�˲������ܡ�",

	"������(���У��߹���)��ӵ�м����㼣�����֡����ϡ�\n\n\
�㼣��ÿ���㼨���ܵ��˺�ʱ�����˺���Դ���ƽ������ƶ�ǰ������Խ�����������������ϡ�\n\
���֣������ʹ���������ϵ��ƴ����ж������\n\
���ϣ����Խ��������ϵĺ�ɫ�Ƶ�����ѧ�ˣ���ɫ�Ƶ���ûѧʹ�á�",

	"¡����(�߹�����������������)��ӵ�м��ܽ��桢������\n\n\
���棺��ѧ����ûѧ���Ի�����档\n\
����������Ļغϣ������һ�ź�ɫ�ƽ������ƶ�֮�󣬿���ѡ��\n\
	��һ����\n\
	����������ɫһ������",

	"���ݵ�(������װ������������)��ӵ�м�����ȹ��������\n\n\
��ȹ�������һ����ɫ����˺�ʱ���������øý�ɫװ������һ���ơ�\n\
���������ƽ׶Σ�����������������ƣ�Ȼ��ָ��һ�����Խ�ɫ��Ȼ����������Խ�ɫ������һ�㼨�㡣",

	"�⳯��(Ⱥ���˺����û�����)��ӵ�м��ܿ񻶡���·��У����\n\n\
�񻶣��޶��������ƽ׶Σ�����������н�ɫ��һ���ƣ�Ȼ��ѡ��һ�\n\
	����ȫ������\n\
	��ʧ��������\n\
��·�������ܵ��˺�ʱ����������һ�����ƣ�Ȼ������һ�㼨�����ޡ�\n\
У�����೤������������ƽ�ɫ�ڻغ�����ʧ����ʱ�����Խ���һ���ж�������Ǻ�ɫ������һ���Ʋ�����һ���ơ�",


	"����(�������Ƹ���)��ӵ�м������ơ����ա�׷Ӱ��\n\n\
���ƣ����ƽ׶Σ�����Խ�һ�ź����ƽ���һ��������ɫ��Ȼ����һ���ƣ��������Ϊ��ǰ����ֵ��\n\
���գ��������������Ƶ��������ơ�\n\
׷Ӱ�����������ˣ���������ɫ����������ʱ + 1��",

	"������(�߹���)��ӵ�м���Ȱ�ˡ��ų���\n\n\
Ȱ�ˣ����ƽ׶���һ�Σ���������Ľ�ɫ����һ��ƴ�㡣����Ӯ������ƴ��������ƣ���һ��ʹ�õı�ѧ���˺�+1�������Ӿ��롣\n\
�ų����೤�����������ڽ�ɫ�غϽ���ʱ������Խ�����һ�ź�ɫ�ı�ѧ�ˣ�Ȼ����һ���ơ�",

	"��������(���������ƣ��߷���)��ӵ�м���͵�ġ����ˡ�\n\n\
͵�ģ��غϿ�ʼ�׶Σ������ѡ��һ�\n\
	����һ������\n\
	��һ����ɫչʾ�������\n\
Ȼ��ۿ��ý�ɫ�����Ʋ���������һ�ź�ɫ���ơ�\n\
���ˣ��������������ܵ��˺�ʱ�����㲻���˺���Դ�Ĺ�����Χ�ڣ�����˺� - 1����������һ���ơ�",

	"��ң(Ⱥ�幥�����߷���)��ӵ�м���Լ����ϰ��\n\n\
Լ��������ĳ��ƽ׶Σ�����Խ����Ų�ͬ��ɫ�����Ƶ���Լ��ʹ�á�\n\
ϰ����������������ɫ��������˺���ʱ������û�����ƣ����˺���Դ������һ�����ƣ��������ֹ���˺���",
	
	"ң��(�߷�������������)��ӵ�м���������\n\n\
�����������ܵ��˺�ʱ�������ѡ��һ�\n\
	����ȫ�����ƣ�Ȼ���ֹ���˺�\n\
	��������������ȫ��������������ͬ",

	"֣��(������������)��ӵ�м���Ⱥ����������ͷ����\n\n\
Ⱥ����ÿ�غ���һ�Σ�������ɫ��ָ��Ϊ����֮һʱ������ʧȥһ�����㣬ȡ�����Ƶ����ò������������������ϣ���ΪȺ�ѡ�\n\
���������Ѽ��������㲻����Ⱥ�ѵ�ʱ��ʧȥȺ�����ܣ�����Ⱥ�ѵ������Ʋ���Ⱥ���������ƶѣ����������޸�Ϊ��ǰ���㡣\n\
ͷ�����೤�����������ڽ�ɫ����ʧȥһ�����㣬��һ������ΪȺ����������������ϲ���һ���ơ�",

	"����(�������ƽ׶�)��ӵ�м����мӡ�˼�硣\n\n\
�мӣ������������ɱ������롣\n\
˼�磺����ж��׶ο�ʼʱ������Է��沢�����ж��׶β����ж����������ƶѣ����������������������ƽ׶β��������ơ�",

	"������(�������ƣ��û�����)��ӵ�м��ܶ�ƴ��������\n\n\
��ƴ����������˺�ʱ����������˺��������һ���ơ�\n\
������ÿ�غ���һ�Σ����������ȫ�����ƣ������������ơ�",

	"�պ�(���ƶ��ֳ���Ч��)��ӵ�м��ܸ�����\n\n\
������ÿ�غ���һ�Σ���������ɫʹ�û����ƺͼ�����ָ��ΨһĿ���ʱ������Ŀ�겻Ϊ�㣬������ɺ�����Խ��Լ���Ϊ���Ƶ���һ��ʹ���ߡ�",
	
	"��Zɭ(��������������)��ӵ�м����������ɹ���������\n\n\
�������޶������غϿ�ʼǰ������������������ƣ�Ȼ��ظ���������\n\
�ɹ����غϿ�ʼ�׶Σ������������С����ļ��㣬������������������뼨����ȡ�\n\
�������غϽ����׶Σ����㱾�غϻ���ƹ��ƴ��ڵ������ţ��������ѡ��һ�\n\
	���н�ɫ����һ��������\n\
	���н�ɫ����һ��������"

};

Killer *Killer::newKiller(KILLER k, int p) {
	Killer *ret = new Killer(k, p);

	switch (k) {
	case CS_GTX:
		ret = new CS_gtx(p);
		break;
	case CS_GS:
		ret = new CS_gs(p);
		break;
	case CS_CZZ:
		ret = new CS_czz(p);
		break;
	case CS_SZL:
		ret = new CS_szl(p);
		break;
	case CS_ZRS:
		ret = new CS_zrs(p);
		break;
	case CS_ZS:
		ret = new CS_zs(p);
		break;
	case CS_WYL:
		ret = new CS_wyl(p);
		break;
	case CS_YZY:
		ret = new CS_yzy(p);
		break;
	case CS_HWN:
		ret = new CS_hwn(p);
		break;
	case CS_BS:
		ret = new CS_bs(p);
		break;
	case CS_HYSB:
		ret = new CS_hysb(p);
		break;
	case SE_YNL:
		ret = new SE_ynl(p);
		break;
	case SE_WAMY:
		ret = new SE_wamy(p);
		break;
	case SE_MYS:
		ret = new SE_mys(p);
		break;
	case SE_MSL:
		ret = new SE_msl(p);
		break;
	case SE_MS:
		ret = new SE_ms(p);
		break;
	case SE_MWZ:
		ret = new SE_mwz(p);
		break;
	case SE_HHW:
		ret = new SE_hhw(p);
		break;
	case SE_SD:
		ret = new SE_sd(p);
		break;
	case SE_YJC:
		ret = new SE_yjc(p);
		break;
	case SE_CFC:
		ret = new SE_cfc(p);
		break;
	case CKC_LWYD:
		ret = new CKC_lwyd(p);
		break;
	case CKC_LWX:
		ret = new CKC_lwx(p);
		break;
	case CKC_ZZH:
		ret = new CKC_zzh(p);
		break;
	case CKC_ZS:
		ret = new CKC_zs(p);
		break;
	case CKC_ZCY:
		ret = new CKC_zcy(p);
		break;
	case CKC_ZSB:
		ret = new CKC_zsb(p);
		break;
	case CKC_YTY:
		ret = new CKC_yty(p);
		break;
	case CKC_LJW:
		ret = new CKC_ljw(p);
		break;
	case CKC_SWYD:
		ret = new CKC_swyd(p);
		break;
	case CKC_WZH:
		ret = new CKC_wzh(p);
		break;
	case OT_GY:
		ret = new OT_gy(p);
		break;
	case OT_SMQ:
		ret = new OT_smq(p);
		break;
	case OT_YXTR:
		ret = new OT_yxtr(p);
		break;
	case OT_ZY:
		ret = new OT_zy(p);
		break;
	case OT_YS:
		ret = new OT_ys(p);
		break;
	case OT_ZH:
		ret = new OT_zh(p);
		break;
	case OT_YX:
		ret = new OT_yx(p);
		break;
	case OT_LZL:
		ret = new OT_lzl(p);
		break;
	case OT_SH:
		ret = new OT_sh(p);
		break;
	case OT_ZJS:
		ret = new OT_zjs(p);
		break;
	case NO_KILLER:
	case KILLER_END:
	default:
		break;
	}
	return ret;
}

void addEquip(Card c, int playerPos, int deltaPos) {
	int posx, posy, tfsize;
	if (deltaPos == 0) {
		posx = 508;
		posy = 380;
		tfsize = 20;
	}
	else {
		posx = 16 + 80 * (deltaPos - 1);
		posy = 70;
		tfsize = 12;
	}
	switch (c.cont) {
	case CC_SCRIPT:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "�����ű�", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_LOLI:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "ˮ�ַ�", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_VIRUS:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "����", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_LINE:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "����", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_OFFLINE:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "����ϵͳ", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_BOOM:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "������Ƶ", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_SPINPEN:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "תת��", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_PTA:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "�����˺�", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_CHICKEN:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "����ɱ", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_CHAIRMAN:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "��ϯ��¼", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_GUARD:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "�����Ʒ�", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_KEYBOARD:
		easyWidget(SG_LABEL, (string("defender" + std::to_string(playerPos)).data()),
			posx, posy + tfsize, 60, 10, "�������", NULL);
		getWidgetByName((string("defender" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_FLYING:
		easyWidget(SG_LABEL, (string("defender" + std::to_string(playerPos)).data()),
			posx, posy + tfsize, 60, 10, "����ģʽ", NULL);
		getWidgetByName((string("defender" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_GLASSES:
		easyWidget(SG_LABEL, (string("defender" + std::to_string(playerPos)).data()),
			posx, posy + tfsize, 60, 10, "�ڿ��۾�", NULL);
		getWidgetByName((string("defender" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_GTX:
		easyWidget(SG_LABEL, (string("defender" + std::to_string(playerPos)).data()),
			posx, posy + tfsize, 60, 10, "�����Կ�", NULL);
		getWidgetByName((string("defender" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_DBELEPHANT:
		easyWidget(SG_LABEL, (string("defender" + std::to_string(playerPos)).data()),
			posx, posy + tfsize, 60, 10, "����", NULL);
		getWidgetByName((string("defender" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_MOTOR:
		easyWidget(SG_LABEL, (string("vehicle" + std::to_string(playerPos)).data()),
			posx, posy + 2 * tfsize, 60, 10, "С��", NULL);
		getWidgetByName((string("vehicle" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_BUS:
		easyWidget(SG_LABEL, (string("vehicle" + std::to_string(playerPos)).data()),
			posx, posy + 2 * tfsize, 60, 10, "У��", NULL);
		getWidgetByName((string("vehicle" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_ARM:
		easyWidget(SG_LABEL, (string("vehicle" + std::to_string(playerPos)).data()),
			posx, posy + 2 * tfsize, 60, 10, "���", NULL);
		getWidgetByName((string("vehicle" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_LAKE:
		easyWidget(SG_LABEL, (string("barrier" + std::to_string(playerPos)).data()),
			posx, posy + 3 * tfsize, 60, 10, "�����", NULL);
		getWidgetByName((string("barrier" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_MOUNTAIN:
		easyWidget(SG_LABEL, (string("barrier" + std::to_string(playerPos)).data()),
			posx, posy + 3 * tfsize, 60, 10, "�Ϻ�ɽ", NULL);
		getWidgetByName((string("barrier" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_BUILDING:
		easyWidget(SG_LABEL, (string("barrier" + std::to_string(playerPos)).data()),
			posx, posy + 3 * tfsize, 60, 10, "����¥", NULL);
		getWidgetByName((string("barrier" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_FOREST:
		easyWidget(SG_LABEL, (string("barrier" + std::to_string(playerPos)).data()),
			posx, posy + 3 * tfsize, 60, 10, "У����", NULL);
		getWidgetByName((string("barrier" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	default:
		return;
	}
}
void removeEquip(int type, int pos) {

}