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
	Vector getLocation();
private:
	const double AMMO_BOX_SPAWN_LOCATIONS[6][3] = {
		{ 45.308, 0.0, -11.4375 },
		{ 1.05685, 0.0, -0.748576 },
		{ 26.2555, 0.0, -47.1757 },
		{ 11.6086, 3.5, -46.0803 },
		{ 31.0324, 3.5, -11.8502},
		{ 11.272, 7, -44.859 }
	};
	Vector pos;
	World world;
};
#endif // !AMMOBOX_H

