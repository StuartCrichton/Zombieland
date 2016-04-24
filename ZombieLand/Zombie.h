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
	//vector<Vector> path;
	void render();
	Vector update(Vector playerPos);
	void drawZombie();
	virtual ~Zombie();
	void set(Vector v);
protected:

private:
	Vector playerPos;
	World* world;//for wall collision
	Path path;
	int counter = 0;
};

