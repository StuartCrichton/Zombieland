#pragma once
#include "Vector.h"
#include <vector>
#include "SearchCell.h"
class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	void FindPath(Vector currentPos, Vector targetPos);
	Vector nextPathPos(Vector pos);
	void clearOpenList() { openList.clear(); }
	void clearVisitedList() { visitedList.clear(); }
	void clearPathToGoal() { pathToGoal.clear(); }
	bool initializedStart = false;
	bool foundGoal = false;

private:
	void setStartAndGoal(SearchCell start, SearchCell goal);
	void pathOpened(int x, int z, float newCost, SearchCell *parent);
	SearchCell *getNextCell();
	void continuePath();

	SearchCell *startCell;
	SearchCell *endCell;
	std::vector<SearchCell*> openList;
	std::vector<SearchCell*> visitedList;
	std::vector<Vector*> pathToGoal;
};

