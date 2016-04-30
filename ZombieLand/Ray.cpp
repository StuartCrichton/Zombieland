#include "Ray.h"
#include "Vector.h"
#include "CollisionMask.h"
#include <iostream>

using namespace std;
Ray::Ray(Vector o, Vector d)
{
	this->pos_v = o;
	this->dir = d;
}

bool Ray::intersects(CollisionMask sphere)
{
	if (pointInSphere(sphere, pos_v))return true;

	Vector v = sphere.getPosition() - pos_v;
	float f = v.dotProduct(dir);
	if (f < 0) return false;

	Vector v2 = pos_v + dir*f;
	distance = pos_v.getDistance(v2);
	return pointInSphere(sphere, v2);
}

bool Ray::pointInSphere(CollisionMask sphere, Vector v)
{
	Vector difference = sphere.getPosition() - v;
	float d = difference.dotProduct();
	if (d < sphere.getSize()*sphere.getSize()) return true;
	return false;
}

float Ray::getDistance()
{
	return distance;
}

Vector Ray::getDirection()
{
	return this->dir;
}

Vector Ray::getOrigin()
{
	return this->pos_v;
}

Ray::~Ray()
{
	//dtor
}
