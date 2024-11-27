#include "warrior.hpp"

Warrior::Warrior(const std::string name, int attack, int defense): name(name), attack(attack), defense(defense) {}

int Warrior::getAttack() {
	return attack;
}

int Warrior::getDefense() {
	return defense;
}

std::string Warrior::getName() {
	return name;
}
