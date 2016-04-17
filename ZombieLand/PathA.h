#pragma once
#include <cstdlib>
#include <math.h>

class PathA
{
public:
	PathA();
	void ReadPath(int pathfinderID, int currentX, int currentY, int pixelsPerFrame);
	int ReadPathX(int pathfinderID, int pathLocation);
	int ReadPathY(int pathfinderID, int pathLocation);
	void InitializePathfinder();
	void EndPathfinder();
	int FindPath(int pathfinderID, int startingX, int startingY,
		int targetX, int targetY);
	~PathA();


	const int mapWidth = 80, mapHeight = 60, tileSize = 10, numberPeople = 1;
	int onClosedList = 10;
	const int notfinished = 0, notStarted = 0;// path-related constants
	const int found = 1, nonexistent = 2;
	const int walkable = 0, unwalkable = 1;// walkability array constants
	char walkability[80][60];
	int openList[80 * 60 + 2]; //1 dimensional array holding ID# of open list items
	int whichList[80 + 1][60 + 1];  //2 dimensional array used to record 
									// 		whether a cell is on the open list or on the closed list.
	int openX[80*60 + 2]; //1d array stores the x location of an item on the open list
	int openY[80*60 + 2]; //1d array stores the y location of an item on the open list
	int parentX[80 + 1][60 + 1]; //2d array to store parent of each cell (x)
	int parentY[80 + 1][60 + 1]; //2d array to store parent of each cell (y)
	int Fcost[80*60 + 2];	//1d array to store F cost of a cell on the open list
	int Gcost[80 + 1][60 + 1]; 	//2d array to store G cost for each cell.
	int Hcost[80*60 + 2];	//1d array to store H cost of a cell on the open list
	int pathLength[1 + 1];     //stores length of the found path for critter
	int pathLocation[1 + 1];   //stores current position along the chosen path for critter		
	int* pathBank[1 + 1];
	int pathStatus[1 + 1];
	int xPath[1 + 1];
	int yPath[1 + 1];
};

