#include "warrior.hpp"
#include "boss.hpp"
#include "effect.hpp"
#include <iostream>
#include <string>
#include <regex>
#include <thread>     // For sleep
#include <chrono>     // for seconds
#include <cstdlib>    // For std::rand
#include <algorithm>  // For std::transform
#include <cctype>     // For std::tolower

bool stringsEqual(const std::string& str1, const std::string& str2);

void eraseLines(int count);

int main(int argc, char* argv[]) {
	// use current time as seed for random generator
	std::srand(std::time(nullptr));
	
	// list of possible player characters
    Warrior warriors[] {Warrior("Legolas", 25, 550), Warrior("Gimli", 110, 310), Warrior("Gandalf", 63, 175)};
    
    // list the characters for selection
    std::cout << "Valid warriors are:\n";
	for (Warrior person : warriors) {
		std::cout << "\t" << person.getName() << "\n";
	}
	
	// read args or ask the player to enter a character name
	std::string a;
	if (argc > 1) {
		a = argv[1];
	} else {
		std::cout << "Enter the name of the warrior you want to play as: ";
		std::cin >> a;
	}
	
	// parse character name to "player" var or stop the programm
	bool selected = false;
	Warrior* player = nullptr;
	for (Warrior& person : warriors) {
		if (stringsEqual(person.getName(), a)) {
			player = &person;
			selected = true;
			break;
		}
	}
	
	// erase lines
	eraseLines(6);
	
	if (!selected) {
		std::cout << "\033[0;31mNo valid warrior name supplied!\033[0m\n";
		return 0;
	}
	std::cout << "You selected: \033[38;5;214m" << player->getName() << "\033[0m\n";
	
	// select a boss
	Boss bosses[3] = {
		Boss({"Smaug", "Scatha", "Glaurung"}, 125, 350),		// dragons
		Boss({"Gorathor", "Azhagdur", "Mûrhul"}, 75, 475),		// balrogs
		Boss({"Bolg", "Azog", "Mallorn"}, 35, 375)};			// orcs
	Boss* enemy = &bosses[std::rand() % 3];
	std::string eName = enemy->getName(std::rand() % BOSS_NAMES);
	std::cout << "You will be fighting \033[0;31m" << eName << "\033[0m.\n\n";
	
	// define effects
	// None - literally none
	Effect none = Effect([](Warrior*, Boss*) -> int {return 0;}, [](Warrior*, Boss*) -> int {return 0;});
	
	// Strength - Just more dmage
	bool hasStrength = player->getName() != "Legolas";
	Effect strength = Effect([hasStrength](Warrior*, Boss*) -> int {
			if (!hasStrength) {
				return 25;
			} else {
				return 0;
			}
		}, [hasStrength](Warrior*, Boss*) -> int {
			if (hasStrength) {
				return 25;
			} else {
				return 0;
			}
		});
	
	// Hate - damage if: Enemy Name starts with S or A & player is Gandalf
	bool hateEffect = std::regex_match(eName, std::regex("^(S|A).*"));
	Effect hate = Effect([hateEffect](Warrior* p, Boss*) -> int {
			if (hateEffect && p->getName()[0] == 'G') {
				return 0;
			} else {
				return 25;
			}
		}, [hateEffect](Warrior* p, Boss*) -> int {
			if (hateEffect && p->getName()[0] == 'G') {
				return 75;
			} else {
				return 0;
			}
		});
		
	// Select an effect
	std::cout << "Valid effects are:\n" << "\tNone\n" << "\tStrength\n" << "\tHate\n";
	std::string b;
	if (argc > 2) {
		a = argv[2];
	} else {
		std::cout << "Enter the effect you want to use: ";
		std::cin >> a;
	}
	Effect* effect = nullptr;
	bool hasEffect = false;
	if (stringsEqual(a, "None")) {
		effect = &none;
		hasEffect = true;
	}
	else if (stringsEqual(a, "Strength")) {
		effect = &strength;
		hasEffect = true;
	} else if (stringsEqual(a, "Hate")) {
		effect = &hate;
		hasEffect = true;
	}
	
	// erase lines
	eraseLines(7);
	
	if (!hasEffect) {
		std::cout << "\033[0;31mNo valid effect name supplied!\033[0m\n";
		return 0;
	}
	
	std::cout << "You selected: \033[32m" << a << "\033[0m\n";
	
	// Fighting
	int playerHealth = player->getDefense();
	int enemyHealth = enemy->getDefense();
	int n = 0;
	
	while (playerHealth > 0 && enemyHealth > 0) {
		if (n > 0) {
			eraseLines(5);
		}
		
		// Update Round counter
		n++;
		std::cout << "\nRound " << n << ":\n";
		
		// wait
		std::this_thread::sleep_for(std::chrono::seconds(1));
		
		// calculate health
		playerHealth -= enemy->getAttack() + effect->damagePlayer(player, enemy);
		enemyHealth -= enemy->getAttack() + effect->damageEnemy(player, enemy);
		// output health
		std::cout << player->getName() << "\'s 'Health: " << playerHealth << "\n";
		std::cout << eName << "\'s Health: " << enemyHealth << "\n";
		
		// wait
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	
	if (playerHealth <= 0) {
		if (enemyHealth <= 0) {
			std::cout << "\n\033[91m" << player->getName() << " fought bravely, but " << eName << " killed him while dying.\033[0m\n";
		}
		else {
			std::cout << "\n\033[91m" << player->getName() << " fought bravely, but " << eName << " won.\033[0m\n";
		}
	} else 	if (enemyHealth <= 0) {
		std::cout << "\n\033[32m" << "The people of middle-earth are grateful, that " << player->getName() << " defeated the vast enemy " << eName << ".\033[0m\n";
	}
	
	// end the program
    return 0;
}

// compare two strings case insensitiv
bool stringsEqual(const std::string& str1, const std::string& str2) {
    // Convert both strings to lowercase
    std::string lowerStr1 = str1;
    std::string lowerStr2 = str2;

    std::transform(lowerStr1.begin(), lowerStr1.end(), lowerStr1.begin(), ::tolower);
    std::transform(lowerStr2.begin(), lowerStr2.end(), lowerStr2.begin(), ::tolower);

    // Compare the lowercase versions
    return lowerStr1 == lowerStr2;
}


// Erases `count` lines, including the current line
void eraseLines(int count) {
    if (count > 0) {
        std::cout << "\x1b[2K"; // Delete current line
        // i=1 because we included the first line
        for (int i = 1; i < count; i++) {
            std::cout
            << "\x1b[1A" // Move cursor up one
            << "\x1b[2K"; // Delete the entire line
        }
        std::cout << "\r"; // Resume the cursor at beginning of line
    }
}

