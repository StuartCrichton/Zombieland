#pragma once
#ifndef AMMOBOX_H
#define AMMOBOX_H
#include "Vector.h"
#include "World.h"

class AmmoBox
{
public:
	AmmoBox();
	~AmmoBox();
	void update();
	void draw();
private:
	const double AMMO_BOX_SPAWN_LOCATIONS[6][3] = {
		{ 48.3914, 0.0, -11.4375 },
		{ 1.05685, 0.0, -0.748576 },
		{ 23.9005, 0.0, -47.1757 },
		{ 13.3193, 3.5, -47.6932 },
		{ 34.0009, 3.5, -12.3445},
		{ 11.272, 7, -44.859 }
	};
	Vector pos;
	World world;
};
#endif // !AMMOBOX_H

