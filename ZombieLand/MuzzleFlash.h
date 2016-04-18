#pragma once
#include "Player.h"

class MuzzleFlash
{
public:
	MuzzleFlash(float x, float y, float z, float thetha, float phi);
	~MuzzleFlash();
	int update();
private:
	void draw();
	Player player;
	float muzzleFlashLength = 0;
	float muzzleFlashRadius = 0;
	float currentTime;
	float previousTime;
	float xPos;
	float yPos;
	float zPos;
	float thetha;
	float phi;
};

