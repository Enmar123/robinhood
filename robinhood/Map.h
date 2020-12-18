#pragma once
#include <list>
#include <iostream>

#include "People.h"
#include "Robin.h"
#include "Guard.h"
#include "Archer.h"

class Map {
public:
	Map();
	void update();
	void drawCmd();
	void addGuard(int x, int y);
	void addArcher(int x, int y);
	void addRobin(int x, int y);
	void addTownsfolk(int x, int y);
private:
	unsigned int size;
	std::list<Robin> robins;
	std::list<Guard> guards;
	std::list<Archer> archers;
	std::list<People> townsfolk;
	//std::list<End> end;
	//void checkCollision();
	//void gameOver();

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

