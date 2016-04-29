#include "Player.h"
#include <math.h>
#include <GL/glut.h>
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;

sf::SoundBuffer bufferReload;
sf::Sound soundReload(bufferReload);
sf::SoundBuffer bufferGun;
sf::Sound soundGun(bufferGun);


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

void Player::shoot() {
	if (noRel && noShoot) {
		//canShoot = true;
		reloading = false;
		shooting = true;
		noShoot = false;
		previousTimeShoot = glutGet(GLUT_ELAPSED_TIME);
		if (ammoCartridge > 0) {
			ammoCartridge--;
			bufferGun.loadFromFile("../Gun.wav");
			soundGun.play(); // Play the sound!
			if (ammoCartridge == 0)
				if (ammoTotal > 0)
					reload();
		}
	}
}

void Player::reload() {
	if (ammoCartridge != 33) {//full cartridge already
		noRel = false;
		//canShoot = false;
		reloading = true;
		previousTimeRel = glutGet(GLUT_ELAPSED_TIME);
		bufferReload.loadFromFile("../Reload.wav");
		soundReload.setVolume(100);
		soundReload.play(); // Play the sound!
		int dif = ammoCartridgeTotal - ammoCartridge;
		ammoTotal -= dif;
		ammoCartridge += dif;
		//previousTime = 0;
	}
}

void Player::regainHealth() {
	if (health < 100)
		health+=2;
}

void Player::takeDamage() {
	if (health - 5 >= 0)
		health -= 5;
	else
		health = 0;
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

void Player::AmmoPickup() {
	ammoCartridge = ammoCartridgeTotal;
	ammoTotal = 99;
}

bool Player::getReloading() {
	return this->reloading;
}

bool Player::getShooting() {
	return this->shooting;
}
bool Player::getNoRel() {
	return this->noRel;
}
bool Player::getNoShoot() {
	return this->noShoot;
}
/*bool Player::getcanShoot() {
	return this->canShoot;
}*/
float Player::getPrevTimeRel() {
	return this->previousTimeRel;
}
float Player::getPrevTimeShoot() {
	return this->previousTimeShoot;
}
void Player::setReloading(bool reloading) {
	this->reloading = reloading;
}
void Player::setShooting(bool shooting) {
	this->shooting = shooting;
}
/*void Player::setcanShoot(bool canShoot) {
	this->canShoot = canShoot;
}*/
void Player::setNoShoot(bool noShoot) {
	this->noShoot = noShoot;
}
void Player::setNoRel(bool noRel) {
	this->noRel = noRel;
}
void Player::setPrevTimeRel(float previousTimeRel) {
	this->previousTimeRel = previousTimeRel;
}
void Player::setPrevTimeShoot(float previousTimeShoot) {
	this->previousTimeShoot = previousTimeShoot;
}
Player::Player()
{
	init();
	this->mask = CollisionMask(pos_v, 0.45);
	this->floor = getFloor(1.7);
}

Player::~Player()
{
	//dtor
}
