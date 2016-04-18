#include "MuzzleFlash.h"
#include <GL/glut.h>
#include <iostream>

void MuzzleFlash::draw() {
	glPushMatrix();
	glTranslatef(player->getPosition().getX(), player->getPosition().getY(), player->getPosition().getZ());
	glRotatef(-player->getThetha() * 180 / 3.14, 0, 1, 0);
	glTranslatef(0.2, 0, -0.2);
	glRotatef(player->getPhi() * 180 / 3.14, 1, 0, 0);
	glTranslatef(0, -0.3, 0);
	float colour[4] = { 0.9f,0.9f,0.2f,0.2f };
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colour);
	glTranslatef(0, 0.15, (-3 - muzzleFlashLength));
	glutSolidCone(muzzleFlashRadius, muzzleFlashLength, 16, 16);
	glPopMatrix();

	glDisable(GL_BLEND);
}

int MuzzleFlash::update() {
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	float difference = currentTime - previousTime;
	if (difference > 300) {
		return 1;
	}
	else {
		muzzleFlashLength += 0.1;
		muzzleFlashRadius += 0.05;
	}

	draw();
}

MuzzleFlash::MuzzleFlash(Player *player)
{
	this->player = player;
	previousTime = glutGet(GLUT_ELAPSED_TIME);
}


MuzzleFlash::~MuzzleFlash()
{
}
