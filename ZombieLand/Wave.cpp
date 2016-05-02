#include "Wave.h"
#include "Zombie.h"
#include <vector>
#include <GL/glut.h>
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <time.h>

using namespace std;


void Wave::addNewZombie()
{
	unsigned int time_ui = unsigned int(time(NULL));
	srand(time_ui);
	int randomSpawnLocation = rand() % 8;

	Zombie *zombie = new Zombie(ZOMBIE_SPAWN_LOCATIONS[randomSpawnLocation][0], ZOMBIE_SPAWN_LOCATIONS[randomSpawnLocation][1], ZOMBIE_SPAWN_LOCATIONS[randomSpawnLocation][2], this->world);
	v_zombies.push_back(zombie);

}

void Wave::incrementWaveNumber()
{
	this->waveNumber++;
	this->numOfZombies += this->WAVE_INCREMENTER;
}

int Wave::getZombieSpawnInterval()
{
	int zombieSpawnInterval = this->WAVE_DURATION / this->numOfZombies;

	return zombieSpawnInterval;
}

Wave::Wave(World* w)
{
	this->world = w;
}

Wave::~Wave()
{
	while (v_zombies.size() > 0) {
		delete v_zombies[0];
		v_zombies.erase(v_zombies.begin(), v_zombies.begin() + 1);
	}
}
