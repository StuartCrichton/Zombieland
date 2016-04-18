#include "KeyEvent.h"
#include <iostream>
using namespace std;

KeyEvent::KeyEvent() {}

KeyEvent::KeyEvent(Player *player, World world, Wave *wave)
{
	this->player = player;
	this->world = world;
	this->wave = wave;

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
		player->init();
		player->lookAt();
	}

	if (keyStates['w']) {
		pressedForward();
	}

	if (keyStates['s']) {
		pressedBackwards();
	}

	if (keyStates['a']) {
		pressedLeft();
	}

	if (keyStates['d']) {
		pressedRight();
	}

	if (keyStates['c']) {
		player->crouch();
	}
	if (keyStates[27]) {
		exit(0);
	}

	if (player->getPosition().getZ() >= -49 && player->getPosition().getZ() <= -46.5 &&
		player->getPosition().getX() >= 35.5 && player->getPosition().getX() <= 45.5 &&
		player->getPosition().getY() <= 5.4)
	{
		float ratio = (player->getPosition().getX() - 35.5) / 10;
		player->setY(ratio*3.5);
	}

	else if (player->getPosition().getZ() >= -13.5 && player->getPosition().getZ() <= -11 &&
		player->getPosition().getX() >= 15 && player->getPosition().getX() <= 25 &&
		player->getPosition().getY() <= 5.4)
	{
		float ratio = (25 - player->getPosition().getX()) / 10;
		player->setY(ratio*3.5);
	}

	else if (player->getPosition().getZ() >= -46.5 && player->getPosition().getZ() <= -44
		&& player->getPosition().getX() >= 35.5 && player->getPosition().getX() <= 45.5 &&
		player->getPosition().getY() >= (5) && player->getPosition().getY() <= (3.5 + 1.7 + 3.5))
	{
		float ratio = (45.5 - player->getPosition().getX()) / 10;
		player->setY(ratio*3.5 + 3.5);
	}

	else {
		if (player->getPosition().getY() >= (4.5) && player->getPosition().getY() <= (6))
			player->setY(5.2 - 1.7);
		else if (player->getPosition().getY() >= (8) && player->getPosition().getY() <= (9.5))
			player->setY(8.7 - 1.7);
		else if (player->getPosition().getY() >= (1) && player->getPosition().getY() <= (2))
			player->setY(0);
	}

	player->lookAt();
}

