#pragma once
#include <array>
#include <vector>
#include <list>
#include <iostream>
#include <windows.h>

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
	
	void loadObstacles(std::vector<std::vector<std::vector<int>>> obstalceMap);
	//std::list<Move> getMoves();
	
	void printNodePath();
	void printObstacleMap(int time_t);
	void runCmdVisualizer();

	std::vector<std::vector<std::vector<Node>>> nodeMap;
	std::vector<std::vector<std::vector<int>>> obstacleMap;
	//std::array<std::array<std::array<int, 20>, 20>, 20> obstacleMap; // bitmap of obstacles through time (t,y,x)

	void clearNodeMap();
	void clearObstacleMap();
	void insertTestObstacle();
private:
	int endX;
	int endY;

	int x_width = 20;
	int y_width = 20;
	int t_width = 70;

	
	std::list<Node*> open;
	std::list<Node*> closed;
	std::list<Node*> path;
	Node* endNode = NULL;

	void initObstacleMap();
	void initNodeMap();

	std::list<Node*> getNeighbors(Node* node);
	
	void calculateNeighborCosts(Node* node);
	bool inClosedList(Node* node);
	bool inOpenList(Node* node);
	void backtrackNodePath();
	
};

