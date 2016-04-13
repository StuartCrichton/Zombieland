#include "CollisionMask.h"
#include "Vector.h"
#include <iostream>

using namespace std;

CollisionMask::CollisionMask() {}

CollisionMask::CollisionMask(Vector v, float s)//Stores the mask as a sphere with position v and radius s
{
	//ctor
	this->position = v;
	this->size = s;
}

float CollisionMask::minN(float a, float b) {
	return a <= b ? a : b;
}

float CollisionMask::maxN(float a, float b) {
	return a >= b ? a : b;
}

bool CollisionMask::intersectsPlane(CollisionPlane *plane) {
	Vector tmp = this->position - plane->getV1();
	float dotP = tmp.dotProduct(plane->getNormal());
	dotP = abs(dotP);
	if (dotP > this->size) return false;
	else {
		if (plane->getNormal().getX() != 0) {
			float minZ = minN(plane->getV1().getZ(), plane->getV3().getZ());
			float maxZ = maxN(plane->getV1().getZ(), plane->getV3().getZ());
			float minY = minN(plane->getV1().getY(), plane->getV2().getY());
			float maxY = maxN(plane->getV1().getY(), plane->getV2().getY());
			if (position.getZ() >= minZ && position.getZ() <= maxZ
				&& position.getY()-1 >= minY && position.getY()-1 <= maxY) return true;
		}
		else if (plane->getNormal().getZ() != 0) {
			float minX = minN(plane->getV1().getX(), plane->getV3().getX());
			float maxX = maxN(plane->getV1().getX(), plane->getV3().getX());
			float minY = minN(plane->getV1().getY(), plane->getV2().getY());
			float maxY = maxN(plane->getV1().getY(), plane->getV2().getY());
			if (position.getX() >= minX && position.getX() <= maxX
				&& position.getY()-1 >= minY && position.getY()-1 <= maxY)return true;
		}
	}
	return false;
		
	/*cout << position.getX() << " y " << position.getY() << " z " << position.getZ() << endl
		<< plane->getV1().getX() << " "
		<< plane->getV1().getZ() << " " << endl
		<< plane->getV3().getX() << " "
		<< plane->getV3().getZ() << " " << endl;*/
}

Vector CollisionMask::getPosition()
{
	return this->position;
}

float CollisionMask::getSize()
{
	return this->size;
}

bool CollisionMask::intersects(CollisionMask mask) {//sphere on sphere collision
	Vector v2 = mask.position;
	Vector difference = position - v2;
	float dot = difference.dotProduct();
	float sumR = size + mask.size;
	sumR *= sumR;
	if (dot <= sumR)
		return true;
	return false;
}

void CollisionMask::update(Vector v)
{
	this->position = v;
}

float CollisionMask::ab(float a)//returns absolute value of a float
{
	return a < 0 ? -a : a;
}

CollisionMask::~CollisionMask()
{
	//dtor
}
