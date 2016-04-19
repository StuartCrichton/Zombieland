#include "PathFinding.h"



PathFinding::PathFinding()
{
}

void PathFinding::FindPath(Vector current, Vector target) {
	if (!initializedStart) {
		for (int i = 0; i < openList.size(); i++) 
			delete openList[i];
		
		openList.clear();
	

	for (int i = 0; i < visitedList.size(); i++) 
		delete visitedList[i];
	
	visitedList.clear();
	for (int i = 0; i < pathToGoal.size(); i++)
		delete pathToGoal[i];
	pathToGoal.clear();

	SearchCell start;
	start.x_coord = current.getX();
	start.z_coord = current.getZ();

	SearchCell goal;
	goal.x_coord = round(target.getX());
	goal.z_coord = -round(target.getZ());

	setStartAndGoal(start, goal);
	initializedStart = true;
	}
	if (initializedStart) {
		continuePath();
	}
}

void PathFinding::setStartAndGoal(SearchCell start, SearchCell goal) {
	startCell = new SearchCell(start.x_coord, start.z_coord, NULL);
	endCell = new SearchCell(goal.x_coord, goal.z_coord, &goal);

	startCell->G = 0;
	startCell->H = startCell->ManHattanDistance(endCell);
	startCell->parent = 0;

	openList.push_back(startCell);
}

SearchCell* PathFinding::getNextCell() {
	float bestF = 99999.0f;
	int cellIndex = -1;
	SearchCell* nextCell = NULL;
	
	for (int i = 0; i < openList.size(); i++) {
		if (openList[i]->getF() < bestF) {
			bestF = openList[i]->getF();
			cellIndex = i;
		}
	}

	if (cellIndex >= 0) {
		nextCell = openList[cellIndex];
		visitedList.push_back(nextCell);
		openList.erase(openList.begin() + cellIndex);
	}

	return nextCell;
}

void PathFinding::pathOpened(int x, int z, float newCost, SearchCell *parent) {
	/*if (CELL_BLOCKED) {
		return;
	}*/
	int id = z * 80 + x;
	for (int i = 0; i < visitedList.size(); i++) {
		if (id == visitedList[i]->id) {
			return;
		}
	}

	SearchCell* newChild = new SearchCell(x, z, parent);
	newChild->G = newCost;
	newChild->H = parent->ManHattanDistance(endCell);

	for (int i = 0; i < openList.size(); i++) {
		if (id == openList[i]->id) {
			float newF = newChild->G + newCost + openList[i]->H;
			if (openList[i]->getF() > newF) {
				openList[i]->G = newChild->G + newCost;
				openList[i]->parent = newChild;
			}
			else {
				delete newChild;
				return;
			}
		}
	}

	openList.push_back(newChild);
}

void PathFinding::continuePath() {
	if (openList.empty()) return;
	SearchCell* currentCell = getNextCell();
	if (currentCell->id == endCell->id) {
		endCell->parent = currentCell->parent;

		SearchCell* getPath;
		for (getPath = endCell; getPath != NULL; getPath = getPath->parent) {
			pathToGoal.push_back(new Vector(getPath->x_coord, 1, getPath->z_coord));
		}

		foundGoal = true;
		return;
	}
	else {
		pathOpened(currentCell->x_coord + 1, currentCell->z_coord, currentCell->G + 1, currentCell);
		pathOpened(currentCell->x_coord - 1, currentCell->z_coord, currentCell->G + 1, currentCell);
		pathOpened(currentCell->x_coord, currentCell->z_coord + 1, currentCell->G + 1, currentCell);
		pathOpened(currentCell->x_coord, currentCell->z_coord - 1, currentCell->G + 1, currentCell);

		pathOpened(currentCell->x_coord + 1, currentCell->z_coord + 1, currentCell->G + 1.414, currentCell);
		pathOpened(currentCell->x_coord + 1, currentCell->z_coord - 1, currentCell->G + 1.414, currentCell);
		pathOpened(currentCell->x_coord - 1, currentCell->z_coord + 1, currentCell->G + 1.414, currentCell);
		pathOpened(currentCell->x_coord - 1, currentCell->z_coord - 1, currentCell->G + 1.414, currentCell);

		for (int i = 0; i < openList.size(); i++) {
			if (currentCell->id == openList[i]->id) {
				openList.erase(openList.begin() + i);
			}
		}
	}
}

Vector PathFinding::nextPathPos(Vector pos) {
	int index = 1;
	Vector nextPos = Vector(pathToGoal[pathToGoal.size() - index]->getX(), 1,
		pathToGoal[pathToGoal.size() - index]->getZ());

	if (index < pathToGoal.size()) {
		if (nextPos.getDistance(pos) < 0.5) {
			pathToGoal.erase(pathToGoal.end() - index);
		}
	}
	return nextPos;
}

PathFinding::~PathFinding()
{
}
