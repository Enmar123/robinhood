#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <Windows.h>

#include "People.h"
#include "Robin.h"
#include "Guard.h"
#include "Archer.h"
#include "End.h"

class Map {
public:
	Map();

	bool gameIsAlive = true;
	bool robinIsAlive = true;
	bool goalWasReached = false;

	void addGuard(int x, int y);
	void addArcher(int x, int y);
	void addRobin(int x, int y);
	void addTownsfolk(int x, int y);
	void addEnd(int x, int y);

	Robin const& getRobin();
	std::list<People> getTownsfolk();
	End getEnd();
	int getMaxTimesteps();
	void setRobinPath(std::list<Point> points);

	void update();
	void drawCmd();
	void runCmdVisualizer();
	void reset();

	std::vector<std::vector<std::vector<bool>>> getObstacleMap(int time);

private:
	int townsfolkRescued = 0;
	int sleepms = 250;
	int x_width;
	int y_width;
	int time_step;
	int time_step_max = 100;

	std::list<Robin> starting_robins;
	std::list<Guard> starting_guards;
	std::list<Archer> starting_archers;
	std::list<People> starting_townsfolk;
	std::list<End> starting_ends;

	std::list<Robin> robins;
	std::list<Guard> guards;
	std::list<Archer> archers;
	std::list<People> townsfolk;
	std::list<End> ends;
	void gameOver();
	void checkCollisions();

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

