#include "CostMap.h"

Node::Node() {
	g_cost = 0;
	h_cost = 0;
	parent = Coord{ 0,0,0 };
}


CostMap::CostMap() {

}

void CostMap::printArray() {
}

void CostMap::setStartEndPoint(int startX, int startY, int endX, int endY) {
	nodeMap[startX, startY, 0].g_cost = 0;
	nodeMap[startX, startY, 0].h_cost = abs(endX - startX) + abs(endY - startY);
	open.push_back( &nodeMap[startX, startY, 0] );
}

// used for sorting nodes by cost
bool CostMap::compareNodeCosts(Node & a, Node & b) {
	if (a.get_f_cost() < b.get_f_cost()) return true;
	if (b.get_f_cost() < a.get_f_cost()) return false;

	// a=b for primary condition, go to secondary
	if (a.h_cost < b.h_cost) return true;
	if (b.h_cost < a.h_cost) return false;

	return false;
}

void CostMap::evaluateOpen() {
	//open.sort([](Node lhs, Node rhs) {return lhs.get_f_cost() < rhs.get_f_cost(); }); // Sort list by f_cost
	open.sort([&](Node lhs, Node rhs) {return compareNodeCosts(lhs, rhs); }); // Sort by f_cost, then h_cost
}

void CostMap::evaluateNeighbors(int x, int y, int t) {
	std::list<Node*> neighbors = getNeighbors(x, y, t);
	for (auto& neighbor : neighbors) {

	}

}

// Returns valid neibours to a coordiante
//
std::list<Node*> CostMap::getNeighbors(int x, int y, int t) {
	std::list<Node*> neighbors;
	std::list<Coord> coords = std::list<Coord>({ Coord{x, y, t + 1}, Coord{x + 1, y, t + 1}, Coord{x - 1, y, t + 1}, Coord{x, y + 1, t + 1}, Coord{x, y - 1, t + 1} });
	
	for (auto& coord : coords) {
		if (coord.t < 100) {
			if (-1 < coord.x < 20 && -1 < coord.y < 20 && obstacleMap[coord.x, coord.y, coord.t] != 1 && !inClosedList(&nodeMap[coord.x, coord.y, coord.t])) {
				neighbors.push_back(&nodeMap[coord.x, coord.y, coord.t]);
			}
		}
	}

	return neighbors;
}

bool CostMap::inClosedList(Node* node_ptr) {
	for (auto& ptr : closed) {
		if (ptr == node_ptr) return true;
	}
	return false;
}