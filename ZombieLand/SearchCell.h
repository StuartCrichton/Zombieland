#pragma once
#include <math.h>

struct SearchCell {
public:
	int x_coord, z_coord;
	int id;
	SearchCell *parent;
	float G;
	float H;

	SearchCell() : parent(0) {}
	SearchCell(int x, int z, SearchCell *parentA = 0) : 
		x_coord(x), z_coord(z), parent(parentA), id(z * 80 + x), 
		G(0), H(0) {}

	float getF() { return G + H; }
	float ManHattanDistance(SearchCell *nodeEnd) 
	{
		float x = (float)(fabs(this->x_coord - nodeEnd->x_coord));
		float z = (float)(fabs(this->z_coord - nodeEnd->z_coord));
		return x + z;
	}
};