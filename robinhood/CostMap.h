#pragma once
#include <array>
#include <list>
#include <iostream>

struct Coord {
	int x;
	int y;
	int t;
};

class Node {
public:
	Node();

	Coord parent;
	int g_cost;
	int h_cost;
	int get_f_cost() {
		return g_cost + h_cost;
	}
};

class CostMap {
public:
	CostMap();
	
	void printArray();
	void setStartEndPoint(int startX, int startY, int endX, int endY);
	void begin();

	void getMove();

private:
	int endX;
	int endY;

	std::array<Node, (20, 20, 100)> nodeMap;
	std::array<int, (20, 20, 100)> obstacleMap;
	std::list<Node*> open;
	std::list<Node*> closed;

	std::list<Node*> getNeighbors(int x, int y, int t);
	void evaluateNeighbors(int x, int y, int t);
	void evaluateOpen();
	bool compareNodeCosts(Node& a, Node& b);
	bool inClosedList(Node* node)
};

