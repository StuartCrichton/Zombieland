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
	this->ammoBox.loadObjFile("../AmmoBox.obj");//create the ammo box
	setPlanes();
}

void World::setPlanes() {
	//outer wall 60x80, normal points into world
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(0.5, 7.5, -0.5),
		Vector(0.5, 0, -0.5), Vector(59.5, 0, -0.5), Vector(59.5, 7.5, -0.5)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(0.5, 7.5, -0.5),
		Vector(0.5, 0, -0.5), Vector(0.5, 0, -79.5), Vector(0.5, 7.5, -79.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(0.5, 7.5, -79.5),
		Vector(0.5, 0, -79.5), Vector(59.5, 0, -79.5), Vector(59.5, 7.5, -79.5)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(59.5, 7.5, -0.5),
		Vector(59.5, 0, -0.5), Vector(59.5, 0, -79.5), Vector(59.5, 7.5, -79.5)));

	//building outer-rim of wall
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(10.5, 8.5, -10.5),
		Vector(10.5, 0, -10.5), Vector(29, 0, -10.5), Vector(29, 8.5, -10.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(31, 8.5, -10.5),
		Vector(31, 0, -10.5), Vector(49.5, 0, -10.5), Vector(49.5, 8.5, -10.5)));

	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(10.5, 8.5, -10.5),
		Vector(10.5, 0, -10.5), Vector(10.5, 0, -49.5), Vector(10.5, 8.5, -49.5)));

	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(10.5, 8.5, -49.5),
		Vector(10.5, 0, -49.5), Vector(17, 0, -49.5), Vector(17, 8.5, -49.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(19, 8.5, -49.5),
		Vector(19, 0, -49.5), Vector(29, 0, -49.5), Vector(29, 8.5, -49.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(31, 8.5, -49.5),
		Vector(31, 0, -49.5), Vector(49.5, 0, -49.5), Vector(49.5, 8.5, -49.5)));

	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(49.5, 8.5, -10.5),
		Vector(49.5, 0, -10.5), Vector(49.5, 0, -49.5), Vector(49.5, 8.5, -49.5)));

	//building inner-rim of wall
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(11, 8.5, -11),
		Vector(11, 0, -11), Vector(29, 0, -11), Vector(29, 8.5, -11)));
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(31, 8.5, -11),
		Vector(31, 0, -11), Vector(49, 0, -11), Vector(49, 8.5, -11)));

	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(11, 8.5, -11),
		Vector(11, 0, -11), Vector(11, 0, -49), Vector(11, 8.5, -49)));

	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(11, 8.5, -49),
		Vector(11, 0, -49), Vector(17, 0, -49), Vector(17, 8.5, -49)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(19, 8.5, -49),
		Vector(19, 0, -49), Vector(29, 0, -49), Vector(29, 8.5, -49)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(31, 8.5, -49),
		Vector(31, 0, -49), Vector(49, 0, -49), Vector(49, 8.5, -49)));

	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(49, 8.5, -11),
		Vector(49, 0, -11), Vector(49, 0, -49), Vector(49, 8.5, -49)));

	//doorway side walls
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(29, 8.5, -11),
		Vector(29, 0, -11), Vector(29, 0, -10.5), Vector(29, 3.5, -10.5)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(31, 8.5, -11),
		Vector(31, 0, -11), Vector(31, 0, -10.5), Vector(31, 3.5, -10.5)));

	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(17, 8.5, -49.5),
		Vector(17, 0, -49.5), Vector(17, 0, -49), Vector(17, 8.5, -49)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(19, 8.5, -49.5),
		Vector(19, 0, -49.5), Vector(19, 0, -49), Vector(19, 8.5, -49)));

	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(29, 8.5, -49.5),
		Vector(29, 0, -49.5), Vector(29, 0, -49), Vector(29, 8.5, -49)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(31, 8.5, -49.5),
		Vector(31, 0, -49.5), Vector(31, 0, -49), Vector(31, 8.5, -49)));

	//inner walls: left side ground floor
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(49, 3.5, -46.5),
		Vector(49, 0, -46.5), Vector(35.5, 0, -46.5), Vector(35.5, 3.5, -46.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(49, 3.5, -37.5),
		Vector(49, 0, -37.5), Vector(35.5, 0, -37.5), Vector(35.5, 3.5, -37.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(49, 3.5, -28.5),
		Vector(49, 0, -28.5), Vector(35.5, 0, -28.5), Vector(35.5, 3.5, -28.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(49, 3.5, -19.5),
		Vector(49, 0, -19.5), Vector(35.5, 0, -19.5), Vector(35.5, 3.5, -19.5)));

	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(35.5, 3.5, -46.5),
		Vector(35.5, 0, -46.5), Vector(35.5, 0, -44.5), Vector(35.5, 3.5, -44.5)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(35.5, 3.5, -42.5),
		Vector(35.5, 0, -42.5), Vector(35.5, 0, -35.5), Vector(35.5, 3.5, -35.5)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(35.5, 3.5, -33.5),
		Vector(35.5, 0, -33.5), Vector(35.5, 0, -26.5), Vector(35.5, 3.5, -26.5)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(35.5, 3.5, -24.5),
		Vector(35.5, 0, -24.5), Vector(35.5, 0, -17.5), Vector(35.5, 3.5, -17.5)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(35.5, 3.5, -15.5),
		Vector(35.5, 0, -15.5), Vector(35.5, 0, -11), Vector(35.5, 3.5, -11)));

	//inner walls: right side ground floor
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(24.75, 3.5, -49),
		Vector(24.75, 0, -49), Vector(24.75, 0, -28), Vector(24.75, 3.5, -28)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(24.75, 3.5, -26),
		Vector(24.75, 0, -26), Vector(24.75, 0, -17.5), Vector(24.75, 3.5, -17.5)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(24.75, 3.5, -15.5),
		Vector(24.75, 0, -15.5), Vector(24.75, 0, -13.25), Vector(24.75, 3.5, -13.25)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(24.75, 3.5, -15.5),
		Vector(24.75, 0, -15.5), Vector(24.75, 0, -13.25), Vector(24.75, 3.5, -13.25)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(21.5, 3.5, -18),
		Vector(21.5, 0, -18), Vector(21.5, 0, -13.5), Vector(21.5, 3.5, -13.5)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(20, 3.5, -24),
		Vector(20, 0, -24), Vector(20, 0, -23), Vector(20, 3.5, -23)));

	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(24.75, 3.5, -24),
		Vector(24.75, 0, -24), Vector(24.75, 0, -17.5), Vector(24.75, 3.5, -17.5)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(24.75, 3.5, -15.5),
		Vector(24.75, 0, -15.5), Vector(24.75, 0, -13.5), Vector(24.75, 3.5, -13.5)));

	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(25, 3.5, -24.25),
		Vector(25, 0, -24.25), Vector(11, 0, -24.25), Vector(11, 3.5, -24.25)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(25, 3.5, -24),
		Vector(25, 0, -24), Vector(11, 0, -24), Vector(11, 3.5, -24)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(25, 3.5, -13),
		Vector(25, 0, -13), Vector(11, 0, -13), Vector(11, 3.5, -13)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(25, 3.5, -13.25),
		Vector(25, 0, -13.25), Vector(11, 0, -13.25), Vector(11, 3.5, -13.25)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(20, 3.5, -23),
		Vector(20, 0, -23), Vector(11, 0, -23), Vector(11, 3.5, -23)));
}

vector<CollisionPlane*>* World::getPlanes() {
	return &planes;
}

World::~World()
{
	//dtor
}
