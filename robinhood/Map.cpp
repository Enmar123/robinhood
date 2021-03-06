#include "Map.h"

void ClearScreen() {
	COORD cursorPosition;	
	cursorPosition.X = 0;	
	cursorPosition.Y = 0;	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput) {
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi)) {
		return cbsi.dwCursorPosition;
	}
	else {
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

void ReturnToPosition(COORD coord) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

Map::Map() {
	x_width = 20;
	y_width = 20;
	time_step = 0;
}

void Map::addGuard(int x, int y) {
	guards.push_back(Guard(x, y));
	starting_guards.push_back(Guard(x, y));

}

void Map::addArcher(int x, int y) {
	archers.push_back(Archer(x, y));
	starting_archers.push_back(Archer(x, y));
}

void Map::setStart(int x, int y) {
	robins.clear();
	robins.push_back(Robin(x, y));
	starting_robins.push_back(Robin(x, y));
}

void Map::addTownsfolk(int x, int y) {
	townsfolk.push_back(People(x, y));
	starting_townsfolk.push_back(People(x, y));
}

void Map::setEnd(int x, int y) {
	ends.clear();
	ends.push_back(End(x, y));
	starting_ends.push_back(End(x, y));
}

void Map::reset() {
	guards = starting_guards;
	archers = starting_archers;
	robins = starting_robins;
	townsfolk = starting_townsfolk;
	ends = starting_ends;
	robinIsAlive = true;
	gameIsAlive = true;
	goalWasReached = false;
	time_step = 0;
}

Robin const& Map::getRobin() {
	return robins.front();
}

std::list<People> Map::getTownsfolk() {
	return townsfolk;
}

End Map::getEnd() {
	return ends.front();
}

void Map::setRobinPath(std::list<Point> points) {
	robins.front().setSteps(points);
}

// Update the positions of each object
void Map::update() {
	if (time_step < time_step_max) {
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
		checkCollisions();
	}
	else {
		gameIsAlive = false;
	}
}

// Draws a single frame of the output to the terminal
void Map::drawCmd() {
	std::cout << std::endl;
	for (int j = 0; j < y_width; j++) {
		for (int i = 0; i < x_width; i++) {
			std::string icon = ".";
			for (auto& const archer : archers) {
				if (objOccupiesXY(i,j,archer)) {
					icon = archer.getSymbol();
					SetConsoleTextAttribute(hConsole, 11); // Cyan
				}
			}
			for (auto& const guard : guards) {
				if (objOccupiesXY(i, j, guard)) {
					icon = guard.getSymbol();
					SetConsoleTextAttribute(hConsole, 11); // Cyan
				}	
			}
			for (auto& const townsperson : townsfolk) {
				if (objOccupiesXY(i, j, townsperson) && townsperson.isAlive) {
					icon = townsperson.getSymbol();
					SetConsoleTextAttribute(hConsole, 14); // Yellow
				}
			}
			for (auto& const end : ends) {
				if (objOccupiesXY(i, j, end)) {
					icon = end.getSymbol();
					SetConsoleTextAttribute(hConsole, 12); // Red
				}
			}
			for (auto& const robin : robins) {
				if (objOccupiesXY(i, j, robin)) {
					icon = robin.getSymbol();
					SetConsoleTextAttribute(hConsole, 10); // Green
				}
			}
			std::cout << icon;
			SetConsoleTextAttribute(hConsole, 7); // Normal Color
		}
		std::cout << std::endl;
	}
	std::cout << "Time Step = " << time_step << std::endl;
	std::cout << "Townsfolk Rescued = " << townsfolkRescued << std::endl;
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
	reset();
	return obstacleMap;
}

void Map::checkCollisions() {
	for (auto& const robin : robins) {
		int x = robin.getX();
		int y = robin.getY();
		for (auto const&  archer : archers) {
			if (objOccupiesXY(x, y, archer)) {
				robinIsAlive = false;
				gameIsAlive = false;
			}
		}
		for (auto const& guard : guards) {
			if (objOccupiesXY(x, y, guard)) {
				robinIsAlive = false;
				gameIsAlive = false;
			}
		}
		for (auto & townsperson: townsfolk) {
			if (objOccupiesXY(x, y, townsperson) && townsperson.isAlive) {
				townsfolkRescued += 1;
				townsperson.isAlive = false;
			}
		}
		for (auto const& end : ends) {
			if (objOccupiesXY(x, y, end)) {
				goalWasReached = true;
				gameIsAlive = false;
			}
		}
	}
}

void Map::gameOver() {
	std::cout << std::endl;
	std::cout << "--------------------------" << std::endl;
	if (robinIsAlive && goalWasReached) {
		std::cout << "Robin Has Saved the day!!!" << std::endl;
	}
	else if (robinIsAlive && !goalWasReached) {
		std::cout << "OH NO! Robin took too long!" << std::endl;
	}
	else {
		std::cout << "OH NO! Robin was Caught!" << std::endl;
	}
	std::cout << "--------------------------" << std::endl;
}

// Run the console-based path visualizer
void Map::runCmdVisualizer() {
	COORD coord = GetConsoleCursorPosition(hConsole);
	drawCmd();
	Sleep(sleepms);
	while (gameIsAlive) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		time_step++;
		update();
		drawCmd();
		Sleep(sleepms); //milliseconds
	}
	gameOver();
}

int Map::getMaxTimesteps() {
	return time_step_max;
}