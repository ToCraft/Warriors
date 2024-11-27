#ifndef BOSS_H
#define BOSS_H
#include <string>
#include <array>
#define BOSS_NAMES 3

struct Boss {
	public:
		Boss(const std::array<std::string, BOSS_NAMES>& names, int attack, int defense);
		
		std::string getName(int index);
		
		int getAttack();
		
		int getDefense();
	private:
		const std::array<std::string, BOSS_NAMES>& names;
		int attack;
		int defense;
};
#endif
