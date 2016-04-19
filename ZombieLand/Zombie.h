#pragma once
#include "Character.h"
#include "PathFinding.h"
#include <vector>

class Zombie : public Character
{
public:
	Zombie();
	Zombie(float x, float y, float z);
	void render(Vector playerPos);
	void update();
	void drawZombie();
	virtual ~Zombie();

protected:

private:
	Vector playerPos;
	PathFinding path;
};

