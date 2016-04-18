#pragma once
#include "Player.h"

class MuzzleFlash
{
public:
	MuzzleFlash(Player *player);
	~MuzzleFlash();
	int update();
private:
	void draw();
	float muzzleFlashLength = 0;
	float muzzleFlashRadius = 0;
	float currentTime;
	float previousTime;
	Player *player;
};

