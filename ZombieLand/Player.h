#pragma once
#include "Character.h"

using namespace std;

class Player : public Character
{
public:
	Player();
	void setY(float x);
	void init();
	void rotateY(int angle);
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	void lookAround(int x, int y);
	void jump();
	void crouch();
	void lookAt();
	void shoot();
	void reload();
	void takeDamage();
	void regainHealth();
	void scoreUp();
	int getHealth();
	int getAmmoCartridge();
	int getAmmoTotal();
	int getWaveNumber();
	void setWaveNumber(int waveNumber);
	int getScore();
	float getPhi();
	void AmmoPickup();
	bool getCanShoot();
	void setCanShoot(bool canShoot);
	virtual ~Player();

protected:

private:
	bool warped = false;
	bool canShoot = true;
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

