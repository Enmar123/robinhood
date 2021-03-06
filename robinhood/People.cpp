#include "People.h"

People::People() {
	x = 0;
	y = 0;
	width = 1;
	height = 1;
	speed = 0;
	symbol = "T";
}

People::People(int x, int y) : People() {
	this->x = x;
	this->y = y;
}

People::People(int x, int y, int w, int h) : People() {
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
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

std::string People::getSymbol() {
	return symbol;
}

void People::update() {
	// do nothing
}

void People::followMoves() {
	if (currentmoves.size() != 0) {
		if (currentmoves.front().steps != 0) {
			x += currentmoves.front().x * speed;
			y += currentmoves.front().y * speed;
			currentmoves.front().steps -= 1;
		}
		else {
			currentmoves.pop_front();
			followMoves();
		}
	}
	else {
		currentmoves = moves;
		followMoves();
	}
}

void People::followSteps() {
	// If steps were provided && If we did not run out of steps
	if (steps.size() != 0 && currentsteps.size() !=  0) {
		x = currentsteps.front().x;
		y = currentsteps.front().y;
		currentsteps.pop_front();
	}
}

void People::setSteps(std::list<Point> points) {
	x = points.front().x;
	y = points.front().y;
	points.pop_front();
	steps = points;
	currentsteps = points;
	loadedSteps = true;
	loadedMoves = false;
}
