#pragma once
#include "Character.h"
#include "Path.h"
#include "PathFinder.h"
#include <vector>
#include "World.h"

class Zombie : public Character
{
public:
	Zombie(float x, float y, float z, World* w);
	void render();
	void drawZombie();
	void set(Vector* v);
	Vector update(Vector playerPos, int floor);
	CollisionMask head;
	void takeDamage();
	int getHealth();
	~Zombie();
protected:

private:
	Vector playerPos;
	Vector spawn;
	World* world;//for wall collision
	Path path;
	int counter = 0;
	int health = 3;
};

