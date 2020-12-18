#include "Robin.h"

Robin::Robin() : People() {
	speed = 1;
	symbol = "R";
}

Robin::Robin(int x, int y) : People(x,y) {
	speed = 1;
	symbol = "R";
}

void Robin::update() {
	x += 1;
}