#include "Map.h"

Map::Map() {
	x_width = 20;
	y_width = 20;
	time_step = 0;
}

void Map::update() {
	time_step++;
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

// Draws a single frame of the output to the terminal
void Map::drawCmd() {
	std::cout << "                    " << std::endl;
	std::cout << "                    " << std::endl;
	std::cout << "                    " << std::endl;
	for (int j = 0; j < y_width; j++) {
		for (int i = 0; i < x_width; i++) {
			std::string icon = ".";
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
		std::cout << std::endl;
	}
}

// Retunrs a 3D obstacle map
std::vector<std::vector<std::vector<bool>>> Map::getObstacleMap(int time) {
	// Initialize vector
	std::vector<std::vector<std::vector<bool>>> obstacleMap;
	obstacleMap.resize(time);
	for (auto& arrY : obstacleMap) {
		arrY.resize(y_width);
		for (auto& arrX : arrY) {
			arrX.resize(x_width);
		}
	}
	// Fill vector
	for (int t = 0; t < time; t++) {
		for (int y = 0; y < y_width; y++) {
			for (int x = 0; x < x_width; x++) {
				for (auto& const archer : archers) {
					if (objOccupiesXY(x, y, archer)) {
						obstacleMap[t][y][x] = 1;
						break;
					}
				}
				for (auto& const guard : guards) {
					if (objOccupiesXY(x, y, guard)) {
						obstacleMap[t][y][x] = 1;
						break;
					}
				}
			}
		}
		update();
	}
	return obstacleMap;
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