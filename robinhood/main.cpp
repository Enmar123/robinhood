#include <iostream>
#include <windows.h>
#include <array>
#include <list>
#include <vector>

#include "Map.h"
#include "CostMap.h"

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
	map1[2, 2] = 5;
	std::cout << "Map.size = " << map1.size() << std::endl;
	std::cout << "Map[0,0] = " << map1[0, 0] << std::endl;
	std::cout << "Map[1,1] = " << map1[1, 1] << std::endl;
	std::cout << "Map[1] = " << map1[1] << std::endl;
	std::cout << "Map[2,2] = " << map1[2, 2] << std::endl;
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

bool compareNodeCosts(Node* a, Node* b) {

	if (a->h_cost < b->f_cost) return true;
	if (b->f_cost < a->f_cost) return false;

	// a=b for primary condition, go to secondary
	if (a->h_cost < b->h_cost) return true;
	if (b->h_cost < a->h_cost) return false;

	return false;
}

void testCostMap() {
	std::cout << "Sorting Test" << std::endl;
	Node node1 = Node(); node1.f_cost = 4;
	Node node2 = Node(); node2.f_cost = 2;
	Node node3 = Node(); node3.f_cost = 3;
	std::list<Node*> testlist = std::list<Node*>({ &node1, &node2, &node3 });
	//testlist.sort();
	testlist.sort([](Node * lhs, Node * rhs) {return lhs->f_cost < rhs->f_cost; }); // Sort by f_cost, then h_cost
	for (auto& item : testlist) {
		std::cout << item->f_cost << std::endl;
	}

	std::cout << "CostMap Test" << std::endl;
	CostMap costmap = CostMap();
	costmap.setStartEndPoint(0, 0, 19, 0);
	costmap.insertTestObstacle();
	costmap.printObstacleMap(0);
	std::cout << costmap.obstacleMap[0][0][0] << std::endl;
	costmap.calculatePath();
	costmap.printNodePath();
	costmap.runCmdVisualizer();
}

int main() {
	//std::cout << "Hello World" << std::endl;
	//testArrays();
	//testSort();
	//testCostMap();
	
	Map mymap = Map();
	mymap.addGuard(5, 0);
	mymap.addArcher(15, 16);
	mymap.addRobin(0, 0);
	mymap.addTownsfolk(5, 16);
	mymap.addTownsfolk(8, 10);
	mymap.addTownsfolk(13, 1);
	mymap.addTownsfolk(16, 8);
	mymap.addEnd(19, 19);

	std::vector<std::vector<std::vector<int>>> obstacleMap;
	obstacleMap = mymap.getObstacleMap(70);

	CostMap costmap = CostMap();
	costmap.loadObstacles(obstacleMap);
	costmap.setStartEndPoint(0, 0, 19, 19);
	costmap.calculatePath();
	costmap.printNodePath();
	costmap.runCmdVisualizer();

	//mymap.drawCmd();
	//while (mymap.gameIsAlive) {
	//	mymap.update();
	//	mymap.drawCmd();
	//	Sleep(500); //milliseconds
	//}
	system("pause");
	return 0;
}
