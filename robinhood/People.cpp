#include "People.h"

People::People() {
	x = 0;
	y = 0;
	width = 1;
	height = 1;
	speed = 0;
}

People::People(int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	speed = 0;
}

int People::getX() {
	return x;
}

int People::getY() {
	return y;
}

int People::getWidth() {
	return width;
}

int People::getHeight() {
	return height;
}