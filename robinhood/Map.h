#pragma once
#include <list>
#include <iostream>

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
private:
	unsigned int size;
	//std::list<Robin> robins;
	std::list<Guard> guards;
	std::list<Archer> archers;
	//std::list<Townsfolk> townsfolk;
	//std::list<End> end;
	//void checkCollision();
	//void gameOver();
};

