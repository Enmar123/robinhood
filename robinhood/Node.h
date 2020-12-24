#pragma once
#include <list>
#include <vector>

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
	void calculateCosts();

	Node* parent;			// The Parent Node
	int x, y, t;			// Current coordinates
	
	int h_of_goal;          // Cost from origin to current coordinates
	int h_of_path;			// Cost of remaining path after next goal
	std::list<Point> goals; // So each node can independently track the goals
	
	int g_cost;				// Cost to reach the current position
	int h_cost;				// Heuristic cost
	int f_cost;				// g_cost + h_cost
};