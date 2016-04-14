#include "Player.h"
#include <math.h>
#include <GL/glut.h>
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <iostream>

using namespace std;

void Player::init() {//set the start values of the player
	thetha = M_PI;
	phi = 0;
	pos_v.setV(20, 1.7, -75);
	look_v.setV(sin(thetha), sin(phi), -cos(thetha));
}

void Player::lookAt() {//Camera function calls gluLookAt
	gluLookAt(pos_v.getX(), pos_v.getY(), pos_v.getZ(), // camera position
		pos_v.getX() + look_v.getX(), pos_v.getY() + look_v.getY(), pos_v.getZ() + look_v.getZ(), // look at position, line of sight
		0, 1.7, 0); // up direction (vector) for camera tilt
	glutPostRedisplay();
}

void Player::rotateY(int angle) {        //rotates the camera a set angle in the y-axis
	float radian = (angle*M_PI) / 1800;   //convert angle to radians and scale down
	phi -= radian;
	if (phi > M_PI / 2) phi = M_PI / 2;
	if (phi < -M_PI / 2) phi = -M_PI / 2;
	look_v.setV(look_v.getX(), sin(phi), look_v.getZ());
}

void Player::moveBackward() {
	pos_v.setV(pos_v.getX() - look_v.getX() * step,
		pos_v.getY(),
		pos_v.getZ() - look_v.getZ() * step);
}

void Player::strafeLeft()
{
	look_v.setV(sin(thetha + M_PI / 2), look_v.getY(), -cos(thetha + M_PI / 2));
	pos_v.setV(pos_v.getX() - look_v.getX() * step,
		pos_v.getY(),
		pos_v.getZ() - look_v.getZ() * step);
	look_v.setV(sin(thetha), look_v.getY(), -cos(thetha));
}

void Player::strafeRight()
{
	look_v.setV(sin(thetha + M_PI / 2), look_v.getY(), -cos(thetha + M_PI / 2));
	pos_v.setV(pos_v.getX() + look_v.getX() * step,
		pos_v.getY(),
		pos_v.getZ() + look_v.getZ() * step);
	look_v.setV(sin(thetha), look_v.getY(), -cos(thetha));
}
void Player::lookAround(int x, int y) {
	xOrigin = glutGet(GLUT_WINDOW_WIDTH) / 2;
	yOrigin = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	if (warped) {
		warped = false;
		return;
	}
	int dx = x - xOrigin;
	int dy = y - yOrigin;
	if (dx)this->rotateX(dx);
	if (dy)this->rotateY(dy);
	glutWarpPointer(xOrigin, yOrigin);
	warped = true;

}

void Player::jump() {}
void Player::crouch()
{
	/*
	If the player is crouched, make him stand
	*/
	if (this->crouched) {
		pos_v.setV(pos_v.getX(),
			pos_v.getY() + 1,
			pos_v.getZ());
		this->crouched = false;
	}
	/*
	If the player is standing, make him crouch
	*/
	else {
		pos_v.setV(pos_v.getX(),
			pos_v.getY() - 1,
			pos_v.getZ());
		this->crouched = true;
	}
	lookAt();
}

void Player::shoot() {
	if (ammoCartridge > 0) {
		ammoCartridge--;
	}
	else if (ammoTotal > 0) {
		ammoCartridge = ammoCartridgeTotal;
		ammoTotal -= ammoCartridgeTotal;
	}
}

void Player::regainHealth() {
	if (health < 100)
		health++;
}

void Player::takeDamage() {
	if (health - 5 >= 0)
		health -= 5;
}

int Player::getHealth() {
	return this->health;
}

int Player::getAmmoCartridge() {
	return this->ammoCartridge;
}

int Player::getAmmoTotal() {
	return this->ammoTotal;
}

int Player::getWaveNumber() {
	return this->waveNumber;
}

void Player::setWaveNumber(int waveNumber)
{
	this->waveNumber = waveNumber;
}

int Player::getScore() {
	return this->score;
}

void Player::scoreUp() {
	this->score++;
}

void Player::setY(float x) {
	this->pos_v = Vector(pos_v.getX(), 1.7 + x, pos_v.getZ());
}

float Player::getPhi() {
	return this->phi;
}

Player::Player()
{
	this->mask = CollisionMask(pos_v, 0.45);
	init();

}

Player::~Player()
{
	//dtor
}
