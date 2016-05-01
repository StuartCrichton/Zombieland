#pragma once
#include "Vector.h"
#include "CollisionMask.h"
#include <GL/glut.h>
class Bullet
{
public:
	Bullet(Vector* position, Vector* direction);
	CollisionMask mask;
	void update();
	void render();
	int getSteps();
	Vector getPosition();
	~Bullet();
private:
	Vector position;
	Vector direction;
	int steps = 0;
};

