#pragma once
#include <vector>
#include <algorithm>
#include "ModelObj.h"
#include "AssimpModelLoader.h"
#include "CollisionPlane.h"

using namespace std;

class World
{
public:
	World();
	AssimpModelLoader building;
	vector<CollisionPlane*> planes;
	vector<CollisionPlane*>* getPlanes();
	void init();
	virtual ~World();

protected:

private:
	void setPlanes();
};

