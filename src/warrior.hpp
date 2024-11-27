#ifndef WARRIOR_H
#define WARRIOR_H
#include <string>

struct Warrior {
	public:
		Warrior(const std::string name, int attack, int defense);
		
		std::string getName();
		
		int getAttack();
		
		int getDefense();
	private:
		const std::string name;
		int attack;
		int defense;
};
#endif
