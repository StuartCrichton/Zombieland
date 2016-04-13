#pragma once
#include "Vector.h"

class CollisionPlane {
public:
	Vector  v1, v2, v3, v4;
	Vector  normal;
	CollisionPlane(Vector vN, Vector v1, Vector v2, Vector v3, Vector v4);
	Vector getV1();
	Vector getV2();
	Vector getV3();
	Vector getV4();
	Vector getNormal();
	void debug();
	bool isok();
};
