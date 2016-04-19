#include "PathFinder.h"
#include <stack>
#include <iostream>
using namespace std;

bool operator<(const TileNode & a, const TileNode & b) {
	int f = b.h + b.g;
	int thatf = a.h + a.g;

	return thatf < f;
}

PathFinder::PathFinder()
{
	for (int i = 0; i < 60; i++)
		for (int j = 0; j < 80; j++) {
			obstacles[i][j] = 'o';
		}
}

void PathFinder::clearGrid() {
	for (int i = 0; i < 60; i++)
		for (int j = 0; j < 80; j++)
			nodes[i][j] = TileNode(i, j);
}

Path PathFinder::findPath(int xStart, int yStart, int xGoal, int yGoal) {
	clearGrid();
	std::cout << "Starting search" << endl;
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
		current.status = 'C';
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {

				int xNeighbour = i + current.x;
				int yNeighbour = j + current.y;
				if (i == 0 && j == 0)continue;

				if (obstacles[xNeighbour][yNeighbour] == 'o') {

					int gNew = current.g + 1;
					TileNode neighbour;
					try {
						neighbour = nodes[xNeighbour][yNeighbour];
					}
					catch (exception e) { continue; }

					if (gNew < neighbour.g) {
						if (neighbour.status == 'O') {
							removeOpen(neighbour);
							neighbour.status = 'U';
						}
						if (neighbour.status == 'C') {
							removeClosed(neighbour);
							neighbour.status = 'U';
						}
					}

					if (neighbour.status == 'U') {
						neighbour.g = gNew;
						neighbour.h = hCalculate(xNeighbour, yNeighbour, xGoal, yGoal);
						neighbour.setParent(&current);
						open.push(neighbour);
						neighbour.status = 'O';
					}
				}
			}
		}
	}
	std::cout << "Found Path" << endl << endl;
	if (nodes[xGoal][yGoal].parent == NULL) {
		return Path();
	}

	Path path;
	TileNode nodeToPath = nodes[xGoal][yGoal];
	while (nodeToPath.x != nodes[xStart][yStart].x && nodeToPath.y != nodes[xStart][yStart].y) {
		path.addStep(nodeToPath.x, nodeToPath.y);
		nodeToPath = *nodeToPath.parent;
	}
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