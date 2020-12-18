#pragma once

struct Move {
	int x = 0;
	int y = 0;
	unsigned int steps = 1;
};

class People {
public:
	People();
	People(int x, int y, int width, int height);

	int getX();
	int getY();
	int getWidth();
	int getHeight();
protected:
	int x,y;
	int width, height;
	int speed;
};

