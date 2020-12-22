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
	Node(int x, int y, int t);

	void setParams(int x, int y, int t, Node* parent);

	Node* parent;
	int x, y, t;
	int g_cost;
	int h_cost;
	int f_cost;
};

class CostMap {
public:
	CostMap();
	
	void setStartEndPoint(int startX, int startY, int endX, int endY);
	void calculatePath();
	
	//std::list<Move> getMoves();
	//std::list<Node> getNodePath();


	Node nodeMap[20][20][20];
	//std::array<Node, (20, 20, 100)> nodeMap;
private:
	int endX;
	int endY;

	int x_width = 20;
	int y_width = 20;
	int t_width = 20;

	std::array<int, (0, 20, 100)> obstacleMap;
	std::list<Node*> open;
	std::list<Node*> closed;
	Node* endNode = NULL;

	std::list<Node*> getNeighbors(int x, int y, int t);
	
	void calculateNeighborCosts(Node* node);
	bool inClosedList(Node* node);
	bool inOpenList(Node* node);
	void resetNodeMap();
};

