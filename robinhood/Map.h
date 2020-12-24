#pragma once
#include <list>
#include <vector>
#include <iostream>

#include "People.h"
#include "Robin.h"
#include "Guard.h"
#include "Archer.h"
#include "End.h"

class Map {
public:
	Map();

	bool gameIsAlive = true;

	void update();
	void drawCmd();
	void addGuard(int x, int y);
	void addArcher(int x, int y);
	void addRobin(int x, int y);
	void addTownsfolk(int x, int y);
	void addEnd(int x, int y);

	std::vector<std::vector<std::vector<bool>>> getObstacleMap(int time);
private:
	unsigned int x_width;
	unsigned int y_width;
	unsigned int time_step;
	std::list<Robin> robins;
	std::list<Guard> guards;
	std::list<Archer> archers;
	std::list<People> townsfolk;
	std::list<End> ends;
	bool checkEnemyCollision();
	void gameOver();

	template<class T>
	bool objOccupiesXY(int x, int y, T obj) {
		if (x >= obj.getX() &&
			x < obj.getX() + obj.getWidth() &&
			y >= obj.getY() &&
			y < obj.getY() + obj.getHeight()) {
			return true;
		}
		else
			return false;
	}
};

