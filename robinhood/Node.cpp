#include "Node.h"

Node::Node() {
	x = 0;
	y = 0;
	t = 0;
	g_cost = 0;
	h_of_goal = 0;
	h_of_path = 0;
	h_cost = 0;
	f_cost = 0;
	parent = NULL;
}

Node::Node(int x, int y, int t) {
	this->x = x;
	this->y = y;
	this->t = t;
	g_cost = 0;
	h_of_goal = 0;
	h_of_path = 0;
	h_cost = 0;
	f_cost = 0;
	parent = NULL;
}

// Will calc remaining costs if parent node, g_cost, goals, and xyt is available
void Node::calculateCosts() {
	// Calculate the heuristic
	h_of_goal = abs(goals.front().x - x) + abs(goals.front().y - y);
	if (x == goals.front().x && y == goals.front().y) {
		goals.pop_front();
		if (goals.size() >= 2) {
			std::vector<Point> goalVec;
			for (auto& goal : goals) {
				goalVec.push_back(goal);
			}
			for (int i = 0; i < goalVec.size() - 1; i++) {
				h_of_path += abs(goalVec[i + 1].x - goalVec[i].x) + abs(goalVec[i + 1].y - goalVec[i].y);
			}
		}
	}
	else {
		h_of_path = parent->h_of_path;
	}
	h_cost = h_of_goal + h_of_path;
	f_cost = g_cost + h_cost;
}

void Node::setParams(int x, int y, int t, Node* parent) {
	this->x = x;
	this->y = y;
	this->t = t;
	this->parent = parent;
}