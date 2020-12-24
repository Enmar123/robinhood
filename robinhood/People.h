#pragma once

#include<list>
#include <string>

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

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	std::string getSymbol();

	bool isAlive = true;

protected:
	
	int x,y;
	int width, height;
	int speed;
	std::string symbol;

	std::list<Move> moves;
	std::list<Move> currentmoves;
};

