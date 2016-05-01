#pragma once
#include "Character.h"

using namespace std;

class Player : public Character
{
public:
	Player();
	~Player();
	void init();
	void setReloading(bool reloading);
	void setShooting(bool shooting);
	void setNoRel(bool noRel);
	void setNoShoot(bool noShoot);
	void setPrevTimeRel(float previousTimeRel);
	void setPrevTimeShoot(float previousTimeShoot);
	void setWaveNumber(int waveNumber);
	void rotateY(int angle);
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	void lookAround(int x, int y);
	void lookAt();
	void shoot();
	void reload();
	void takeDamage();
	void regainHealth();
	void scoreUp();
	void AmmoPickup();
	
	bool getReloading();
	bool getShooting();
	bool getNoRel();
	bool getNoShoot();
	float getPhi();
	float getPrevTimeRel();
	float getPrevTimeShoot();
	int getScore();
	int getHealth();
	int getAmmoCartridge();
	int getAmmoTotal();
	int getWaveNumber();

private:
	bool warped = false;
	int health = 100;
	int xOrigin = 0;
	int yOrigin = 0;
	int ammoCartridge = 11;
	int ammoCartridgeTotal = 11;
	int ammoTotal = 44;
	int waveNumber = 1;
	int score = 0;

	float previousTimeRel = 0;
	float previousTimeShoot = 0;
	bool reloading = false;
	bool shooting = false;
	bool noRel = true;
	bool noShoot = true;
};

