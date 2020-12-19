#include <iostream>
#include <windows.h>
#include <array>
#include <list>

#include "Map.h"

void testMapDisplay() {
	std::cout << "--------" << std::endl;
	std::cout << "|R GG  |" << std::endl;
	std::cout << "|  GG  |" << std::endl;
	std::cout << "|      |" << std::endl;
	std::cout << "|      |" << std::endl;
	std::cout << "|    A |" << std::endl;
	std::cout << "|    A |" << std::endl;
	std::cout << "--------" << std::endl;
}

void testArrays() {
	std::array<int, (20, 20)> map1;
	map1.fill(0);
	map1[1, 1] = 1;
	std::cout << "Map.size = " << map1.size() << std::endl;
	std::cout << "Map[0,0] = " << map1[0, 0] << std::endl;
	std::cout << "Map[1,1] = " << map1[1, 1] << std::endl;
	std::cout << "Map[1] = " << map1[1] << std::endl;
}

struct Point {
	int x;
	int y;
};

//bool operator<(Point const &lhs, Point const& rhs) { return lhs.y < rhs.y; }

void testSort() {
	std::cout << "Test Sort" << std::endl;
	std::list<Point> mylist = std::list<Point>({ Point{3,2}, Point{0,1}, Point{0,0}, Point{0,1} });
	for (auto item : mylist) {
		std::cout << item.y << ", ";
	}
	std::cout << std::endl;
	mylist.sort([](Point lhs, Point rhs) {return lhs.y < rhs.y; });
	//mylist.sort();
	for (auto item : mylist) {
		std::cout << item.y << ", ";
	}
	std::cout << std::endl;
}

int main() {
	testArrays();
	testSort();
	std::cout << "Hello World" << std::endl;
	Map mymap = Map();
	mymap.addGuard(5, 0);
	mymap.addArcher(15, 16);
	mymap.addRobin(0, 0);
	mymap.addTownsfolk(5, 16);
	mymap.addTownsfolk(8, 10);
	mymap.addTownsfolk(13, 1);
	mymap.addTownsfolk(16, 8);
	mymap.addEnd(19, 19);

	mymap.drawCmd();
	while (mymap.gameIsAlive) {
		mymap.update();
		mymap.drawCmd();
		Sleep(1000); //milliseconds
	}
	system("pause");
	return 0;
}
