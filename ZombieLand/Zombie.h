#pragma once
#include "Character.h"
#include "PathA.h"
#include <vector>

class Zombie : public Character
{
public:
	Zombie();
	Zombie(float x, float y, float z);
	std::vector<Vector> path;
	void render(Vector playerPos);
	void update();
	void drawZombie();
	virtual ~Zombie();

protected:

private:
	Vector playerPos;
};

