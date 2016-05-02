#include "CollisionPlane.h"
#include "Vector.h"
#include <GL/glut.h>

CollisionPlane::CollisionPlane(Vector vN, Vector a, Vector b, Vector c, Vector d) {
	this->v1 = a;
	this->v2 = b;
	this->v3 = c;
	this->v4 = d;
	normal = vN;
}

CollisionPlane::~CollisionPlane()
{
}

Vector CollisionPlane::getV1()
{
	return this->v1;
}

Vector CollisionPlane::getV2()
{
	return this->v2;
}

Vector CollisionPlane::getV3()
{
	return this->v3;
}

Vector CollisionPlane::getV4()
{
	return this->v4;
}

Vector CollisionPlane::getNormal()
{
	return normal;
}

bool CollisionPlane::isok()
{
	return (normal.getX() != 0 && normal.getY() != 0 && normal.getZ() != 0);
}

void CollisionPlane::debug() {

	glPushMatrix();
	glBegin(GL_POLYGON);  //if you want to make the plane look solid
						  //glBegin(GL_LINE_LOOP);
	glVertex3f(v1.getX(), v1.getY(), v1.getZ());
	glVertex3f(v2.getX(), v2.getY(), v2.getZ());
	glVertex3f(v3.getX(), v3.getY(), v3.getZ());
	glVertex3f(v4.getX(), v4.getY(), v4.getZ());
	glEnd();
	glPopMatrix();
}

