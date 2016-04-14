#pragma once
#ifndef WAVE_H
#define WAVE_H
#include "Zombie.h"
#include <vector>

using namespace std;

class Wave
{
public:
	Wave();
	~Wave();
	vector<Zombie*> v_zombies;
	void addNewZombie();
	void incrementWaveNumber();
	int getZombieSpawnInterval();
	int waveNumber = 1;
	int numOfZombies = 10;
	const float WAVE_DURATION = 30000.0;
	const float WAVE_COOLDOWN = 5000.0;

private:
	const int WAVE_INCREMENTER = 5;
	const double ZOMBIE_SPAWN_LOCATIONS[8][3] = {
		{ 58.1947, 1, -78.1053 },
		{ 57.9937, 1, -0.951329 },
		{ 28.5384, 1, -0.993304 },
		{ 13.5043, 1, -20.5573 },
		{ 2.99109, 1, -1.35359 },
		{ 52.5862, 4.5, -52.8509 },
		{ 52.4732, 4.5, -12.8664 },
		{ 8.88614, 4.5, -12.8664 }
	};

};

#endif // !WAVE_H