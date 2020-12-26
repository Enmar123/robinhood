#include <iostream>
#include <windows.h>
#include <array>
#include <list>
#include <vector>

#include "Map.h"
#include "CostMap.h"
#include "MultiCostMap.h"

int main() {
	// --- You can edit this part ---
	Map sherwood = Map();

	sherwood.setStart(0, 0);		// Default: (0, 0)
	sherwood.setEnd(19, 19);		// Default: (19, 19)

	sherwood.addGuard(5, 0);		// Default: (5, 0)
	sherwood.addArcher(15, 16);		// Default: (15, 16)

	sherwood.addTownsfolk(5, 16);	// Default: (5, 16)
	sherwood.addTownsfolk(8, 10);	// Default: (8, 10)
	sherwood.addTownsfolk(13, 1);	// Default: (13, 1)
	sherwood.addTownsfolk(16, 8);	// Default: (16, 8)
	//sherwood.addTownsfolk(19, 0);   // 
	//sherwood.addTownsfolk(16, 17);  // 
	//sherwood.addTownsfolk(10, 17);  // Calc time using release ~1 sec for 7 townsfolk
	//sherwood.addTownsfolk(0, 19);  // Calc time using release ~10 sec for 8 townsfolk
	
	
	// --- Do not edit this Part ---
	MultiCostMap mcm = MultiCostMap();
	mcm.loadParams(sherwood);
	mcm.runPathfinder();
	sherwood.setRobinPath(mcm.getPath());
	sherwood.runCmdVisualizer();

	system("pause");
	return 0;
}
