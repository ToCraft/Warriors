#include "boss.hpp"

Boss::Boss(const std::array<std::string, BOSS_NAMES>& names, int attack, int defense): names(names), attack(attack), defense(defense) {}

int Boss::getAttack() {
	return attack;
}

int Boss::getDefense() {
	return defense;
}

std::string Boss::getName(int index) {
	if (index >= 0 && index < BOSS_NAMES) {
		return Boss::names[index];
	} else {
		return "";
	}
}
