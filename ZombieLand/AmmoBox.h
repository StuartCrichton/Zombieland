#pragma once
class AmmoBox
{
public:
	AmmoBox();
	~AmmoBox();

private:
	const double AMMO_BOX_SPAWN_LOCATIONS[3][3] = {
		{ 48.3914, 1.0, -11.4375 },
		{ 1.05685, 1.0, -0.748576 },
		{ 23.9005, 1.0, -47.1757 }
	};
};

