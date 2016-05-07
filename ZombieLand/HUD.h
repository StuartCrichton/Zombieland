#pragma once
#ifndef HUD_H
#define HUD_H
#include "Vector.h"

using namespace std;

class HUD {
public:
	HUD();
	HUD(int health, int ammoCartridge, int ammoTotal, int score, int waveNumber, Vector pos_v, Vector look_v);
	~HUD();
	void update(int health, int ammoCartridge, int ammoTotal, int score, int waveNumber, Vector pos_v, Vector look_v);
	int getSeconds();
	int getMinutes();
	bool getTimeUp();
	void render();
	void updateETA();
	void renderEndGameScreen();
	void setRoof(bool roof);
private:
	Vector pos_v, look_v;
	int health = 100, ammoCartridge = 11, ammoTotal = 44, score = 0, waveNumber = 1;
	int minutes = 0;
	int seconds = 30;
	bool roof = false;
	bool timeUp = false;
	void renderCrosshair();
	void renderHealth();
	void renderTotalAmmo();
	void renderCurrentAmmo();
	void renderScoreText();
	void renderScore();
	void renderWaveText();
	void renderWave();
	void renderETAText();
	void renderETA();
};

#endif //HUD_H