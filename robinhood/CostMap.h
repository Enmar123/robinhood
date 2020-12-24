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
	//void setStartPoint(int startX, int startY);
	void addSubGoal(int x, int y);
	void addGoal(int x, int y);
	void calculatePath();
	void evalOpen();
	
	void loadObstacleMap(std::vector<std::vector<std::vector<int>>> map);
	void makeStartNode();
	
	void printNodePath();
	void printObstacleMap(int time_t);
	void printGoalPath();
	void runCmdVisualizer();
	//void makeGoalPaths();

	
	std::vector<std::vector<std::vector<int>>> obstacleMap;
	//std::vector<std::vector<std::vector<Node>>> nodeMap;
	std::list<Node*> open;
	Node* endNode = NULL;

	//void clearNodeMap();
	void clearObstacleMap();
	void insertTestObstacle();
private:
	//int startX, startY;
	//int endX, endY;

	int x_width = 20;
	int y_width = 20;
	int t_width = 200;

	std::list<Point> goals;  // will try and reach each goal sequentially
	std::list<Point> goalsSaved;

	std::list<Point> subGoals;	// list of subgoal points to reach
	std::list<std::list<Point>> goalPaths; // All path permutations to iterate through

	
	std::list<Node*> closed;
	std::list<Node*> path;

	void initObstacleMap();
	//void initNodeMap();

	std::list<Node*> getNeighbors(Node* node);
	
	void calculateNeighborCosts(Node* node);
	bool inClosedList(Node* node);
	bool inOpenList(Node* node);
	bool inClosedListByComponents(int t, int y, int x);
	bool inOpenListByComponents(int t, int y, int x);
	void backtrackNodePath();
	
	//void permute(std::list<Point> subGoals, std::list<Point> goalPath);

	int getHeuristic(int x, int y);
	int getHeuristic2(int x, int y);
	
};

