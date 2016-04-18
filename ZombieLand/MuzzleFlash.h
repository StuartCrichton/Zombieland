#pragma once
#include "Player.h"

class MuzzleFlash
{
public:
	MuzzleFlash();
	~MuzzleFlash();
	int update();
private:
	void draw();
	Player player;
	float muzzleFlashLength = 0;
	float muzzleFlashRadius = 0;
	float currentTime;
	float previousTime;
};

