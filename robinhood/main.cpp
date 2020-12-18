#include <iostream>
#include <windows.h>

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

int main() {
	std::cout << "Hello World" << std::endl;
	Map mymap = Map();
	mymap.addGuard(5, 0);
	mymap.addArcher(15, 16);
	mymap.addRobin(0, 0);
	mymap.addTownsfolk(5, 16);
	mymap.addTownsfolk(8, 10);
	mymap.addTownsfolk(13, 1);
	mymap.addTownsfolk(16, 8);
	mymap.drawCmd();
	while (true) {
		mymap.update();
		mymap.drawCmd();
		Sleep(250); //milliseconds
	}
	system("pause");
	return 0;
}
