#include "game/Game.h"
#include <iostream>
#include <limits>

int main() {
	try {
		std::cout << "Carcassonne\n\n";
		std::cout << "Number of players (2 - 5): ";

		int playerCount;

		while (true) {
			if (std::cin >> playerCount && playerCount >= 2 && playerCount <= 5) {
				break;
			}
			std::cout << "Incorrect input\n Enter a number from 2 to 5: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		Game game(playerCount);
		game.run();
	}
	catch (const std::exception& e) {
		std::cerr << "\nError! " << e.what() << "\n";
		return 1;
	}

	return 0;
}