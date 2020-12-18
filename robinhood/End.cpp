#include "End.h"

End::End() {
	x = 0;
	y = 0;
	width = 1;
	height = 1;
	speed = 0;
	symbol = "E";
}

End::End(int x, int y) : End() {
	this->x = x;
	this->y = y;
}

void End::update() {
	//do nothing
}