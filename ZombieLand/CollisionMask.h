#pragma once
#include "Vector.h"
#include "CollisionPlane.h"

class CollisionMask
{
public:
	CollisionMask();
	CollisionMask(Vector v, float s);
	Vector getPosition();
	float getSize();
	bool intersects(CollisionMask mask);
	bool intersectsPlane(CollisionPlane *plane);
	void update(Vector v);
	virtual ~CollisionMask();

protected:

private:
	float minN(float a, float b);
	float maxN(float a, float b);
	Vector position;
	float size;
	float ab(float a);
};

