#pragma once
#include <vector>
#include <algorithm>
#include "AssimpModelLoader.h"
#include "CollisionPlane.h"

using namespace std;

class World
{
public:
	World();
	AssimpModelLoader building;
	AssimpModelLoader ammoBox;
	AssimpModelLoader gun;
	vector<CollisionPlane*> planes;
	vector<CollisionPlane*>* getPlanes();
	char obstacles[3][60][80];//ground
	char obstacles1[60][80];//first floor
	char obstacles2[60][80];//roof
	void init();
	virtual ~World();

protected:

private:
	void setObstacles();
	void setPlanes();
	CollisionPlane* setPlane(float xNormal, float start, float end, float bottom, float top, float constant);
};

