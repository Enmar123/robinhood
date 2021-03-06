#pragma once
#include "costMap.h"
#include "Map.h"


class MultiCostMap {
public:
	MultiCostMap();

	void setStart(int x, int y);
	void setEnd(int x, int y);
	void addSubgoal(int x, int y);
	void loadObstacleMap(std::vector<std::vector<std::vector<bool>>> map);
	void loadParams(Map& map);

	void makeGoalPaths();
	void makeCostMaps();

	std::list<Point> getPath();

	void runPathfinder();
	void runCmdVisualizer();

	

	std::vector<std::vector<std::vector<bool>>> obstacleMap;
	std::list<std::list<Point>> goalPaths;
	std::list<CostMap> costMaps;
	std::list<Point> subGoals;
	CostMap* chosenMap;
	Point start;
	Point end;

private:
	void permute(std::list<Point> str, std::list<Point> out);
};

