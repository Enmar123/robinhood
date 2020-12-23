#pragma once
#include <array>
#include <vector>
#include <list>
#include <iostream>
#include <windows.h>

struct Point {
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
	void addSubGoal(int x, int y);
	void calculatePath();
	
	void loadObstacles(std::vector<std::vector<std::vector<int>>> obstalceMap);
	//std::list<Move> getMoves();
	
	void printNodePath();
	void printObstacleMap(int time_t);
	void runCmdVisualizer();

	
	std::vector<std::vector<std::vector<int>>> obstacleMap;
	//std::vector<std::vector<std::vector<Node>>> nodeMap;

	//void clearNodeMap();
	void clearObstacleMap();
	void insertTestObstacle();
private:
	int endX;
	int endY;

	int x_width = 20;
	int y_width = 20;
	int t_width = 100;

	std::list<Point> subGoals;

	std::list<Node*> open;
	std::list<Node*> closed;
	std::list<Node*> path;
	Node* endNode = NULL;

	void initObstacleMap();
	//void initNodeMap();

	std::list<Node*> getNeighbors(Node* node);
	
	void calculateNeighborCosts(Node* node);
	bool inClosedList(Node* node);
	bool inClosedListByComponents(int t, int y, int x);
	bool inOpenList(Node* node);
	void backtrackNodePath();
	
};

