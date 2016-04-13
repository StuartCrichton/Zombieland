#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <GL/glut.h>
#include "AmmoBox.h"
#include <time.h>
#include "World.h"

using namespace std;

void AmmoBox::draw() {
	glPushMatrix();
	glTranslatef(pos.getX(), pos.getY(), pos.getZ());
	glScalef(0.1,0.1,0.1);
	this->world.ammoBox.Draw(2);
	glPopMatrix();
}

void AmmoBox::update() {
	unsigned int time_ui = unsigned int(time(NULL));
	srand(time_ui);
	int randomSpawnLocation = rand() % 6;

	pos = Vector(AMMO_BOX_SPAWN_LOCATIONS[randomSpawnLocation][0], AMMO_BOX_SPAWN_LOCATIONS[randomSpawnLocation][1], AMMO_BOX_SPAWN_LOCATIONS[randomSpawnLocation][2]);

	draw();
}

AmmoBox::AmmoBox()
{
	update();
}


AmmoBox::~AmmoBox()
{
}
