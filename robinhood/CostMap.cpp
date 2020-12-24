#include "CostMap.h"

Node::Node() {
	x = 0;
	y = 0;
	t = 0;
	g_cost = 0;
	h_cost = 0;
	f_cost = 0;
	parent = NULL;
}

Node::Node(int x, int y, int t) {
	this->x = x;
	this->y = y;
	this->t = t;
	g_cost = 0;
	h_cost = 0;
	f_cost = 0;
	parent = NULL;
}

void Node::setParams(int x, int y, int t, Node* parent) {
	this->x = x;
	this->y = y;
	this->t = t;
	this->parent = parent;
}


CostMap::CostMap() {
	initObstacleMap();
	clearObstacleMap();
	endNode == NULL;
}

void CostMap::initObstacleMap() {
	obstacleMap.resize(t_width);
	for (auto& arrY : obstacleMap) {
		arrY.resize(y_width);
		for (auto& arrX : arrY) {
			arrX.resize(x_width);
		}
	}
}

void CostMap::clearObstacleMap() {
	for (int t = 0; t < t_width; t++) {
		for (int y = 0; y < y_width; y++) {
			for (int x = 0; x < x_width; x++) {
				obstacleMap[t][y][x] = 0;
			}
		}
	}
}

void CostMap::insertTestObstacle() {
	int x_pos = 3;
	int height = 17;
	for (int t = 0; t < t_width; t++) {
		for (int y = 0; y < height; y++) {
			obstacleMap[t][y][x_pos] = 1;
		}
	}
}

void CostMap::setGoalPath(std::list<Point> goals) {
	goalsSaved = goals;
	this->goals = goals;
	Node* startNode = new Node(goals.front().x, goals.front().y, 0);
	open.push_back(startNode);
	this->goals.pop_front();
}

void CostMap::addSubGoal(int x, int y) {
	// Ignoring subgoal time, not important for this version.
	subGoals.push_back(Point{ x,y,0 });
}

void CostMap::addGoal(int x, int y) {
	// Ignoring subgoal time, not important for this version.
	goalsSaved.push_back(Point{ x,y,0 });
	goals.push_back(Point{ x,y,0 });
	if (goalsSaved.size() == 1) {
		Node* startNode = new Node(goals.front().x, goals.front().y, 0);
		open.push_back(startNode);
		goals.pop_front();
	}
}

void CostMap::printGoalPath() {
		for (auto& point : goalsSaved) {
			std::cout << "(" << point.x << ", " << point.y << ") ";
		}
		std::cout << std::endl;
	}

// used for sorting nodes by cost
bool compareNodeCosts(Node const& a, Node const& b) {

	if (a.h_cost < b.f_cost) return true;
	if (b.f_cost < a.f_cost) return false;

	// a=b for primary condition, go to secondary
	if (a.h_cost < b.h_cost) return true;
	if (b.h_cost < a.h_cost) return false;

	return false;
}

bool operator<(Node const& lhs, Node const& rhs) { return compareNodeCosts(lhs, rhs); }

void CostMap::calculatePath() {
	while (endNode == NULL) {
		if (open.size() == 0) {
			std::cout << "No path To Goal (in specified timeframe)" << std::endl;
			return;
		}
		else {
			evalOpen();
		}
	}
}

void CostMap::evalOpen() {
	Node* current;
	current = open.front();
	std::cout << "Current Pos = (" << current->x << ", " << current->y << ", " << current->t << ")" << std::endl;
	closed.push_back(current);
	open.pop_front();
	if (current->x == goals.front().x && current->y == goals.front().y) { //ending criteria
		if (goals.size() == 1) {
			endNode = current;
			backtrackNodePath();
			std::cout << "End Node Reached" << std::endl;
			return;
		}
		goals.pop_front();
	}
	calculateNeighborCosts(current);
	open.sort([](Node* lhs, Node* rhs) {return (lhs->f_cost < rhs->f_cost || (lhs->f_cost == rhs->f_cost && lhs->h_cost < rhs->h_cost)); });
}

int CostMap::getHeuristic(int x, int y) {
	int currentDist = abs(goals.front().x - x) + abs(goals.front().y - y);
	int remainDist = 0;
	if (goals.size() >= 2) {
		std::vector<Point> goalVec;
		for (auto& goal : goals) {
			goalVec.push_back(goal);
		}
		for (int i = 0 ; i < goalVec.size() - 1; i++) {
			remainDist += abs(goalVec[i+1].x - goalVec[i].x) + abs(goalVec[i + 1].y - goalVec[i].y);
		}
	}
	return currentDist + remainDist;
}

void CostMap::calculateNeighborCosts(Node* node) {
	std::list<Node*> neighbors = getNeighbors(node);
	for (auto& neighbor : neighbors) {
		Node newNode = *neighbor;
		newNode.parent = node;
		newNode.g_cost = node->g_cost + 1;
		newNode.h_cost = getHeuristic(neighbor->x, neighbor->y);
		newNode.f_cost = newNode.g_cost + newNode.h_cost;
		if (inOpenList(neighbor) && *neighbor < newNode ) {
			// do not replace neighbor
		}
		else {
			neighbor->parent = newNode.parent;
			neighbor->g_cost = newNode.g_cost;
			neighbor->h_cost = newNode.h_cost;
			neighbor->f_cost = newNode.f_cost;
			open.push_back(neighbor);
		}
		
	}

}

// Returns valid neibours to a coordiante
std::list<Node*> CostMap::getNeighbors(Node* node) {
	int x = node->x;
	int y = node->y;
	int t = node->t;
	std::list<Node*> neighbors;
	std::list<Point> points = std::list<Point>({ Point{x, y, t + 1},Point{x + 1, y, t + 1}, Point{x - 1, y, t + 1}, Point{x, y + 1, t + 1}, Point{x, y - 1, t + 1} });
	
	//std::cout << "Current points = " << t << ", " << y << ", " << x << std::endl;
	for (auto& point : points) {
		if (point.t < t_width) {
			//std::cout << "Neighbor points = " << point.t << ", " <<  point.y << ", " << point.x << std::endl;
			//std::cout << "Obstacle Map = " << obstacleMap[point.t][point.y][point.x] << std::endl;
			if (0 <= point.x && point.x < x_width && 
				0 <= point.y && point.y < y_width && 
				(obstacleMap[point.t][point.y][point.x] != 1) &&
				!inClosedListByComponents(point.t, point.y, point.x)) {

				neighbors.push_back(new Node(point.x, point.y, point.t));
			}
		}
	}
	std::cout << "Valid Neighbors = " << neighbors.size() << std::endl;
	return neighbors;
}

bool CostMap::inClosedList(Node* node) {
	for (auto& ptr : closed) {
		if (ptr == node) return true;
	}
	return false;
}

bool CostMap::inClosedListByComponents(int t, int y, int x) {
	for (auto& node : closed) {
		if (node->x == x && node->y == y && node->t == t)
			return true;
	}
	return false;
}


bool CostMap::inOpenList(Node* node) {
	for (auto& ptr : open) {
		if (ptr == node) return true;
	}
	return false;
}

void CostMap::backtrackNodePath() {
	if (endNode != NULL) {
		path.push_front(endNode);
		Node* parent = endNode->parent;
		while (parent != NULL) {
			path.push_front(parent);
			parent = parent->parent;     // lol 
		}
	}
}

void CostMap::printNodePath() {
	for (auto& node : path) {
		std::cout << "(" << node->x << ", " << node->y << ", " << node->t << ")" << std::endl;
	}
}

void CostMap::printObstacleMap(int time_t) {
	for (int y = 0 ; y < y_width ; y++) {
		for (int x = 0 ; x < x_width ; x++) {
			std::cout << obstacleMap[time_t][y][x];
		}
		std::cout << std::endl;
	}
}

void CostMap::runCmdVisualizer() {
	for (auto& node : path) {
		std::cout << "                    " << std::endl;
		std::cout << "                    " << std::endl;
		std::cout << "                    " << std::endl;
		for (int y = 0; y < y_width; y++) {
			for (int x = 0; x < x_width; x++){
				while (true) {
					//Prioritize printing robin
					if (y == node->y && x == node->x) {
						std::cout << "R";
						break;
					}

					int i = 0;
					for (auto& point : goalsSaved) {
						if (y == point.y && x == point.x) {
							std::cout << i;
							goto exitPrintLoop;
						}
						i++;
					}

					if (obstacleMap[node->t][y][x] == 1) {
						std::cout << "#";
						break;
					}

					std::cout << ".";
					exitPrintLoop:
					break;
				}
			}
			std::cout << std::endl;
		}
		std::cout << "TimeStep = " << node->t << std::endl;
		Sleep(250);
	}
}

void CostMap::loadObstacleMap(std::vector<std::vector<std::vector<int>>> map) {
	obstacleMap = map;
}

