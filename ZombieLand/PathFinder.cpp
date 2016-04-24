/*author Dawood Kamdar*/
#include "PathFinder.h"
#include <stack>
#include <iostream>
using namespace std;

bool operator<(const TileNode & a, const TileNode & b) {
	float f = b.h + b.g;
	float thatf = a.h + a.g;

	return f < thatf;
}

PathFinder::PathFinder() {}

PathFinder::PathFinder(World* w)
{
	this->world = w;
}

void PathFinder::clearGrid() {
	for (int i = 0; i < 60; i++)
		for (int j = 0; j < 80; j++)
			nodes[i][j] = TileNode(i, j);
}

Path PathFinder::findPath(int xStart, int yStart, int xGoal, int yGoal) {
	if (world->obstacles[xGoal][yGoal] == 'w')
		return Path();
	clearGrid();
	//std::cout << "Starting search" << endl;
	nodes[xStart][yStart].g = 0;
	closed.clear();
	while (!open.empty())
		open.pop();
	open.push(nodes[xStart][yStart]);

	while (!open.empty()) {
		TileNode current = open.top();
		if (current.x == nodes[xGoal][yGoal].x && current.y == nodes[xGoal][yGoal].y) {
			break;
		}
		TileNode tmp = open.top();
		closed.push_back(tmp);
		open.pop();
		nodes[current.x][current.y].status = 'C';
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {

				int xNeighbour = i + current.x;
				int yNeighbour = j + current.y;
				if (i == 0 && j == 0)continue;

				if (world->obstacles[xNeighbour][yNeighbour] == 'o') {
					float addG = 1;
					if (i != 0 && j != 0)
						addG = 1.414;
					float gNew = current.g + addG;
					TileNode neighbour;
					try {
						neighbour = nodes[xNeighbour][yNeighbour];
					

					if (gNew < nodes[xNeighbour][yNeighbour].g) {
						if (nodes[xNeighbour][yNeighbour].status == 'O') {
							removeOpen(nodes[xNeighbour][yNeighbour]);
							nodes[xNeighbour][yNeighbour].status = 'U';
						}
						if (nodes[xNeighbour][yNeighbour].status == 'C') {
							removeClosed(nodes[xNeighbour][yNeighbour]);
							nodes[xNeighbour][yNeighbour].status = 'U';
						}
					}

					if (nodes[xNeighbour][yNeighbour].status == 'U') {
						nodes[xNeighbour][yNeighbour].g = gNew;
						nodes[xNeighbour][yNeighbour].h = hCalculate(xNeighbour, yNeighbour, xGoal, yGoal);
						nodes[xNeighbour][yNeighbour].setParent(&nodes[current.x][current.y]);
						open.push(nodes[xNeighbour][yNeighbour]);
						nodes[xNeighbour][yNeighbour].status = 'O';
					}
					}
					catch (exception e) { continue; }
				}
			}
		}
	}
	
	if (!nodes[xGoal][yGoal].parent) {
		return Path();
	}

	Path path;
	TileNode *nodeToPath = &nodes[xGoal][yGoal];
	while (nodeToPath->x != xStart || nodeToPath->y != yStart) {
		path.addStep(nodeToPath->x, nodeToPath->y);
		nodeToPath = nodeToPath->parent;
	}
	//std::cout << "Found Path" << endl << endl;
	return path;
}

int PathFinder::hCalculate(int xN, int yN, int xG, int yG) {
	int h = 0;
	int dx = abs(xN - xG);
	int dy = abs(yN - yG);
	h = dx + dy;
	return h;
}

PathFinder::~PathFinder()
{
}

void PathFinder::removeOpen(TileNode n) {
	stack<TileNode> myStack;
	while (!open.empty()) {
		TileNode tmp = open.top();
		if (n.x == tmp.x && n.y == tmp.y) {
			open.pop();
			break;
		}
		else {
			myStack.push(tmp);
			open.pop();
		}
	}
	while (!myStack.empty()) {
		TileNode tmp = myStack.top();
		open.push(tmp);
		myStack.pop();
	}
}

void PathFinder::removeClosed(TileNode n) {
	for (int i = 0; i < closed.size(); i++) {
		TileNode tmp = closed[i];
		if (n.x == tmp.x && n.y == tmp.y) {
			closed.erase(closed.begin() + i);
			return;
		}
	}
}