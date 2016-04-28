#include "Character.h"
#include <math.h>
#include "World.h"

void Character::turnRight() {
	thetha += 0.01f;
	look_v.setV(sin(thetha), look_v.getY(), -cos(thetha));
}

void Character::rotateX(int angle) {//rotates the camera by a set angle in the x-z plane
	this->thetha += (angle*0.001f);
	look_v.setV(sin(thetha), look_v.getY(), -cos(thetha));
}

void Character::turnLeft() {
	this->thetha -= 0.01f;
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
	return this->thetha;
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

void Character::checkStairs() {
	if (pos_v.getZ() >= -49 && pos_v.getZ() <= -46.5 &&
		pos_v.getX() >= 35.5 && pos_v.getX() <= 45.5 &&
		pos_v.getY() <= 5.4)
	{
		float ratio = (pos_v.getX() - 35.5) / 10;
		pos_v.setY(ratio*3.5 + 1.7);
	}

	else if (pos_v.getZ() >= -13.5 && pos_v.getZ() <= -11 &&
		pos_v.getX() >= 15 && pos_v.getX() <= 25 &&
		pos_v.getY() <= 5.4)
	{
		float ratio = (25 - pos_v.getX()) / 10;
		pos_v.setY(ratio*3.5 + 1.7);
	}

	else if (pos_v.getZ() >= -46.5 && pos_v.getZ() <= -44
		&& pos_v.getX() >= 35.5 && pos_v.getX() <= 45.5 &&
		pos_v.getY() >= (5) && pos_v.getY() <= (3.5 + 1.7 + 3.5))
	{
		float ratio = (45.5 - pos_v.getX()) / 10;
		pos_v.setY(ratio*3.5 + 1.7 + 3.5);
	}

	else {
		if (pos_v.getY() >= (4.5) && pos_v.getY() <= (6))
			pos_v.setY(5.2);
		else if (pos_v.getY() >= (8) && pos_v.getY() <= (9.5))
			pos_v.setY(8.7);
		else if (pos_v.getY() >= (1) && pos_v.getY() <= (2))
			pos_v.setY(1.7);
	}
}

int Character::getFloor(float eyeLevel) {
	float y = pos_v.getY() - eyeLevel;
	if (y >= 0 && y <= 3.5)
		return 0;
	else if (y >= 3.5 && y <= 7)
		return 1;
	else
		return 2;
}

int Character::getFloor(float y, float eyeLevel) {
	if (y - eyeLevel >= 0 && y - eyeLevel <= 3.5)
		return 0;
	else if (y - eyeLevel >= 3.5 && y - eyeLevel <= 7)
		return 1;
	else
		return 2;
}

Character::Character()
{
	//ctor
}

Character::~Character()
{
	//dtor
}
