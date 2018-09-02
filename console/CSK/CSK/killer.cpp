#include "killer.h"
#include "manager.h"
#include <algorithm>

extern Manager *manager;

bool handLeft(const Card &c1, const Card &c2) {
	int p1, p2;
	switch (c1.cont) {
	case CC_STUDY:
		p1 = 0;
		break;
	case CC_STAYUP:
		p1 = 1;
		break;
	case CC_DENY:
		p1 = 2;
		break;
	case CC_PREVENT:
	case CC_COMMERCE:
	case CC_PARTY:
		p1 = 3;
		break;
	default:
		p1 = INFINITY;
		break;
	}
	switch (c2.cont) {
	case CC_STUDY:
		p2 = 0;
		break;
	case CC_STAYUP:
		p2 = 1;
		break;
	case CC_DENY:
		p2 = 2;
		break;
	case CC_PREVENT:
	case CC_COMMERCE:
	case CC_PARTY:
		p2 = 3;
		break;
	default:
		p2 = INFINITY;
		break;
	}
	return p1 < p2;
}

void Killer::incomeCard(Card c) {
	handCards.cont.push_back(c);
}
void Killer::exeStart() {
	std::cout << position << "号位" << name << "准备阶段\r";
	start = true;
}
void Killer::exeGet() {
	std::cout << position << "号位" << name << "摸牌阶段\r";
	handCards.cont.push_back(manager->topCard());
	handCards.cont.push_back(manager->topCard());
	std::cout << position << "号位" << name << "摸2张牌。" << std::endl;
	get = true;
}
void Killer::exeUse() {
	std::cout << position << "号位" << name << "出牌阶段\r";

	for (unsigned int i = 0; i < handCards.cont.size(); i++) {
		if (cardType(handCards.cont[i]) == CT_EQUIPMENT) {
			switch (handCards.cont[i].cont) {
			case CC_SCRIPT:
			case CC_LOLI:
			case CC_VIRUS:
			case CC_LINE:
			case CC_OFFLINE:
			case CC_BOOM:
			case CC_SPINPEN:
			case CC_PTA:
			case CC_CHICKEN:
			case CC_CHAIRMAN:
			case CC_GUARD:
				if (equipCards.cont[0].cont != CC_NULL)
					manager->dropCard(equipCards.cont[0]);
				equipCards.cont[0] = handCards.cont[i];
				handCards.cont[i] = handCards.cont.back();
				handCards.cont.pop_back();

				std::cout << position << "号位" << name << "装备" <<
					cardName(equipCards.cont[0]) <<  std::endl;
				return;

			case CC_KEYBOARD:
			case CC_FLYING:
			case CC_GLASSES:
			case CC_GTX:
			case CC_DBELEPHANT:
				if (equipCards.cont[1].cont != CC_NULL)
					manager->dropCard(equipCards.cont[1]);
				equipCards.cont[1] = handCards.cont[i];
				handCards.cont[i] = handCards.cont.back();
				handCards.cont.pop_back();

				std::cout << position << "号位" << name << "装备" <<
					cardName(equipCards.cont[1]) << std::endl;
				return;

			case CC_LAKE:
			case CC_MOUNTAIN:
			case CC_BUILDING:
			case CC_FOREST:
				if (equipCards.cont[2].cont != CC_NULL)
					manager->dropCard(equipCards.cont[2]);
				equipCards.cont[2] = handCards.cont[i];
				handCards.cont[i] = handCards.cont.back();
				handCards.cont.pop_back();

				std::cout << position << "号位" << name << "装备" <<
					cardName(equipCards.cont[2]) << std::endl;
				return;

			case CC_MOTOR:
			case CC_BUS:
			case CC_ARM:
				if (equipCards.cont[3].cont != CC_NULL)
					manager->dropCard(equipCards.cont[3]);
				equipCards.cont[3] = handCards.cont[i];
				handCards.cont[i] = handCards.cont.back();
				handCards.cont.pop_back();

				std::cout << position << "号位" << name << "装备" <<
					cardName(equipCards.cont[3]) << std::endl;
				return;

			default:
				break;
			}
		}
	}

	for (unsigned int i = 0; i < handCards.cont.size(); i++) {
		if (cardType(handCards.cont[i]) == CT_ORDINARY) {
			switch (handCards.cont[i].cont) {
			case CC_PREVENT:
			case CC_COMMERCE:
			case CC_PARTY:
				if (role == ROLE_MASTER) {
					for (unsigned int j = 0; j < manager->getPlayer().size(); j++) {
						if (j == position)continue;
						if (manager->getPlayer()[j]->dead == true)continue;
						if (judge.roles[j] == ROLE_INVADER || judge.roles[j] == ROLE_TRAITOR) {
							if (manager->calDist(position, j) <= weaponDist(equipCards.cont[0])) {
								manager->preventEnemy(handCards.cont[i], j);
								handCards.cont[i] = handCards.cont.back();
								handCards.cont.pop_back();

								std::cout << position << "号位" << name << "对" <<
									j << "号位" << manager->getPlayer()[j]->getName() <<
									"：别学了！" << std::endl;
								break;
							}
						}
					}
				}
				if (role == ROLE_INVADER) {
					for (unsigned int j = 0; j < manager->getPlayer().size(); j++) {
						if (j == position)continue;
						if (manager->getPlayer()[j]->dead == true)continue;
						if (judge.roles[j] == ROLE_MASTER || judge.roles[j] == ROLE_MINISTER) {
							if (manager->calDist(position, j) <= weaponDist(equipCards.cont[0])) {
								manager->preventEnemy(handCards.cont[i], j);
								handCards.cont[i] = handCards.cont.back();
								handCards.cont.pop_back();

								std::cout << position << "号位" << name << "对" <<
									j << "号位" << manager->getPlayer()[j]->getName() <<
									"：别学了！" << std::endl;
								break;
							}
						}
					}
				}
				if (role == ROLE_MINISTER) {
					for (unsigned int j = 0; j < manager->getPlayer().size(); j++) {
						if (j == position)continue;
						if (manager->getPlayer()[j]->dead == true)continue;
						if (judge.roles[j] == ROLE_INVADER || judge.roles[j] == ROLE_TRAITOR) {
							if (manager->calDist(position, j) <= weaponDist(equipCards.cont[0])) {
								manager->preventEnemy(handCards.cont[i], j);
								handCards.cont[i] = handCards.cont.back();
								handCards.cont.pop_back();

								std::cout << position << "号位" << name << "对" <<
									j << "号位" << manager->getPlayer()[j]->getName() <<
									"：别学了！" << std::endl;
								break;
							}
						}
					}
				}
				if (role == ROLE_TRAITOR) {
					for (unsigned int j = 0; j < manager->getPlayer().size(); j++) {
						if (j == position)continue;
						if (manager->getPlayer()[j]->dead == true)continue;
						if (judge.roles[j] == ROLE_INVADER || judge.roles[j] == ROLE_MINISTER) {
							if (manager->calDist(position, j) <= weaponDist(equipCards.cont[0])) {
								manager->preventEnemy(handCards.cont[i], j);
								handCards.cont[i] = handCards.cont.back();
								handCards.cont.pop_back();

								std::cout << position << "号位" << name << "对" <<
									j << "号位" << manager->getPlayer()[j]->getName() <<
									"：别学了！" << std::endl;
								break;
							}
						}
					}
				}
				break;
			case CC_DENY:
				break;
			case CC_STUDY:
				if (health < full) {
					incomeGrade();
					manager->dropCard(handCards.cont[i]);
					handCards.cont[i] = handCards.cont.back();
					handCards.cont.pop_back();

					std::cout << position << "号位" << name << "学习。" << std::endl;
					return;
				}
				break;
			case CC_STAYUP:
				break;
			}
			if (!manager->finishSummary())break;
		}
	}

	if(manager->finishSummary())use = true;
}
void Killer::exeDrop() {
	std::cout << position << "号位" << name << "弃牌阶段\r";
	
	std::sort(handCards.cont.begin(), handCards.cont.end(), handLeft);
	while (handCards.cont.size() > health) {
		Card tmp = handCards.cont.back();
		handCards.cont.pop_back();
		manager->dropCard(tmp);
		std::cout << position << "号位" << name << "弃牌 " <<
			cardName(tmp) << "。" << std::endl;
	}

	drop = true;
}
void Killer::exeEnd() {
	std::cout << position << "号位" << name << "结束阶段\r";
	end = true;
}
bool Killer::endStart() {
	if (start) {
		start = false;
		return true;
	}
	else return false;
}
bool Killer::endGet() {
	if (get) {
		get = false;
		return true;
	}
	else return false;
}
bool Killer::endUse() {
	if (use) {
		use = false;
		return true;
	}
	else return false;
}
bool Killer::endDrop() {
	if (drop) {
		drop = false;
		return true;
	}
	else return false;
}
bool Killer::endEnd() {
	if (end) {
		end = false;
		return true;
	}
	else return false;
}

void Killer::hurtGrade(int g) {
	health -= g;

	std::cout << position << "号位" << name << "受到" << 
		g << "点伤害。" << std::endl;
	if (health <= 0) {
		manager->dying = position;
	}
}
void Killer::looseGrade(int g) {
	health -= g;
	std::cout << position << "号位" << name << "受到" <<
		g << "点伤害。" << std::endl;
	if (health <= 0) {
		manager->dying = position;
	}
}
void Killer::incomeGrade() {
	if(health < full)health++;
}
void Killer::increaseFull() {
	full++;
}
bool Killer::askSave(int p) {
	if (p == position) {
		for (unsigned int i = 0; i < handCards.cont.size(); i++) {
			if (handCards.cont[i].cont == CC_STUDY || handCards.cont[i].cont == CC_STAYUP) {
				manager->dropCard(handCards.cont[i]);
				handCards.cont[i] = handCards.cont.back();
				handCards.cont.pop_back();

				std::cout << position << "号位" << name << "：学习！" << std::endl;
				return true;
			}
		}
		return false;
	}

	if (role == ROLE_MASTER) {
		if (judge.roles[p] == ROLE_MINISTER) {
			for (unsigned int i = 0; i < handCards.cont.size(); i++) {
				if (handCards.cont[i].cont == CC_STUDY || handCards.cont[i].cont == CC_STAYUP) {
					manager->dropCard(handCards.cont[i]);
					handCards.cont[i] = handCards.cont.back();
					handCards.cont.pop_back();

					std::cout << position << "号位" << name << "：学习！" << std::endl;
					return true;
				}
			}
			return false;
		}
	}
	if (role == ROLE_MINISTER) {
		if (judge.roles[p] == ROLE_MINISTER || judge.roles[p] == ROLE_MASTER) {
			for (unsigned int i = 0; i < handCards.cont.size(); i++) {
				if (handCards.cont[i].cont == CC_STUDY || handCards.cont[i].cont == CC_STAYUP) {
					manager->dropCard(handCards.cont[i]);
					handCards.cont[i] = handCards.cont.back();
					handCards.cont.pop_back();

					std::cout << position << "号位" << name << "：学习！" << std::endl;
					return true;
				}
			}
			return false;
		}
	}
	if (role == ROLE_INVADER) {
		if (judge.roles[p] == ROLE_INVADER) {
			for (unsigned int i = 0; i < handCards.cont.size(); i++) {
				if (handCards.cont[i].cont == CC_STUDY || handCards.cont[i].cont == CC_STAYUP) {
					manager->dropCard(handCards.cont[i]);
					handCards.cont[i] = handCards.cont.back();
					handCards.cont.pop_back();

					std::cout << position << "号位" << name << "：学习！" << std::endl;
					return true;
				}
			}
			return false;
		}
	}
	if (role == ROLE_TRAITOR) {
		if (judge.roles[p] == ROLE_MASTER) {
			for (unsigned int i = 0; i < handCards.cont.size(); i++) {
				if (handCards.cont[i].cont == CC_STUDY || handCards.cont[i].cont == CC_STAYUP) {
					manager->dropCard(handCards.cont[i]);
					handCards.cont[i] = handCards.cont.back();
					handCards.cont.pop_back();

					std::cout << position << "号位" << name << "：学习！" << std::endl;
					return true;
				}
			}
			return false;
		}
	}
	return false;
}
bool Killer::receivePrevent() {
	for (unsigned int i = 0; i < handCards.cont.size(); i++) {
		if (handCards.cont[i].cont == CC_DENY) {
			manager->dropCard(handCards.cont[i]);
			handCards.cont[i] = handCards.cont.back();
			handCards.cont.pop_back();

			std::cout << position << "号位" << name << "：没学！" << std::endl;
			return true;
		}
	}
	return false;
}

string roleName(ROLE r) {
	switch (r) {
	case ROLE_MASTER:
		return "班长";
	case ROLE_MINISTER:
		return "学霸";
	case ROLE_INVADER:
		return "学渣";
	case ROLE_TRAITOR:
		return "学婊";
	default:
		return "";
	}
}
