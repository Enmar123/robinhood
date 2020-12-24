#pragma once
#include <list>
#include <string>

#include "Node.h"

struct Move {
	int x = 0;
	int y = 0;
	unsigned int steps = 1;
};

class People {
public:
	People();
	People(int x, int y);
	People(int x, int y, int width, int height);

	void update();
	void followMoves();
	void followSteps();

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	std::string getSymbol();

	void setSteps(std::list<Point> points);

	bool isAlive = true;
	int x, y;


protected:
	bool loadedMoves = true;
	bool loadedSteps = false;

	int width, height;
	int speed;
	std::string symbol;

	std::list<Move> moves;			// Move order, displacement based on speed
	std::list<Move> currentmoves;

	std::list<Point> steps;			// Explicit locatios to be at evey timestep
	std::list<Point> currentsteps;
};

