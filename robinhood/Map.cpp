#include "Map.h"

Map::Map() {
	size = 20;
}

void Map::update() {
	for (auto& guard : guards) {
		guard.update();
	}
}

void Map::drawCmd() {
	std::cout << "---------------------" << std::endl;
	for (int j = 0; j < size; j++) {
		if (j < 10)
			std::cout << "0" << j << "|";
		else
			std::cout << j << "|";
		for (int i = 0; i < size; i++) {
			for (auto& const guard : guards) {
				if (i >= guard.getX() &&
					i < guard.getX() + guard.getWidth() &&
					j >= guard.getY() &&
					j < guard.getY() + guard.getHeight()) {
					std::cout << guard.getSymbol();
				}
				else
					std::cout << " ";
			}

		}
		std::cout << std::endl;
	}
	std::cout << "---------------------" << std::endl;
	std::cout << "Guard Pos = " << guards.front().getX() << ", " << guards.front().getY() << std::endl;
}

void Map::addGuard(int x, int y) {
	guards.push_back(Guard(x, y));
}