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
	// Customizable, try and keep Townsfolk count under 5
	Map sherwood = Map();
	sherwood.addGuard(5, 0);		// Default: (5, 0)
	sherwood.addArcher(15, 16);		// Default: (15, 16)
	sherwood.addRobin(19, 19);		// Default: (0, 0)
	sherwood.addTownsfolk(0, 0);	// Default: (5, 16)
	sherwood.addTownsfolk(16, 9);	// Default: (8, 10)
	sherwood.addTownsfolk(13, 1);	// Default: (13, 1)
	sherwood.addTownsfolk(13, 17);	// Default: (16, 8)
	//sherwood.addTownsfolk(19, 0);   // 
	//sherwood.addTownsfolk(16, 17);  // 
	//sherwood.addTownsfolk(10, 17);  // Calc time using release ~2 sec
	//sherwood.addTownsfolk(16, 3);  // Calc time using release ~20 sec 
	sherwood.addEnd(19, 19);		// Default: (19, 19)
	
	// --- Do not edit this Part ---
	MultiCostMap mcm = MultiCostMap();
	mcm.loadParams(sherwood);
	mcm.runPathfinder();
	sherwood.setRobinPath(mcm.getPath());
	sherwood.runCmdVisualizer();

	system("pause");
	return 0;
}
