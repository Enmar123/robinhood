#include "Map.h"

Map::Map() {
	size = 20;
}

void Map::update() {
	for (auto& archer : archers) {
		archer.update();
	}
	for (auto& guard : guards) {
		guard.update();
	}
	for (auto& people : townsfolk) {
		people.update();
	}
	for (auto& end : ends) {
		end.update();
	}
	for (auto& robin : robins) {
		robin.update();
	}
	if (checkEnemyCollision())
		gameOver();
}

void Map::drawCmd() {
	std::cout << "   " << "--------------------" << std::endl;
	std::cout << "   " << "01234567890123456789" << std::endl;
	std::cout << "   " << "--------------------" << std::endl;
	for (int j = 0; j < size; j++) {
		if (j < 10)
			std::cout << "0" << j << "|";
		else
			std::cout << j << "|";
		for (int i = 0; i < size; i++) {
			std::string icon = " ";
			for (auto& const archer : archers) {
				if (objOccupiesXY(i,j,archer)) {
					icon = archer.getSymbol();
				}
			}
			for (auto& const guard : guards) {
				if (objOccupiesXY(i, j, guard)) {
					icon = guard.getSymbol();
				}	
			}
			for (auto& const person : townsfolk) {
				if (objOccupiesXY(i, j, person)) {
					icon = person.getSymbol();
				}
			}
			for (auto& const end : ends) {
				if (objOccupiesXY(i, j, end)) {
					icon = end.getSymbol();
				}
			}
			for (auto& const robin : robins) {
				if (objOccupiesXY(i, j, robin)) {
					icon = robin.getSymbol();
				}
			}
			std::cout << icon;
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "   " << "--------------------" << std::endl;
	std::cout << "   " << "01234567890123456789" << std::endl;
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

void Map::addRobin(int x, int y) {
	robins.push_back(Robin(x, y));
}

void Map::addTownsfolk(int x, int y) {
	townsfolk.push_back(People(x, y));
}

void Map::addEnd(int x, int y) {
	ends.push_back(End(x, y));
}

bool Map::checkEnemyCollision() {
	for (auto& const robin : robins) {
		int x = robin.getX();
		int y = robin.getY();
		for (auto& const archer : archers) {
			if (objOccupiesXY(x, y, archer)) {
				return true;
			}
		}
		for (auto& const guard : guards) {
			if (objOccupiesXY(x, y, guard)) {
				return true;
			}
		}
	}
	return false;
}

void Map::gameOver() {
	gameIsAlive = false;
	std::cout << "GAME OVER" << std::endl;
}