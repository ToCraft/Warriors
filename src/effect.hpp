#ifndef EFFECT_H
#define EFFECT_H
#include <string>
#include <exception>
#include <functional>
#include "warrior.hpp"
#include "boss.hpp"

class Effect {
	public:
		Effect(std::function<int(Warrior*, Boss*)> playerDmgF, std::function<int(Warrior*, Boss*)> emenyDmgF);
		
		int damagePlayer(Warrior* player, Boss* enemy);
		int damageEnemy(Warrior* player, Boss* enemy);

	private:
		std::function<int(Warrior*, Boss*)> playerDmg;
		std::function<int(Warrior*, Boss*)> enemyDmg;
};
#endif
