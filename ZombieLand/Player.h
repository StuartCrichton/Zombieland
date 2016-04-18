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

	bool getReloading();
	bool getcanShoot();
	float getPrevTime();
	void setReloading(bool reloading);
	void setcanShoot(bool canShoot);
	void setPrevTime(float previousTime);
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

	float previousTime = 0;
	bool reloading = false;
	bool canShoot = true;
};

