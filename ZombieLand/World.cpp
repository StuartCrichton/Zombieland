#include "World.h"
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <GL/glut.h>
#include <cstdlib>
#include "CollisionPlane.h"
#include "AssimpModelLoader.h"

#include "World.h"
#include <windows.h>
#include <GL/glut.h>
#include <cstdlib>
#include "CollisionPlane.h"
#include "AssimpModelLoader.h"
#include "PathFinder.h"
#include <iostream>

World::World()
{

}


void World::init() {
	this->building.loadObjFile("../Office.obj");
	this->ammoBox.loadObjFile("../AmmoBox.obj");
	this->gun.loadObjFile("../Gun3.obj");
	setPlanes();
	setObstacles();
}

void World::setPlanes() {
	//outer wall 60x80, normal points into world
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(0.5, 3.5, -0.5),
		Vector(0.5, 0, -0.5), Vector(59.5, 0, -0.5), Vector(59.5, 3.5, -0.5)));
	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(0.5, 3.5, -0.5),
		Vector(0.5, 0, -0.5), Vector(0.5, 0, -79.5), Vector(0.5, 3.5, -79.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(0.5, 3.5, -79.5),
		Vector(0.5, 0, -79.5), Vector(59.5, 0, -79.5), Vector(59.5, 3.5, -79.5)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(59.5, 3.5, -0.5),
		Vector(59.5, 0, -0.5), Vector(59.5, 0, -79.5), Vector(59.5, 3.5, -79.5)));

	//building outer-rim of wall
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(10.5, 3.5, -10.5),
		Vector(10.5, 0, -10.5), Vector(29, 0, -10.5), Vector(29, 3.5, -10.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(31, 3.5, -10.5),
		Vector(31, 0, -10.5), Vector(49.5, 0, -10.5), Vector(49.5, 3.5, -10.5)));

	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(10.5, 3.5, -10.5),
		Vector(10.5, 0, -10.5), Vector(10.5, 0, -49.5), Vector(10.5, 3.5, -49.5)));

	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(10.5, 3.5, -49.5),
		Vector(10.5, 0, -49.5), Vector(17, 0, -49.5), Vector(17, 3.5, -49.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(19, 3.5, -49.5),
		Vector(19, 0, -49.5), Vector(29, 0, -49.5), Vector(29, 3.5, -49.5)));
	planes.push_back(setPlane(0, 31, 49.5, 0, 3.5, -49.5));

	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(49.5, 3.5, -10.5),
		Vector(49.5, 0, -10.5), Vector(49.5, 0, -49.5), Vector(49.5, 3.5, -49.5)));

	//building inner-rim of wall
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(11, 3.5, -11),
		Vector(11, 0, -11), Vector(29, 0, -11), Vector(29, 3.5, -11)));
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(31, 3.5, -11),
		Vector(31, 0, -11), Vector(49, 0, -11), Vector(49, 3.5, -11)));

	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(11, 3.5, -11),
		Vector(11, 0, -11), Vector(11, 0, -49), Vector(11, 3.5, -49)));

	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(11, 3.5, -49),
		Vector(11, 0, -49), Vector(17, 0, -49), Vector(17, 3.5, -49)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(19, 3.5, -49),
		Vector(19, 0, -49), Vector(29, 0, -49), Vector(29, 3.5, -49)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(31, 3.5, -49),
		Vector(31, 0, -49), Vector(49, 0, -49), Vector(49, 3.5, -49)));

	planes.push_back(new CollisionPlane(Vector(1, 0, 0), Vector(49, 3.5, -11),
		Vector(49, 0, -11), Vector(49, 0, -49), Vector(49, 3.5, -49)));

	//doorway side walls
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(29, 3.5, -11),
		Vector(29, 0, -11), Vector(29, 0, -10.5), Vector(29, 3.5, -10.5)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(31, 3.5, -11),
		Vector(31, 0, -11), Vector(31, 0, -10.5), Vector(31, 3.5, -10.5)));

	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(17, 3.5, -49.5),
		Vector(17, 0, -49.5), Vector(17, 0, -49), Vector(17, 3.5, -49)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(19, 3.5, -49.5),
		Vector(19, 0, -49.5), Vector(19, 0, -49), Vector(19, 3.5, -49)));

	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(29, 3.5, -49.5),
		Vector(29, 0, -49.5), Vector(29, 0, -49), Vector(29, 3.5, -49)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(31, 3.5, -49.5),
		Vector(31, 0, -49.5), Vector(31, 0, -49), Vector(31, 3.5, -49)));

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

	////////////////////////////////////////////////////////////////////////////////////
	//SECOND FLOOR 
	//OUTER WALL - OUTER RIM
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(10.5, 7, -10.5),
		Vector(10.5, 3.5, -10.5), Vector(49.5, 3.5, -10.5), Vector(49.5, 7, -10.5)));

	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(10.5, 7, -10.5),
		Vector(10.5, 3.5, -10.5), Vector(10.5, 3.5, -16), Vector(10.5, 7, -16)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(10.5, 7, -18),
		Vector(10.5, 3.5, -18), Vector(10.5, 3.5, -34), Vector(10.5, 7, -34)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(10.5, 7, -36),
		Vector(10.5, 3.5, -36), Vector(10.5, 3.5, -49.5), Vector(10.5, 7, -49.5)));

	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(10.5, 7, -49.5),
		Vector(10.5, 3.5, -49.5), Vector(29, 3.5, -49.5), Vector(29, 7, -49.5)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(31, 7, -49.5),
		Vector(31, 3.5, -49.5), Vector(49.5, 3.5, -49.5), Vector(49.5, 7, -49.5)));

	planes.push_back(setPlane(1, -10.5, -24.5, 3.5, 7, 49.5));
	planes.push_back(setPlane(1, -26.5, -40.5, 3.5, 7, 49.5));
	planes.push_back(setPlane(1, -42.5, -50, 3.5, 7, 49.5));

	//Outer WALL - Inner Rim
	planes.push_back(new CollisionPlane(Vector(0, 0, 1), Vector(11, 7, -11),
		Vector(11, 3.5, -11), Vector(49, 3.5, -11), Vector(49, 7, -11)));

	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(11, 7, -11),
		Vector(11, 3.5, -11), Vector(11, 3.5, -16), Vector(11, 7, -16)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(11, 7, -18),
		Vector(11, 3.5, -18), Vector(11, 3.5, -34), Vector(11, 7, -34)));
	planes.push_back(new CollisionPlane(Vector(-1, 0, 0), Vector(11, 7, -36),
		Vector(11, 3.5, -36), Vector(11, 3.5, -49), Vector(11, 7, -49)));

	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(11, 7, -49),
		Vector(11, 3.5, -49), Vector(29, 3.5, -49), Vector(29, 7, -49)));
	planes.push_back(new CollisionPlane(Vector(0, 0, -1), Vector(31, 7, -49),
		Vector(31, 3.5, -49), Vector(49, 3.5, -49), Vector(49, 7, -49)));

	planes.push_back(setPlane(1, -11, -24.5, 3.5, 7, 49));
	planes.push_back(setPlane(1, -26.5, -40.5, 3.5, 7, 49));
	planes.push_back(setPlane(1, -42.5, -49, 3.5, 7, 49));

	//Doorway side walls - outer wall
	planes.push_back(setPlane(0, 49.5, 49, 3.5, 7, -24.5));
	planes.push_back(setPlane(0, 49.5, 49, 3.5, 7, -26.5));
	planes.push_back(setPlane(0, 49.5, 49, 3.5, 7, -40.5));
	planes.push_back(setPlane(0, 49.5, 49, 3.5, 7, -42.5));

	planes.push_back(setPlane(0, 11, 10.5, 3.5, 7, -16));
	planes.push_back(setPlane(0, 11, 10.5, 3.5, 7, -18));
	planes.push_back(setPlane(0, 11, 10.5, 3.5, 7, -34));
	planes.push_back(setPlane(0, 11, 10.5, 3.5, 7, -36));

	planes.push_back(setPlane(1, -49.5, -49, 3.5, 7, 29));
	planes.push_back(setPlane(1, -49.5, -49, 3.5, 7, 31));

	//Balcony wall
	planes.push_back(setPlane(0, 6.75, 10.5, 3.5, 7, -10.5));
	planes.push_back(setPlane(0, 49.5, 53, 3.5, 7, -10.5));

	planes.push_back(setPlane(1, -10.5, -54, 3.5, 7, 6.75));
	planes.push_back(setPlane(1, -10.5, -54, 3.5, 7, 53));

	planes.push_back(setPlane(0, 6.75, 53, 3.5, 7, -53));

	//Inner walls
	planes.push_back(setPlane(0, 49.5, 35, 3.5, 7, -38.5));
	planes.push_back(setPlane(0, 49.5, 35, 3.5, 7, -29.75));
	planes.push_back(setPlane(0, 49.5, 35, 3.5, 7, -20.75));

	planes.push_back(setPlane(1, -38.5, -36.5, 3.5, 7, 35));
	planes.push_back(setPlane(1, -34.5, -27.5, 3.5, 7, 35));
	planes.push_back(setPlane(1, -25.5, -18.5, 3.5, 7, 35));
	planes.push_back(setPlane(1, -16.5, -10.5, 3.5, 7, 35));

	planes.push_back(setPlane(1, -49, -43.5, 3.5, 7, 25));
	planes.push_back(setPlane(1, -41.5, -34.5, 3.5, 7, 25));
	planes.push_back(setPlane(0, 25, 31, 3.5, 7, -34.5));
	planes.push_back(setPlane(1, -34.5, -28.75, 3.5, 7, 31));
	planes.push_back(setPlane(1, -26.75, -20.75, 3.5, 7, 31));
	planes.push_back(setPlane(0, 31, 22, 3.5, 7, -20.75));
	planes.push_back(setPlane(0, 20, 11, 3.5, 7, -20.75));

	planes.push_back(setPlane(1, -49, -44, 3.5, 7, 35.5));
	planes.push_back(setPlane(0, 35.5, 45.6, 3.5, 7, -44));
	planes.push_back(setPlane(0, 35.5, 45.6, 3.5, 7, -46.5));

	//Cubicles
	planes.push_back(setPlane(0, 21, 15, 3.5, 7, -44));
	planes.push_back(setPlane(0, 21, 15, 3.5, 7, -41));
	planes.push_back(setPlane(0, 21, 15, 3.5, 7, -38));
	planes.push_back(setPlane(0, 21, 15, 3.5, 7, -35));
	planes.push_back(setPlane(0, 21, 15, 3.5, 7, -32));
	planes.push_back(setPlane(0, 21, 15, 3.5, 7, -29));
	planes.push_back(setPlane(0, 21, 15, 3.5, 7, -26));

	planes.push_back(setPlane(1, -44, -41, 3.5, 7, 20));
	planes.push_back(setPlane(1, -44, -41, 3.5, 7, 16));

	planes.push_back(setPlane(1, -41, -38, 3.5, 7, 20));
	planes.push_back(setPlane(1, -41, -38, 3.5, 7, 16));

	planes.push_back(setPlane(1, -38, -35, 3.5, 7, 20));
	planes.push_back(setPlane(1, -38, -35, 3.5, 7, 16));

	planes.push_back(setPlane(1, -35, -32, 3.5, 7, 20));
	planes.push_back(setPlane(1, -35, -32, 3.5, 7, 16));

	planes.push_back(setPlane(1, -32, -29, 3.5, 7, 20));
	planes.push_back(setPlane(1, -32, -29, 3.5, 7, 16));

	//Arround staircases
	planes.push_back(setPlane(1, -29, -26, 3.5, 7, 20));
	planes.push_back(setPlane(1, -29, -26, 3.5, 7, 16));

	planes.push_back(setPlane(1, -11, -14, 3.5, 7, 25));
	planes.push_back(setPlane(0, 25, 15, 3.5, 7, -13.5));
	

	///////////////////////////////////////////////////////////////////////////
	//ROOF
	planes.push_back(setPlane(1, -11, -49, 7, 8, 11));
	planes.push_back(setPlane(0, 11, 49, 7, 8, -49));
	planes.push_back(setPlane(1, -49, -11, 7, 8, 49));
	planes.push_back(setPlane(0, 49, 11, 7, 8, -11));

	planes.push_back(setPlane(0, 33, 46, 7, 8, -44));
	planes.push_back(setPlane(0, 33, 46, 7, 8, -46.5));
	planes.push_back(setPlane(1, -47, -44, 7, 8, 45.5));

	//TO_DO: ADD INVISIBLE WALLS NEXT TO STAIRS and add forgotten walls at stair 1 upper floor
}

void World::setObstacles() {
	for (int k = 0; k < 3; k++)
		for (int i = 0; i < 60; i++)
			for (int j = 0; j < 80; j++) {
				obstacles[k][i][j] = 'o';//o is open, w is wall
			}


	//set char[i][j] as w for a wall
	for (unsigned i = 0; i < planes.size(); i++) {
		CollisionPlane *p = planes[i];
		int xNormal = p->getNormal().getX();
		int floorN = 0;
		if (p->getV1().getY() == 3.5) floorN = 0;
		else if (p->getV1().getY() == 7) floorN = 1;
		else floorN = 2;
			if (xNormal != 0) {//z changes, x is constant
				int x = floor(p->getV1().getX());
				int start = floor(min(-p->getV1().getZ(), -p->getV3().getZ()));
				int end = floor(max(-p->getV1().getZ(), -p->getV3().getZ()));
				for (int i = start; i < end; i++) {
					obstacles[floorN][x][i] = 'w';
				}
			}
			else {//z constant, x changes
				int z = floor(-p->getV1().getZ());
				int start = floor(min(p->getV1().getX(), p->getV3().getX()));
				int end = floor(max(p->getV1().getX(), p->getV3().getX()));
				for (int i = start; i < end; i++)
					obstacles[floorN][i][z] = 'w';
			}
	}
	
	cout << endl;
	for (int k = 0; k < 3; k++){
		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 80; j++) {
				if (obstacles[k][i][j] == 'w')
					cout << obstacles[k][i][j];
				else
					cout << ".";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
}

CollisionPlane* World::setPlane(float xNormal, float start, float end, float bottom, float top, float constant) {
	if (xNormal != 0) {//x normal, z changes
		return new CollisionPlane(Vector(xNormal, 0, 0), Vector(constant, top, start),
			Vector(constant, bottom, start), Vector(constant, bottom, end), Vector(constant, top, end));
	}
	else {//z normal, x changes
		return new CollisionPlane(Vector(0, 0, 1), Vector(start, top, constant),
			Vector(start, bottom, constant), Vector(end, bottom, constant), Vector(end, top, constant));
	}
}

vector<CollisionPlane*>* World::getPlanes() {
	return &planes;
}

World::~World()
{
	//dtor
}
