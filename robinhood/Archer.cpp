#include "Archer.h"

Archer::Archer() {
	x = 0;
	y = 0;
	width = 3;
	height = 4;
	speed = 2;
	symbol = "A";
	moves = std::list<Move>({ Move{ -1,0,3 }, Move{ 0,-1, 4 }, Move{ 1,0,3 }, Move{ 0,-1, 4 },
							  Move{ -1,0,3 }, Move{ 0, 1, 4 }, Move{ 1,0,3 }, Move{ 0, 1, 4 } });
	currentmoves = moves;
}

Archer::Archer(int x, int y) : Archer() {
	this->x = x;
	this->y = y;
}