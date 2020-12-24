#pragma once
#include <array>
#include <vector>
#include <list>
#include <iostream>
#include <windows.h>

#include "Node.h"



class CostMap {
public:
	CostMap();
	
	void setGoalPath(std::list<Point> goals); // includes the start point, eg: std::list<>({Point{0,0}, Point{19,19}}
	void addGoal(int x, int y);
	void calculatePath();
	void evalOpen();  // Evaluates the open set
	
	void loadObstacleMap(std::vector<std::vector<std::vector<int>>> map);
	void makeStartNode();
	
	void printNodePath();
	void printObstacleMap(int time_t);
	void printGoalPath();

	void runCmdVisualizer();
	
	std::vector<std::vector<std::vector<int>>> obstacleMap;
	std::list<Node*> open;
	Node* endNode = NULL;

	void clearObstacleMap();
	void insertTestObstacle();

private:
	int x_width = 20;
	int y_width = 20;
	int t_width = 100;

	std::list<Point> goals;  // will try and reach each goal sequentially
	
	std::list<Node*> closed;
	std::list<Node*> path;

	void initObstacleMap();

	std::list<Node*> getNeighbors(Node* node);
	
	void calculateNeighborCosts(Node* node);
	bool inClosedList(Node* node);
	bool inOpenList(Node* node);
	bool inClosedListByComponents(int t, int y, int x);
	//bool inOpenListByComponents(Node* mynode);
	Node* inOpenListByComponents(Node* mynode);
	void backtrackNodePath();
	
};

