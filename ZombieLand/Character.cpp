#include "Character.h"
#include <math.h>
#include "World.h"

void Character::turnRight() {
	thetha += 0.01f;
	look_v.setV(sin(thetha), look_v.getY(), -cos(thetha));
}

void Character::rotateX(int angle) {//rotates the camera by a set angle in the x-z plane
	thetha += (angle*0.001f);
	look_v.setV(sin(thetha), look_v.getY(), -cos(thetha));
}

void Character::turnLeft() {
	thetha -= 0.01f;
	look_v.setV(sin(thetha), look_v.getY(), -cos(thetha));
}

void Character::moveForward() {
	pos_v.setV(pos_v.getX() + look_v.getX() * step,
		pos_v.getY(),
		pos_v.getZ() + look_v.getZ() * step);
}

void Character::moveForward(float steps) {
	pos_v.setV(pos_v.getX() + look_v.getX() * steps,
		pos_v.getY(),
		pos_v.getZ() + look_v.getZ() * steps);
}

Vector Character::getPosition()
{
	return pos_v;
}

Vector Character::getLookVector()
{
	return look_v;
}

float Character::getThetha() {
	return thetha;
}

Vector Character::getNewPosition(int id)//return the new position of where the character should be if he moves
{
	if (id == FORWARD)
		return Vector(pos_v.getX() + look_v.getX() * step, pos_v.getY(), pos_v.getZ() + look_v.getZ() * step);
	else if (id == BACKWARD)
		return Vector(pos_v.getX() - look_v.getX() * step, pos_v.getY(), pos_v.getZ() - look_v.getZ() * step);
	else if (id == LEFT) {
		look_v.setV(sin(thetha + M_PI / 2), look_v.getY(), -cos(thetha + M_PI / 2));
		Vector v(pos_v.getX() - look_v.getX() * step,
			pos_v.getY(),
			pos_v.getZ() - look_v.getZ() * step);
		look_v.setV(sin(thetha), look_v.getY(), -cos(thetha));
		return v;
	}
	else if (id == RIGHT) {
		look_v.setV(sin(thetha + M_PI / 2), look_v.getY(), -cos(thetha + M_PI / 2));
		Vector v(pos_v.getX() + look_v.getX() * step,
			pos_v.getY(),
			pos_v.getZ() + look_v.getZ() * step);
		look_v.setV(sin(thetha), look_v.getY(), -cos(thetha));
		return v;
	}
	else return pos_v;

}

Vector Character::getUnitVector() {
	return this->look_v;
}


Character::Character()
{
	//ctor
}

Character::~Character()
{
	//dtor
}
