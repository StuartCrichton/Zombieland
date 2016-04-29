#pragma once
#include "Vector.h"
#include "CollisionMask.h"

class Ray
{
public:
	Ray(Vector o, Vector d);
	~Ray();
	Vector getOrigin();
	Vector getDirection();
	bool intersects(CollisionMask sphere);
	float getDistance();
protected:

private:
	bool pointInSphere(CollisionMask sphere, Vector v);
	Vector pos_v;
	Vector dir;
	float distance;
};

