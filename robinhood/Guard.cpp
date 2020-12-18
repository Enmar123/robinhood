#include "Guard.h"

Guard::Guard() : People(0,0,2,2) {
	moves = std::list<Move>({ Move{ 0,1,18 }, Move{ 0,-1,18 } });
	currentmoves = moves;
	speed = 1;
	symbol = "G";
}

Guard::Guard(int x, int y) : People(x, y, 2, 2) {
	moves = std::list<Move>({ Move{ 0,1,18 }, Move{ 0,-1,18 } });
	currentmoves = moves;
	speed = 1;
	symbol = "G";
}

void Guard::update() {
	if (currentmoves.size() != 0 ) {
		if (currentmoves.front().steps != 0) {
			x += currentmoves.front().x * speed;
			y += currentmoves.front().y * speed;
			currentmoves.front().steps -= 1;
		}
		else {
			currentmoves.pop_front();
			update();
		}
	}
	else {
		currentmoves = moves;
		update();
	}
}

