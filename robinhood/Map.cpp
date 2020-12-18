#include "Map.h"

Map::Map() {
	size = 20;
}

void Map::update() {
	for (auto& guard : guards) {
		guard.update();
	}
	for (auto& archer : archers) {
		archer.update();
	}
}

void Map::drawCmd() {
	std::cout <<"   " << "--------------------" << std::endl;
	for (int j = 0; j < size; j++) {
		if (j < 10)
			std::cout << "0" << j << "|";
		else
			std::cout << j << "|";
		for (int i = 0; i < size; i++) {
			std::string icon = " ";
			for (auto& const guard : guards) {
				if (i >= guard.getX() &&
					i < guard.getX() + guard.getWidth() &&
					j >= guard.getY() &&
					j < guard.getY() + guard.getHeight()) {
					icon = guard.getSymbol();
				}	
			}
			for (auto& const archer : archers) {
				if (i >= archer.getX() &&
					i < archer.getX() + archer.getWidth() &&
					j >= archer.getY() &&
					j < archer.getY() + archer.getHeight()) {
					icon = archer.getSymbol();
				}
			}
			std::cout << icon;
		}
		std::cout << std::endl;
	}
	std::cout << "   " << "--------------------" << std::endl;
	std::cout << "Guard Pos =  " << guards.front().getX() << ", " << guards.front().getY() << std::endl;
	std::cout << "Archer Pos = " << archers.front().getX() << ", " << archers.front().getY() << std::endl;
}

void Map::addGuard(int x, int y) {
	guards.push_back(Guard(x, y));
}

void Map::addArcher(int x, int y) {
	archers.push_back(Archer(x, y));
}