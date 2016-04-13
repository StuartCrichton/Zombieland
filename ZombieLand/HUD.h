#pragma once
#ifndef HUD_H
#define HUD_H
#include "Vector.h"
#include "World.h"

using namespace std;

class HUD {
public:
	HUD();
	HUD(int health, int ammoCartridge, int ammoTotal, int score, int waveNumber, Vector pos_v, Vector look_v);
	void update(int health, int ammoCartridge, int ammoTotal, int score, int waveNumber, Vector pos_v, Vector look_v);
	void render();

private:
	Vector pos_v, look_v;
	World world;
	int health = 100, ammoCartridge = 33, ammoTotal = 99, score = 0, waveNumber = 1;
	void renderGun();
	void renderCrosshair();
	void renderHealth();
	void renderTotalAmmo();
	void renderCurrentAmmo();
	void renderScoreText();
	void renderScore();
	void renderWaveText();
	void renderWave();
};

#endif //HUD_H