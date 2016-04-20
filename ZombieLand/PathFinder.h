#pragma once
#include <vector>
#include <queue>
#include <string>
#include "Path.h"
#include "TileNode.h"
#include "World.h"

class PathFinder
{
	
public:
	void clearGrid();
	Path findPath(int xStart, int yStart, int xGoal, int yGoal);
	PathFinder();
	PathFinder(World w);
	~PathFinder();
private:
	std::vector<TileNode> closed;
	std::priority_queue<TileNode> open;
	World world;
	TileNode nodes[60][80];

	void removeOpen(TileNode n);
	void removeClosed(TileNode n);
	int hCalculate(int xNeighbour, int yNeighbour, int xGoal, int yGoal);
};

