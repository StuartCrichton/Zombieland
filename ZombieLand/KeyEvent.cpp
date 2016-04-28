#include "KeyEvent.h"
#include <iostream>
using namespace std;

KeyEvent::KeyEvent() {}

KeyEvent::KeyEvent(Player *player, World world, Wave *wave, AmmoBox *box)
{
	this->player = player;
	this->world = world;
	this->wave = wave;
	this->box = box;

	for (int i = 0; i < 256; i++) {
		keyStates[i] = false;
	}
}


KeyEvent::~KeyEvent()
{
	/*delete wave;
	wave = NULL;

	delete player;
	player = NULL;*/
}

void KeyEvent::pressedForward()
{
	v = player->getNewPosition(player->FORWARD);
	player->mask.update(v);
	canMove = true;
	for (unsigned i = 0; i < wave->v_zombies.size(); i++)
	{
		if (player->mask.intersects(wave->v_zombies[i]->mask)) {
			canMove = false;
			player->takeDamage();
		}
	}
	planes = world.getPlanes();
	for (CollisionPlane* p : *planes) {
		if (player->mask.intersectsPlane(p)) {
			canMove = false;
		}
	}
	if (canMove)player->moveForward();
	else
		player->mask.update(player->getPosition());
}

void KeyEvent::pressedBackwards()
{
	v = player->getNewPosition(player->BACKWARD);
	player->mask.update(v);
	canMove = true;
	for (unsigned i = 0; i < wave->v_zombies.size(); i++)
	{
		if (player->mask.intersects(wave->v_zombies[i]->mask)) {
			canMove = false;
			player->takeDamage();
		}
	}
	planes = world.getPlanes();
	for (CollisionPlane* p : *planes) {
		if (player->mask.intersectsPlane(p)) {
			canMove = false;
		}
	}
	if (canMove)player->moveBackward();
	else
		player->mask.update(player->getPosition());
}

void KeyEvent::pressedLeft()
{
	v = player->getNewPosition(player->LEFT);
	player->mask.update(v);
	canMove = true;
	for (unsigned i = 0; i < wave->v_zombies.size(); i++)
	{
		if (player->mask.intersects(wave->v_zombies[i]->mask)) {
			canMove = false;
			player->takeDamage();
		}
	}
	planes = world.getPlanes();
	for (CollisionPlane* p : *planes) {
		if (player->mask.intersectsPlane(p)) {
			canMove = false;
		}
	}
	if (canMove)player->strafeLeft();
	else
		player->mask.update(player->getPosition());
}

void KeyEvent::pressedRight()
{
	v = player->getNewPosition(player->RIGHT);
	player->mask.update(v);
	canMove = true;
	for (unsigned i = 0; i < wave->v_zombies.size(); i++)
	{
		if (player->mask.intersects(wave->v_zombies[i]->mask)) {
			canMove = false;
			player->takeDamage();
		}
	}
	planes = world.getPlanes();
	for (CollisionPlane* p : *planes) {
		if (player->mask.intersectsPlane(p)) {
			canMove = false;
		}
	}
	if (canMove)player->strafeRight();
	else
		player->mask.update(player->getPosition());
}

void KeyEvent::keyOperations()
{
	if (keyStates['r']) {
		//player->init();
		//player->lookAt();
		player->reload();
	}

	if (keyStates['w']) {
		pressedForward();
		//cout << player->getPosition().getX() << " " << player->getPosition().getY() << " " << player->getPosition().getZ() << endl;
	}

	if (keyStates['s']) {
		pressedBackwards();
		//cout << player->getPosition().getX() << " " << player->getPosition().getY() << " " << player->getPosition().getZ() << endl;
	}

	if (keyStates['a']) {
		pressedLeft();
		//cout << player->getPosition().getX() << " " << player->getPosition().getY() << " " << player->getPosition().getZ() << endl;
	}

	if (keyStates['d']) {
		pressedRight();
		//cout << player->getPosition().getX() << " " << player->getPosition().getY() << " " << player->getPosition().getZ() << endl;
	}

	if (keyStates['c']) {
		player->crouch();
	}
	if (keyStates[27]) {
		exit(0);
	}

	player->checkStairs();

	//ammoBox collision check
	if (player->getPosition().getX() >= box->getLocation().getX() && player->getPosition().getX() <= box->getLocation().getX() + 2.5 &&
		player->getPosition().getZ() <= box->getLocation().getZ() && player->getPosition().getZ() >= box->getLocation().getZ() - 2 &&
		player->getPosition().getY() >= box->getLocation().getY() && player->getPosition().getY() <= box->getLocation().getY() + 3.5) {
		box->update();
		player->AmmoPickup();
	}

	
	player->lookAt();
}


