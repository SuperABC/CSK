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

	"高天祥(高攻击，额外摸牌)，拥有技能高深、幻境。\n\n\
高深：锁定技，当其他角色在你的回合需要使用一张没学时，必须先弃置一张手牌。\n\
幻境：当你被黑色技巧牌指定为目标时，结算完成后你可以摸一张牌。\n\
蔑视：班长技，一名计科角色可以在回合结束之后让你摸X张牌（X为其回合内使其他角色进入濒临挂科状态的角色个数）。",
	
	"高神(屯牌，高防御)，拥有技能科研、名目。\n\n\
科研：回合开始时，你可以将一名角色的全部手牌置于武将牌上，当回合结束的时候该角色获得这些牌。\n\
名目：锁定技，你无法成为手牌数大于你当前绩点的角色“别学了”和“决斗”的目标。",

	"蔡展璋(群体伤害，弃置对手牌)，拥有技能学霸、恶竞。\n\n\
学霸：出牌阶段限一次，你可以指定一名其攻击范围内包含你自己的其他角色，该角色需对你使用一张别学了，否则你弃置其一张牌。\n\
恶竞：限定技，在你出牌阶段，若你不为满绩，你可以选择所有其他角色，这些角色各需对距离最近的另一名角色使用一张别学了，否则其损失一个绩点。",
	
	"孙占林(额外摸牌，额外回复绩点)，拥有技能苦学、偷学、自恋。\n\n\
苦学：每回合限一次，你可以将一张黑桃牌当做刷夜使用。\n\
偷学：当你回合结束时，若你不为满绩，你可以额外弃置一张手牌，提升一个绩点。\n\
自恋：锁定技，摸牌阶段，若你已受伤，则你额外摸X张牌（X为你已损失的体力值）。",

	"朱瑞昇(减少受伤，群体伤害)，拥有技能痴情、天秀、醉归。\n\n\
天妒：锁定技，你的延时性技巧牌在判定时均视为判定失效。\n\
痴情：始终视为有对象。\n\
天秀：限定技，出牌阶段，你可以展示一张红桃牌，令其他所有角色选择一项：\n\
	弃置所有装备牌\n\
	失去一个绩点\n\
醉归：班长技，在你濒临挂科的时候，可以让其他计科的角色帮你使用一张刷夜。",

	"朱神(免疫判定，获得对手手牌)，拥有技能天妒、豪夺。\n\n\
神速：当你的绩点受到伤害时，你可以摸牌至手牌数与体力值相等。若其中有装备牌，则你可以将其放置在任意角色的装备区内。\n\
豪夺：在你的回合，当其他角色的手牌在结算完成进入弃牌堆前，你可以获得此牌。",

	"王宜霖(使用对手手牌，限制距离)，拥有技能绝世、居所。\n\n\
绝世：每回合限一次，你可以声明一种牌，然后选择一名角色的手牌，若其为所声明的牌，则视为你使用此牌，否则此牌置入弃牌堆。\n\
居所：锁定技，男性角色与你计算距离始终 + 1，你与女性角色计算距离始终 - 1。",

	"于振云(额外摸很多牌)，拥有技能反思、超算。\n\n\
反思：锁定技，当你的绩点发生变化时，若你没有进入濒临挂科状态，你摸1张牌。\n\
超算：回合结束阶段，你可以翻开牌堆顶1 + X张牌，取走其中点数之和不超过13的牌，展示后将其中任意数量的牌加入手牌或交给其他角色，弃置其他的牌（X为你已损失的体力值）。",

	"黄伟楠(额外摸牌，惩罚伤人者)，拥有技能凉了、滋滋、书记。\n\n\
凉了：锁定技，使你挂科的角色须弃置所有的牌。\n\
滋滋：当回合开始时，若你手牌数为全场最少或之一，你可以多摸两张牌。\n\
书记：在你的回合外，若有人对其他角色的绩点造成了伤害，你可以弃置一张牌，使其该回合的手牌上限 - 1。",
	
	"边淞(调整目标，弃置对手牌)，拥有技能精算、智御。\n\n\
精算：在你回合出牌阶段，若你使用了一张指定了其他角色的非延时技巧牌，你可以从下列效果中选择一项：\n\
	额外指定一个目标\n\
	少指定一个目标\n\
智御：当你受到伤害时，你可以弃置至多两名其他角色各一张牌。",

	"黄杨思博(交换对手手牌，高防御)，拥有技能外交、联衡。\n\n\
外交：出牌阶段限一次，你可以交换另外两名角色手牌或某一区域内的牌，并受到失去牌数较多的角色对你造成的X绩点伤害（X为牌数差值的一半并且向上取整）。\n\
联衡：当你的绩点受到伤害时，你可以进行一次判定，若结果为红色则你提升一个绩点，若结果为黑色则伤害来源须弃置一张牌。",


	"余南龙(挂科急救)，拥有技能博客、奋笔。\n\n\
博客：在你回合结束阶段开始时，若你武将牌上没有牌，你可以将任意数量的梅花牌置于你的武将牌上，称为“博客”，当有角色进入濒临挂科状态时，你可以弃置一张“博客”，视为其使用了一张“刷夜”。\n\
奋笔：锁定技，回合开始时查看你的武将牌，若上面没有“博客”，你可以额外摸一张牌，如果上面有“博客”，你回合内的第一张别学了无视距离。",
	
	"王淼(回收弃牌，伤害来源翻面)，拥有技能外包、核心。\n\n\
外包：其他角色弃牌阶段结束时，你可以选择其中某一颜色的牌，获得之或者将其交给原角色。\n\
核心：锁定技，当你受到伤害时，你的伤害来源翻面。",

	"淼神(回收弃牌，改判)，拥有技能外包、信手。\n\n\
外包：其他角色弃牌阶段结束时，你可以选择其中某一颜色的牌，获得之或者将其交给原角色。\n\
信手：你可以使用任意角色区域内的牌代替判定牌。",

	"毛顺龙(额外攻击)，拥有技能狂膜、大水。\n\n\
狂膜：在你的回合外，当你需要打出一张别学了的时候，可以进行一次判定，若不为红桃，则视为你打出了一张别学了。\n\
大水：出牌阶段，你可以指定一名角色并弃置X张牌，然后令该角色选择一项：\n\
	弃置X张牌\n\
	受到一绩点党性压制",

	"毛神(额外攻击，党性压制)，拥有技能狂膜、乱膜、支部。\n\n\
狂膜：在你的回合外，当你需要打出一张别学了的时候，可以进行一次判定，若不为红桃，则视为你打出了一张别学了。\n\
乱膜：当除你以外的一名角色在自己的回合对其他角色的绩点造成的损害，则你可以弃置一张手牌，视为对其打出一张互膜。",

	"马文喆(额外摸牌，改判)，拥有技能福利、扫雷、统一。\n\n\
福利：回合开始阶段，你可以进行一次判定，若为红桃，则你摸两张牌，然后将任意张牌交给任意其他角色。\n\
扫雷：当一张判定牌生效前，你可以翻开牌堆顶一张牌代替原有的判定牌。\n\
统一：班长技，其他软工角色可以在一次判定阶段结束之后交给你一张牌。",

	"洪海文(绩点输送)，拥有技能膜蛤。\n\n\
膜蛤：出牌阶段限一次，你可以失去一个绩点并摸一张牌，然后使另一名角色提升一个绩点或者提升一个绩点上限。",

	"宋鼎(额外摸牌，转移伤害)，拥有技能博学、耽美。\n\n\
博学：摸牌阶段开始时，你可以放弃摸牌，改为展示牌堆顶5张牌，之后获得其中每种花色的牌各一张，其余的置入弃牌堆。\n\
耽美：当被一名男性角色的牌指定为唯一目标时，你可以弃置一张手牌，然后将此目标转移给另一名你攻击范围内的其他男性角色。",

	"叶靖琛(额外摸牌，装备转移)，拥有技能叶落、授业。\n\n\
叶落：当你受到伤害时，可以选择摸一张牌，若你有装备，可以同时弃置一张装备牌并额外摸一张牌。\n\
授业：当你失去装备区内的牌时，你可以将其放置在另一角色的装备区内。",

	"陈方超(高攻击，高防御)，拥有技能灌溉。\n\n\
灌溉：锁定技，当你造成伤害时，若其不在你攻击范围内，则伤害 + 1。",


	"魏耀东(额外攻击，减小距离)，拥有技能图论、二叉。\n\n\
图论：出牌阶段限一次，你可以将任意两名角色指定为steam好友，然后本回合你与这两人的距离计算为二人与你距离的最小值。\n\
二叉：当你使用别学了或互膜对一名角色的绩点造成伤害时，你可以弃置一张基本牌，然后对一名与之距离相同的角色的绩点造成一点伤害。",

	"梁伟欣(高防御，使他人通宵)，拥有技能演说、护肝。\n\n\
演说：若你当前不为Steam好友，你可以加入Steam并将两张相同颜色的牌当做没学使用。\n\
护肝：若你当前为Steam好友，你可以退出Steam，并将一张手牌当做游戏通宵使用。",

	"张倬豪(额外攻击)，拥有技能震慑、大哥、领导。\n\n\
震慑：当你被其他角色的别学了指定为目标时，结算完成后，你可以弃置一张基本牌，视为对其打出一张别学了。\n\
大哥：觉醒技，当你回合结束时，若你体力值为全场最少或之一，你减少一点绩点上限，提升一个绩点，并且从全场其他所有角色得到一张牌，之后你的武将牌翻面，手牌上限 + 2。\n\
领导：班长技，其他求科角色可以替你出没学。",

	"张神(获得对手技能)，拥有技能震慑、毕至。\n\n\
震慑：回合结束时，若你本回合被其他角色的别学了指定为目标，你可以对其打出一张别学了。\n\
毕至：当你受到伤害时，你可以减少一点绩点上限，然后获得伤害来源的一个技能。",

	"张程易(得判定牌，防御技巧牌)，拥有技能闻名、大爷。\n\n\
闻名：当其他角色的延时技巧牌因判定失效时，你可以获得该技巧牌。\n\
大爷：你可以将一张技巧牌当做滚使用。",

	"朱淞伯(高防御，装备转化)，拥有技能静心、卖萌。\n\n\
静心：每回合限一次，你可以将一张装备区内的牌当做一张基本牌使用或打出。\n\
卖萌：其他角色的一张别学了对你无效，两张别学了视为一张别学了，三张别学了不可闪避。",

	"杨天宇(改判，高攻防)，拥有技能足迹、数分、北上。\n\n\
足迹：每当你绩点受到伤害时，在伤害来源的牌进入弃牌堆前，你可以将其置于你的人物牌上。\n\
数分：你可以使用人物牌上的牌代替判定结果。\n\
北上：可以将人物牌上的黑色牌当做别学了，红色牌当做没学使用。",

	"隆晋威(高攻防，额外摸牌弃牌)，拥有技能交叉、龙吟。\n\n\
交叉：别学了与没学可以互相代替。\n\
龙吟：在你的回合，当你的一张黑色牌进入弃牌堆之后，可以选择：\n\
	摸一张牌\n\
	弃掉其他角色一张手牌",

	"王逸旦(弃对手装备，提升绩点)，拥有技能褪裙、给力。\n\n\
褪裙：当你对一名角色造成伤害时，可以弃置该角色装备区内一张牌。\n\
给力：出牌阶段，你可以弃置两张手牌，然后指定一名男性角色，然后你与该男性角色都提升一点绩点。",

	"吴朝晖(群体伤害，置换手牌)，拥有技能狂欢、天路、校长。\n\n\
狂欢：限定技，出牌阶段，你可以令所有角色摸一张牌，然后选择一项：\n\
	弃置全部手牌\n\
	损失两个绩点\n\
天路：当你受到伤害时，可以弃置一张手牌，然后增加一点绩点上限。\n\
校长：班长技，当其他求科角色在回合外损失手牌时，可以进行一次判定，如果是红色则你摸一张牌并弃置一张牌。",


	"高雅(额外摸牌给牌)，拥有技能内推、红颜、追影。\n\n\
内推：出牌阶段，你可以将一张红桃牌交给一名其他角色，然后摸一张牌（次数最多为当前体力值）\n\
红颜：锁定技，黑桃牌当做红桃牌。\n\
追影：若你已受伤，则其他角色与你计算距离时 + 1。",

	"孙明琦(高攻击)，拥有技能劝退、团长。\n\n\
劝退：出牌阶段限一次，你可以与别的角色进行一次拼点。若你赢，你获得拼点的两张牌，下一张使用的别学了伤害+1并且无视距离。\n\
团长：班长技，其他大众角色回合结束时，其可以交给你一张红色的别学了，然后摸一张牌。",

	"闫徐天任(弃对手手牌，高防御)，拥有技能偷拍、溜了。\n\n\
偷拍：回合开始阶段，你可以选择一项：\n\
	弃置一张手牌\n\
	给一名角色展示你的手牌\n\
然后观看该角色的手牌并弃置其中一张黑色的牌。\n\
溜了：锁定技，当你受到伤害时，若你不在伤害来源的攻击范围内，则此伤害 - 1，否则你摸一张牌。",

	"邹遥(群体攻击，高防御)，拥有技能约饭、习蛤。\n\n\
约饭：在你的出牌阶段，你可以将两张不同颜色的手牌当做约饭使用。\n\
习蛤：锁定技，其他角色对你造成伤害的时候，若你没有手牌，则伤害来源需弃置一张手牌，否则你防止此伤害。",
	
	"遥神(高防御，额外摸牌)，拥有技能心望。\n\n\
心望：当你受到伤害时，你可以选择一项：\n\
	弃置全部手牌，然后防止此伤害\n\
	摸牌至手牌数与全场手牌最多的人相同",

	"郑虎(提升绩点上限)，拥有技能群主、开车、头条。\n\n\
群主：每回合限一次，当被黑色牌指定为对象之一时，可以失去一个绩点，取消该牌的作用并将该牌置于人物牌上，记为群费。\n\
开车：觉醒技，当绩点不大于群费的时候，失去群主技能，摸与群费等量的牌并将群费置于弃牌堆，将绩点上限改为当前绩点。\n\
头条：班长技，其他大众角色可以失去一个绩点，将一张牌作为群费置于你的人物牌上并摸一张牌。",

	"杨熙(跳过弃牌阶段)，拥有技能中加、思乡。\n\n\
中加：锁定技，不可被抄代码。\n\
思乡：你的判定阶段开始时，你可以翻面并跳过判定阶段并将判定牌置入弃牌堆，若如此做，你可以跳过弃牌阶段并摸两张牌。",

	"李自乐(额外摸牌，置换手牌)，拥有技能多拼、历经。\n\n\
多拼：当你造成伤害时，你可以与伤害对象各摸一张牌。\n\
历经：每回合限一次，你可以弃掉全部手牌，并摸等量的牌。",

	"苏杭(复制对手出牌效果)，拥有技能复读。\n\n\
复读：每回合限一次，当其他角色使用基本牌和技巧牌指定唯一目标的时候，若该目标不为你，结算完成后你可以将自己作为该牌的另一个使用者。",
	
	"朱璟森(重生，额外摸牌)，拥有技能满绩、成功、教主。\n\n\
满绩：限定技，回合开始前，你可以弃置所有手牌，然后回复至满绩。\n\
成功：回合开始阶段，若你的手牌数小于你的绩点，你可以摸牌至手牌数与绩点相等。\n\
教主：回合结束阶段，若你本回合获得牌共计大于等于六张，则你可以选择一项：\n\
	所有角色增加一绩点上限\n\
	所有角色减少一绩点上限"

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
			posx, posy, 60, 10, "卖弱脚本", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_LOLI:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "水手服", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_VIRUS:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "病毒", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_LINE:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "网线", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_OFFLINE:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "盗版系统", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_BOOM:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "抖音视频", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_SPINPEN:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "转转笔", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_PTA:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "互评账号", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_CHICKEN:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "大逃杀", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_CHAIRMAN:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "主席语录", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_GUARD:
		easyWidget(SG_LABEL, (string("weapon" + std::to_string(playerPos)).data()),
			posx, posy, 60, 10, "保安制服", NULL);
		getWidgetByName((string("weapon" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_KEYBOARD:
		easyWidget(SG_LABEL, (string("defender" + std::to_string(playerPos)).data()),
			posx, posy + tfsize, 60, 10, "红轴键盘", NULL);
		getWidgetByName((string("defender" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_FLYING:
		easyWidget(SG_LABEL, (string("defender" + std::to_string(playerPos)).data()),
			posx, posy + tfsize, 60, 10, "飞行模式", NULL);
		getWidgetByName((string("defender" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_GLASSES:
		easyWidget(SG_LABEL, (string("defender" + std::to_string(playerPos)).data()),
			posx, posy + tfsize, 60, 10, "黑框眼镜", NULL);
		getWidgetByName((string("defender" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_GTX:
		easyWidget(SG_LABEL, (string("defender" + std::to_string(playerPos)).data()),
			posx, posy + tfsize, 60, 10, "集成显卡", NULL);
		getWidgetByName((string("defender" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_DBELEPHANT:
		easyWidget(SG_LABEL, (string("defender" + std::to_string(playerPos)).data()),
			posx, posy + tfsize, 60, 10, "对象", NULL);
		getWidgetByName((string("defender" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_MOTOR:
		easyWidget(SG_LABEL, (string("vehicle" + std::to_string(playerPos)).data()),
			posx, posy + 2 * tfsize, 60, 10, "小龟", NULL);
		getWidgetByName((string("vehicle" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_BUS:
		easyWidget(SG_LABEL, (string("vehicle" + std::to_string(playerPos)).data()),
			posx, posy + 2 * tfsize, 60, 10, "校车", NULL);
		getWidgetByName((string("vehicle" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_ARM:
		easyWidget(SG_LABEL, (string("vehicle" + std::to_string(playerPos)).data()),
			posx, posy + 2 * tfsize, 60, 10, "翅膀", NULL);
		getWidgetByName((string("vehicle" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_LAKE:
		easyWidget(SG_LABEL, (string("barrier" + std::to_string(playerPos)).data()),
			posx, posy + 3 * tfsize, 60, 10, "启真湖", NULL);
		getWidgetByName((string("barrier" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_MOUNTAIN:
		easyWidget(SG_LABEL, (string("barrier" + std::to_string(playerPos)).data()),
			posx, posy + 3 * tfsize, 60, 10, "老和山", NULL);
		getWidgetByName((string("barrier" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_BUILDING:
		easyWidget(SG_LABEL, (string("barrier" + std::to_string(playerPos)).data()),
			posx, posy + 3 * tfsize, 60, 10, "行政楼", NULL);
		getWidgetByName((string("barrier" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	case CC_FOREST:
		easyWidget(SG_LABEL, (string("barrier" + std::to_string(playerPos)).data()),
			posx, posy + 3 * tfsize, 60, 10, "校友林", NULL);
		getWidgetByName((string("barrier" + std::to_string(playerPos)).data()))->tf.size = tfsize;
		break;
	default:
		return;
	}
}
void removeEquip(int type, int pos) {

}