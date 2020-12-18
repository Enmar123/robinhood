#include "Guard.h"

Guard::Guard() : People() {
	x = 0;
	y = 0;
	width = 2;
	height = 2;
	speed = 1;
	symbol = "G";

	moves = std::list<Move>({ Move{ 0,1,18 }, Move{ 0,-1,18 } });
	currentmoves = moves;
}

Guard::Guard(int x, int y) : Guard() {
	this->x = x;
	this->y = y;
}

void Guard::update() {
	followMoves();
}
