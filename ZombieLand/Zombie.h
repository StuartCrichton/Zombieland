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
	void set(Vector v);
	Vector update(Vector playerPos);
	~Zombie();
protected:

private:
	Vector playerPos;
	World* world;//for wall collision
	Path path;
	int counter = 0;
};

