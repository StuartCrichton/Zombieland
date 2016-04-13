
#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player();
	void setY(float x);
	void init();
	void lookUp();
	void rotateY(int angle);
	void lookDown();
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	void lookAround(int x, int y);
	void jump();
	void crouch();
	void lookAt();
	void shoot();
	void takeDamage();
	void regainHealth();
	void scoreUp();
	int getHealth();
	int getAmmoCartridge();
	int getAmmoTotal();
	int getWaveNumber();
	void setWaveNumber(int waveNumber);
	int getScore();
	virtual ~Player();

protected:

private:
	bool warped = false;
	int health = 100;
	int xOrigin = 0;
	int yOrigin = 0;
	int ammoCartridge = 33;
	int ammoCartridgeTotal = 33;
	int ammoTotal = 99;
	int waveNumber = 1;
	int score = 0;
	bool crouched = false;
};

