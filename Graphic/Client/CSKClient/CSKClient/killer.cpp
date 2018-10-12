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
	"������(�߹�������������)��ӵ�м��ܸ���þ���",
	"����(���ƣ��߷���)��ӵ�м��ܿ��С���Ŀ��",
	"��չ�(Ⱥ���˺������ö�����)��ӵ�м���ѧ�ԡ��񾺡�",
	"��ռ��(�������ƣ�����ظ�����)��ӵ�м��ܿ�ѧ��͵ѧ��������",
	"����N(�������ˣ�Ⱥ���˺�)��ӵ�м��ܳ��顢���㡢��顣",
	"����(�����ж�����ö�������)��ӵ�м�����ʡ����ᡣ",
	"������(ʹ�ö������ƣ����ƾ���)��ӵ�м��ܾ�����������",
	"������(�������ܶ���)��ӵ�м��ܷ�˼�����㡣",
	"��ΰ�(�������ƣ��ͷ�������)��ӵ�м������ˡ����̡���ǡ�",
	"����(����Ŀ�꣬���ö�����)��ӵ�м��ܾ��㡢������",
	"����˼��(�����������ƣ��߷���)��ӵ�м����⽻�����⡣",
	"������(�ҿƼ���)��ӵ�м��ܲ��͡��ܱʡ�",
	"���(�������ƣ��˺���Դ����)��ӵ�м�����������ġ�",
	"���(�������ƣ�����)��ӵ�м�����������֡�",
	"ë˳��(���⹥��)��ӵ�м��ܿ�Ĥ����ˮ��",
	"ë��(���⹥��������ѹ��)��ӵ�м��ܿ�Ĥ����Ĥ��֧����",
	"���Ć�(�������ƣ�����)��ӵ�м��ܸ�����ɨ�ס�ͳһ��",
	"�麣��(��������)��ӵ�м���Ĥ��",
	"�ζ�(�������ƣ�ת���˺�)��ӵ�м��ܲ�ѧ��������",
	"Ҷ���(�������ƣ�װ��ת��)��ӵ�м���Ҷ�䡢��ҵ��",
	"�·���(�߹������߷���)��ӵ�м��ܹ�ȡ�",
	"κҫ��(���⹥������С����)��ӵ�м���ͼ�ۡ����档",
	"��ΰ��(�߷�����ʹ����ͨ��)��ӵ�м�����˵�����Ρ�",
	"��پ��(���⹥��)��ӵ�м������塢��硢�쵼��",
	"����(��ö��ּ���)��ӵ�м������塢������",
	"�ų���(���ж��ƣ�����������)��ӵ�м�����������ү��",
	"������(�߷�����װ��ת��)��ӵ�м��ܾ��ġ����ȡ�",
	"������(���У��߹���)��ӵ�м����㼣�����֡����ϡ�",
	"¡����(�߹�����������������)��ӵ�м��ܽ��桢������",
	"���ݵ�(������װ������������)��ӵ�м�����ȹ��������",
	"�⳯��(Ⱥ���˺����û�����)��ӵ�м��ܿ񻶡���·��У����",
	"����(�������Ƹ���)��ӵ�м������ơ����ա�׷Ӱ��",
	"������(�߹���)��ӵ�м���Ȱ�ˡ��ų���",
	"��������(���������ƣ��߷���)��ӵ�м���͵�ġ����ˡ�",
	"��ң(Ⱥ�幥�����߷���)��ӵ�м���Լ����ϰ��",
	"ң��(�߷�������������)��ӵ�м���������",
	"֣��(������������)��ӵ�м���Ⱥ����������ͷ����",
	"����(�������ƽ׶�)��ӵ�м����мӡ�˼�硣",
	"������(�������ƣ��û�����)��ӵ�м��ܶ�ƴ��������",
	"�պ�(���ƶ��ֳ���Ч��)��ӵ�м��ܸ�����",
	"��Zɭ(��������������)��ӵ�м����������ɹ���������"
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
