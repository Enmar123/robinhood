#include "CostMap.h"

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

// inserts a test obstalce into the obstaclemap
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
	this->goals = goals;
	makeStartNode();
}

void CostMap::addGoal(int x, int y) {
	// Ignoring subgoal time, not important for this version.
	goals.push_back(Point{ x,y,0 });
}

// Create starting node and add to open list
void CostMap::makeStartNode() {
	Node* startNode = new Node(goals.front().x, goals.front().y, 0);
	startNode->goals = goals;
	startNode->g_cost = 0;
	startNode->calculateCosts();
	open.push_back(startNode);
}

void CostMap::printGoalPath() {
		for (auto& point : goals) {
			std::cout << "(" << point.x << ", " << point.y << ") ";
		}
		std::cout << std::endl;
	}

// Overloading operator to compare nodes by cost
bool operator<(Node const & lhs, Node const & rhs) {
	if (lhs.h_cost < rhs.f_cost) return true;
	if (rhs.f_cost < lhs.f_cost) return false;

	// a=b for primary condition, go to secondary
	if (lhs.h_cost < rhs.h_cost) return true;
	if (rhs.h_cost < lhs.h_cost) return false;

	return false;
	//return compareNodeCosts(lhs, rhs); 
}

// Run algorithm to calculate path
void CostMap::calculatePath() {
	makeStartNode();
	while (endNode == NULL) {
		if (open.size() == 0) {
			std::cout << "No path To Goal (in specified timeframe)" << std::endl;
			return;
		}
		else {
			std::cout << "Open Set size = " << open.size() << std::endl;
			std::cout << "Closed Set size = " << closed.size() << std::endl;
			evalOpen();
		}
	}
}

// Evaluate the open set of nodes
void CostMap::evalOpen() {
	Node* current;
	current = open.front();
	//std::cout << "Current Pos = (" << current->x << ", " << current->y << ", " << current->t << ")" << std::endl;
	closed.push_back(current);
	open.pop_front();
	// Ending criteria
	if (current->goals.size() == 0) { 
		endNode = current;
		backtrackNodePath();
		std::cout << "End Node Reached" << std::endl;
		return;
	}
	calculateNeighborCosts(current);
	open.sort([](Node* lhs, Node* rhs) {return (lhs->f_cost < rhs->f_cost || (lhs->f_cost == rhs->f_cost && lhs->h_cost < rhs->h_cost)); });
}

// for every neighbor to node, calculate their costs
void CostMap::calculateNeighborCosts(Node* node) {
	std::list<Node*> neighbors = getNeighbors(node);
	for (auto& neighbor : neighbors) {
		neighbor->parent = node;
		neighbor->goals = node->goals;
		neighbor->g_cost = node->g_cost + 1;
		neighbor->calculateCosts();
		// this in open list should bechange to by components i think... let me try befor changing
		Node* existingNode = inOpenListByComponents(neighbor);
		//std::cout << existingNode << std::endl;
		if (existingNode) {
			if (neighbor < existingNode) {
				existingNode = neighbor;
			}
			else {
				// Do nothing
			}
			
		}
		else {
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
	
	for (auto& point : points) {
		if (point.t < t_width) {
			if (0 <= point.x && point.x < x_width && 
				0 <= point.y && point.y < y_width && 
				(obstacleMap[point.t][point.y][point.x] != 1) &&
				!inClosedListByComponents(point.t, point.y, point.x)) {

				neighbors.push_back(new Node(point.x, point.y, point.t));
			}
		}
	}
	//std::cout << "Valid Neighbors = " << neighbors.size() << std::endl;
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

Node* CostMap::inOpenListByComponents(Node* mynode) {
	for (auto& node : open) {
		if (node->x == mynode->x && node->y == mynode->y && node->t == mynode->t)
			return node;
	}
	return NULL;
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
					for (auto& point : goals) {
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
		Sleep(500);
	}
}

void CostMap::loadObstacleMap(std::vector<std::vector<std::vector<bool>>> map) {
	obstacleMap = map;
}

