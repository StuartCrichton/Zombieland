#include "World.h"
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <GL/glut.h>
#include <cstdlib>
#include "ModelObj.h"
#include "CollisionPlane.h"
#include "AssimpModelLoader.h"

#include "World.h"
#include <windows.h>
#include <GL/glut.h>
#include <cstdlib>
#include "ModelObj.h"
#include "CollisionPlane.h"
#include "AssimpModelLoader.h"

World::World()
{

}

void World::init() {
	this->building.loadObjFile("../Office.obj");//create the building
	setPlanes();
}

void World::setPlanes() {
	//outer wall 60x80, normal points into world
	planes.push_back(new CollisionPlane(Vector(0,0,-1), Vector(0.5, 7.5, -0.5), 
			Vector(0.5,0,-0.5), Vector(59.5,0,-0.5), Vector(59.5, 7.5,-0.5)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(0.5, 7.5, -0.5),
		Vector(0.5, 0, -0.5), Vector(0.5, 0, -79.5), Vector(0.5, 7.5, -79.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(0.5, 7.5, -79.5),
		Vector(0.5, 0, -79.5), Vector(59.5, 0, -79.5), Vector(59.5, 7.5, -79.5)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(59.5, 7.5, -0.5),
		Vector(59.5, 0, -0.5), Vector(59.5, 0, -79.5), Vector(59.5, 7.5, -79.5)));

	//building outer-rim of wall
	//planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(10.5, 7.5, -10.5),
		//Vector(10.5, 0, -10.5), Vector(49.5, 0, -10.5), Vector(49.5, 7.5, -10.5)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(10.5, 7.5, -10.5),
		Vector(10.5, 0, -10.5), Vector(10.5, 0, -49.5), Vector(10.5, 7.5, -49.5)));
	//planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(10.5, 7.5, -49.5),
		//Vector(10.5, 0, -49.5), Vector(49.5, 0, -49.5), Vector(49.5, 7.5, -49.5)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(49.5, 7.5, -10.5),
		Vector(49.5, 0, -10.5), Vector(49.5, 0, -49.5), Vector(49.5, 7.5, -49.5)));

	//TO-DO building inner-rim, inner walls and edit planes to have doorways
}

vector<CollisionPlane*>* World::getPlanes() {
	return &planes;
}

World::~World()
{
	//dtor
}
