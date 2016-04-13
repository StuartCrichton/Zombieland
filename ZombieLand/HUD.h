#pragma once
using namespace std;

class HUD {
public:
	HUD();
	HUD(int health, int ammoCartridge, int ammoTotal, int score, int waveNumber);
	void update(int health, int ammoCartridge, int ammoTotal, int score, int waveNumber);
	void render();

private:
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

