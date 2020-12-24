#include "Robin.h"

Robin::Robin() : People() {
	x = 0;
	y = 0;
	width = 1;
	height = 1;
	speed = 1;
	symbol = "R";

	moves = std::list<Move>({ Move{ 0,0,1000 } }); // Timeout case
	//moves = std::list<Move>({ Move{ 0,1,19 }, Move{ 1,0,19 },  Move{ 0,0,1000 } }); // moving and gameover
	//moves = std::list<Move>({ Move{ 0,1,19 }, Move{ 1,0,8 }, Move{ 0,0,4 }, Move{ 1,0,11 },  Move{ 0,0,1000 } }); // simple win case
	currentmoves = moves;

}

Robin::Robin(int x, int y) : Robin() {
	this->x = x;
	this->y = y;
}

void Robin::update() {
	if (loadedMoves)
		followMoves();
	else if (loadedSteps)
		followSteps();
}