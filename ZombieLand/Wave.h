#pragma once
#ifndef WAVE_H
#define WAVE_H
#include "Zombie.h"
#include <vector>
#include "World.h"

using namespace std;

class Wave
{
public:
	Wave(World* w);
	~Wave();
	void addNewZombie();
	void incrementWaveNumber();
	int getZombieSpawnInterval();

	vector<Zombie*> v_zombies;
	int waveNumber = 1;
	int numOfZombies = 10;
	const float WAVE_DURATION = 30000.0;
	const float WAVE_COOLDOWN = 5000.0;

private:
	World* world;
	const int WAVE_INCREMENTER = 5;
	const double ZOMBIE_SPAWN_LOCATIONS[8][3] = {
		{ 58, 1, -78 },
		{ 58, 1, -1 },
		{ 29, 1, -1 },
		{ 14, 1, -21 },
		{ 3, 1, -1 },
		{52, 8, -52},
		{ 52, 4.5, -13 },
		{ 9, 4.5, -13 }
	};

};

#endif // !WAVE_H