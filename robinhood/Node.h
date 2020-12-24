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
	int h_of_goal;
	int h_of_path;
	std::list<Point> goals;
	int h_cost;
	int f_cost;
};