#pragma once
#ifndef AMMOBOX_H
#define AMMOBOX_H

using namespace std;


class AmmoBox
{
public:
	void render();
	void update();
	void hide();

	AmmoBox();
	~AmmoBox();

private:
	const double AMMO_BOX_SPAWN_LOCATIONS[6][3] = {
		{ 48.3914, 1.0, -11.4375 },
		{ 1.05685, 1.0, -0.748576 },
		{ 23.9005, 1.0, -47.1757 },
		{ 13.3193, 4.5, -47.6932 },
		{ 34.0009, 4.5, -12.3445 },
		{ 11.272, 8, -44.859 }
	};
};

#endif //AMMOBOX_H