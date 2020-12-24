#include <iostream>
#include <windows.h>
#include <array>
#include <list>
#include <vector>

#include "Map.h"
#include "CostMap.h"
#include "MultiCostMap.h"

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

struct TestPoint {
	int x;
	int y;
};

//bool operator<(Point const &lhs, Point const& rhs) { return lhs.y < rhs.y; }

void testSort() {
	std::cout << "Test Sort" << std::endl;
	std::list<TestPoint> mylist = std::list<TestPoint>({ TestPoint{3,2}, TestPoint{0,1}, TestPoint{0,0}, TestPoint{0,1} });
	for (auto item : mylist) {
		std::cout << item.y << ", ";
	}
	std::cout << std::endl;
	mylist.sort([](TestPoint lhs, TestPoint rhs) {return lhs.y < rhs.y; });
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
	costmap.addGoal(0, 0);
	costmap.addGoal(19, 19);
	costmap.insertTestObstacle();
	costmap.printObstacleMap(0);
	std::cout << costmap.obstacleMap[0][0][0] << std::endl;
	costmap.calculatePath();
	costmap.printNodePath();
	costmap.runCmdVisualizer();
}

void runCostMap(std::vector<std::vector<std::vector<bool>>> obstacleMap) {
	CostMap costmap = CostMap();
	costmap.loadObstacleMap(obstacleMap);
	costmap.addGoal(0, 0);
	
	//costmap.addGoal(5, 12);
	//costmap.addGoal(8, 10);
	//costmap.addGoal(13, 1);
	//costmap.addGoal(16, 8);

	// Wow This is a tough set of subgoals!!!
	costmap.addGoal(10, 9);
	costmap.addGoal(16, 9);
	costmap.addGoal(13, 1);
	costmap.addGoal(13, 17);
	
	costmap.addGoal(19, 19);
	costmap.printGoalPath();
	costmap.calculatePath();
	costmap.printNodePath();
	costmap.runCmdVisualizer();
	//costmap.printNodePath();
}

void runMultiCostMap(std::vector<std::vector<std::vector<bool>>> obstacleMap) {
	MultiCostMap mcm = MultiCostMap();
	mcm.setStart(0, 0);
	mcm.setEnd(19, 19);
	
	mcm.addSubgoal(5, 12);
	mcm.addSubgoal(8, 10);
	mcm.addSubgoal(13, 1);
	mcm.addSubgoal(16, 8);
	
	mcm.addSubgoal(0, 19);
	mcm.addSubgoal(19, 0);
	
	// Wow This is a tough set of subgoals!!!
	//mcm.addSubgoal(10, 9);
	//mcm.addSubgoal(16, 9);
	//mcm.addSubgoal(13, 1);
	//mcm.addSubgoal(13, 17);
	
	mcm.makeGoalPaths();
	mcm.loadObstacleMap(obstacleMap);
	mcm.makeCostMaps();
	mcm.runPathfinder();
	mcm.runCmdVisualizer();
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

	std::vector<std::vector<std::vector<bool>>> obstacleMap;
	obstacleMap = mymap.getObstacleMap(100);

	//runCostMap(obstacleMap);
	runMultiCostMap(obstacleMap);
	

	//mymap.drawCmd();
	//while (mymap.gameIsAlive) {
	//	mymap.update();
	//	mymap.drawCmd();
	//	Sleep(500); //milliseconds
	//}
	system("pause");
	return 0;
}
