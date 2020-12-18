#include <iostream>
#include <windows.h>

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
	while (true) {
		testMapDisplay();
		Sleep(1000); //milliseconds
	}
	system("pause");
	return 0;
}
