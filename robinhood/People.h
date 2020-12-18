#pragma once
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

