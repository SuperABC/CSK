#include "killer.h"
#include "cs.h"
#include "se.h"
#include "ckc.h"
#include "ot.h"

const char *killerName[] = {
	"学生",

	"高天祥",
	"高神",
	"蔡展璋",
	"孙占林",
	"朱瑞昇",
	"朱神",
	"王宜霖",
	"于振云",
	"黄伟楠",
	"边淞",
	"黄杨思博",
	"余南龙",
	"王淼",
	"淼神",
	"毛顺龙",
	"毛神",
	"马文喆",
	"洪海文",
	"宋鼎",
	"叶靖琛",
	"陈方超",
	"魏耀东",
	"梁伟欣",
	"张倬豪",
	"张神",
	"张程易",
	"朱淞泊",
	"杨天宇",
	"隆晋威",
	"王逸旦",
	"吴朝晖",
	"高雅",
	"孙铭琦",
	"闫徐天任",
	"邹遥",
	"遥神",
	"郑虎",
	"杨熙",
	"李自乐",
	"苏杭",
	"朱璟森"
};

const char *killerDetail[] = {
	"普通学生，没有技能。",
	"高天祥(高攻击，额外摸牌)，拥有技能高深、幻境。",
	"高神(屯牌，高防御)，拥有技能科研、名目。",
	"蔡展璋(群体伤害，弃置对手牌)，拥有技能学霸、恶竞。",
	"孙占林(额外摸牌，额外回复绩点)，拥有技能苦学、偷学、自恋。",
	"朱瑞昇(减少受伤，群体伤害)，拥有技能痴情、天秀、醉归。",
	"朱神(免疫判定，获得对手手牌)，拥有技能天妒、豪夺。",
	"王宜霖(使用对手手牌，限制距离)，拥有技能绝世、居所。",
	"于振云(额外摸很多牌)，拥有技能反思、超算。",
	"黄伟楠(额外摸牌，惩罚伤人者)，拥有技能凉了、滋滋、书记。",
	"边淞(调整目标，弃置对手牌)，拥有技能精算、智御。",
	"黄杨思博(交换对手手牌，高防御)，拥有技能外交、联衡。",
	"余南龙(挂科急救)，拥有技能博客、奋笔。",
	"王淼(回收弃牌，伤害来源翻面)，拥有技能外包、核心。",
	"淼神(回收弃牌，改判)，拥有技能外包、信手。",
	"毛顺龙(额外攻击)，拥有技能狂膜、大水。",
	"毛神(额外攻击，党性压制)，拥有技能狂膜、乱膜、支部。",
	"马文喆(额外摸牌，改判)，拥有技能福利、扫雷、统一。",
	"洪海文(绩点输送)，拥有技能膜蛤。",
	"宋鼎(额外摸牌，转移伤害)，拥有技能博学、耽美。",
	"叶靖琛(额外摸牌，装备转移)，拥有技能叶落、授业。",
	"陈方超(高攻击，高防御)，拥有技能灌溉。",
	"魏耀东(额外攻击，减小距离)，拥有技能图论、二叉。",
	"梁伟欣(高防御，使他人通宵)，拥有技能演说、护肝。",
	"张倬豪(额外攻击)，拥有技能震慑、大哥、领导。",
	"张神(获得对手技能)，拥有技能震慑、毕至。",
	"张程易(得判定牌，防御技巧牌)，拥有技能闻名、大爷。",
	"朱淞伯(高防御，装备转化)，拥有技能静心、卖萌。",
	"杨天宇(改判，高攻防)，拥有技能足迹、数分、北上。",
	"隆晋威(高攻防，额外摸牌弃牌)，拥有技能交叉、龙吟。",
	"王逸旦(弃对手装备，提升绩点)，拥有技能褪裙、给力。",
	"吴朝晖(群体伤害，置换手牌)，拥有技能狂欢、天路、校长。",
	"高雅(额外摸牌给牌)，拥有技能内推、红颜、追影。",
	"孙明琦(高攻击)，拥有技能劝退、团长。",
	"闫徐天任(弃对手手牌，高防御)，拥有技能偷拍、溜了。",
	"邹遥(群体攻击，高防御)，拥有技能约饭、习蛤",
	"遥神(高防御，额外摸牌)，拥有技能心望。",
	"郑虎(提升绩点上限)，拥有技能群主、开车、头条。",
	"杨熙(跳过弃牌阶段)，拥有技能中加、思乡。",
	"李自乐(额外摸牌，置换手牌)，拥有技能多拼、历经。",
	"苏杭(复制对手出牌效果)，拥有技能复读。",
	"朱璟森(重生，额外摸牌)，拥有技能满绩、成功、教主。"
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
		break;
	case CKC_LWX:
		break;
	case CKC_ZZH:
		break;
	case CKC_ZS:
		break;
	case CKC_ZCY:
		break;
	case CKC_ZSB:
		break;
	case CKC_YTY:
		break;
	case CKC_LJW:
		break;
	case CKC_SWYD:
		break;
	case CKC_WZH:
		break;
	case OT_GY:
		break;
	case OT_SMQ:
		break;
	case OT_YXTR:
		break;
	case OT_ZY:
		break;
	case OT_YS:
		break;
	case OT_ZH:
		break;
	case OT_YX:
		break;
	case OT_LZL:
		break;
	case OT_SH:
		break;
	case OT_ZJS:
		break;
	case NO_KILLER:
	case KILLER_END:
	default:
		break;
	}
	return ret;
}
