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

	Node* parent;
	int x, y, t;
	int g_cost;
	int h_of_goal;          // Cost from current location to next goal
	int h_of_path;			// Cost of remaining path after next goal
	std::list<Point> goals; // So each node can independently track the goals
	int h_cost;
	int f_cost;
};