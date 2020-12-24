#include "MultiCostMap.h"

MultiCostMap::MultiCostMap() {
	// no initializer really
}

void MultiCostMap::setStart(int x, int y) {
	start.x = x;
	start.y = y;
}

void MultiCostMap::setEnd(int x, int y) {
	end.x = x;
	end.y = y;
}

void MultiCostMap::addSubgoal(int x, int y) {
	subGoals.push_back(Point{ x,y,0 });
}

void MultiCostMap::makeGoalPaths() {
	std::cout << "Permuting Goal Paths, please wait..." << std::endl;
	goalPaths.clear();
	permute(subGoals, std::list<Point>());
}

void MultiCostMap::loadObstacleMap(std::vector<std::vector<std::vector<bool>>> map) {
	obstacleMap = map;
}

void MultiCostMap::loadParams(Map& map) {
	setStart(map.getRobin().x, map.getRobin().y);
	for (auto& townsperson : map.getTownsfolk()) {
		addSubgoal(townsperson.x, townsperson.y);
	}
	setEnd(map.getEnd().x, map.getEnd().y);
	loadObstacleMap(map.getObstacleMap(map.getMaxTimesteps()));
	makeGoalPaths();
	makeCostMaps();
}

std::list<Point> MultiCostMap::getPath() {
	return chosenMap->getPointPath();
}

void MultiCostMap::permute(std::list<Point> str, std::list<Point> out) {
	// When size of str becomes 0, out has a
	// permutation (length of out is n)
	if (str.size() == 0) {
		out.push_front(start);
		out.push_back(end);
		goalPaths.push_back(out);
		return;
	}

	// One be one move all characters at
	// the beginning of out (or result)
	for (int i = 0; i < str.size(); i++) {
		// Remove first character from str and
		// add it to out
		Point point = str.front();
		std::list<Point> newOut = out;
		str.pop_front();
		newOut.push_back(point);
		permute(str, newOut);

		// Rotate string in a way second character
		// moves to the beginning.
		str.push_back(point);
	}
}

void MultiCostMap::makeCostMaps() {
	std::cout << "Making Costmaps, please wait..." << std::endl;
	costMaps.clear();
	for (auto& goalPath : goalPaths) {
		CostMap costmap = CostMap();
		costmap.loadObstacleMap(obstacleMap);
		costmap.setGoalPath(goalPath);
		costMaps.push_back(costmap);

	}
}

void MultiCostMap::runPathfinder() {
	std::cout << "Finding Path, please wait..." << std::endl;
	costMaps.sort([](CostMap lhs, CostMap rhs) {return lhs.open.front()->f_cost < rhs.open.front()->f_cost; });
	while (true) {
		if (costMaps.front().endNode != NULL) {
			chosenMap = &costMaps.front();
			return;
		}
		costMaps.front().evalOpen();
		costMaps.sort([](CostMap &lhs, CostMap &rhs) {return lhs.open.front()->f_cost < rhs.open.front()->f_cost; });
	}
}

void MultiCostMap::runCmdVisualizer() {
	chosenMap->runCmdVisualizer();
}