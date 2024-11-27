#include "effect.hpp"

Effect::Effect(std::function<int(Warrior*, Boss*)> playerDmg, std::function<int(Warrior*, Boss*)> enemyDmg) : playerDmg(playerDmg), enemyDmg(enemyDmg) {}

int Effect::damagePlayer(Warrior* player, Boss* enemy) {
	return playerDmg(player, enemy);
}

int Effect::damageEnemy(Warrior* player, Boss* enemy) {
	return enemyDmg(player, enemy);
}
