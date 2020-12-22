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
	obstacleMap.fill(0);
	resetNodeMap();
}

void CostMap::resetNodeMap() {
	for (int x = 0; x < 20; x++) {
		for (int y = 0; y < 20; y++) {
			for (int t = 0; t < 20; t++) {
				//nodeMap[x, y, t].setParams(x, y, t, NULL);
				nodeMap[x][y][t].setParams(x, y, t, NULL);
			}
		}
	}
}

void CostMap::setStartEndPoint(int startX, int startY, int endX, int endY) {
	//Node* startNode = &nodeMap[startX, startY, 0];
	Node* startNode = &nodeMap[startX][startY][0];
	startNode->g_cost = 0;
	startNode->h_cost = abs(endX - startX) + abs(endY - startY);
	startNode->f_cost = startNode->g_cost + startNode->h_cost;
	open.push_back( startNode );
	this->endX = endX;
	this->endY = endY;
	//std::cout << "StartNode = (" << startNode->x << ", " << startNode->y << ")" << std::endl;
	std::cout << "Start = (" << startX << ", " << startY << ")" << std::endl;
	std::cout << "End   = (" << this->endX << ", " << this->endY << ")" << std::endl;
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
	//open.sort([](Node lhs, Node rhs) {return lhs.h_cost < rhs.h_cost; }); // Sort list by f_cost
	//open.sort([&](Node lhs, Node rhs) {return compareNodeCosts(lhs, rhs); }); // Sort by f_cost, then h_cost
	
	Node* current;
	while (true) {
		std::cout << "Len Open =" << open.size() << std::endl;
		open.sort([](Node* lhs, Node* rhs) {return (lhs->f_cost < rhs->f_cost || (lhs->f_cost == rhs->f_cost && lhs->h_cost < rhs->h_cost));});
		current = open.front();
		std::cout << "Current Pos = (" << current->x << ", " << current->y << ", " << current->t << ")" << std::endl;
		closed.push_back(current);
		open.pop_front();
		if (current->x == endX && current->y == endY) { //ending criteria
			endNode = current;
			std::cout << "End Node Reached" << std::endl;
			return;
		}
		calculateNeighborCosts(current);
		
	}
}

void CostMap::calculateNeighborCosts(Node* node) {
	std::list<Node*> neighbors = getNeighbors(node->x, node->y, node->t);
	for (auto& neighbor : neighbors) {
		Node newNode = *neighbor;
		newNode.parent = node;
		newNode.g_cost = node->g_cost + 1;
		newNode.h_cost = abs(endX - neighbor->x) + abs(endY - neighbor->y);
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
std::list<Node*> CostMap::getNeighbors(int x, int y, int t) {
	std::list<Node*> neighbors;
	std::list<Coord> coords = std::list<Coord>({ Coord{x, y, t + 1}, Coord{x + 1, y, t + 1}, Coord{x - 1, y, t + 1}, Coord{x, y + 1, t + 1}, Coord{x, y - 1, t + 1} });
	
	for (auto& coord : coords) {
		if (coord.t < t_width) {
			if (0 <= coord.x < x_width && 0 <= coord.y < y_width && obstacleMap[coord.x, coord.y, coord.t] != 1 && !inClosedList(&nodeMap[coord.x][coord.y][coord.t])) {
				//neighbors.push_back(&nodeMap[coord.x, coord.y, coord.t]);
				neighbors.push_back(&nodeMap[coord.x][coord.y][coord.t]);
			}
		}
	}

	return neighbors;
}

bool CostMap::inClosedList(Node* node) {
	for (auto& ptr : closed) {
		if (ptr == node) return true;
	}
	return false;
}

bool CostMap::inOpenList(Node* node) {
	for (auto& ptr : open) {
		if (ptr == node) return true;
	}
	return false;
}