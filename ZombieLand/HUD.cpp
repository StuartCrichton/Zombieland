#include "HUD.h"
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <SFML/Audio.hpp>

using namespace std;

sf::SoundBuffer bufferEnd;
sf::Sound soundEnd(bufferEnd);

HUD::HUD() {

}

HUD::HUD(int health, int ammoCartridge, int ammoTotal, int score, int waveNumberrender, Vector pos_v, Vector look_v) {
	this->health = health;
	this->ammoCartridge = ammoCartridge;
	this->ammoTotal = ammoTotal;
	this->score = score;
	this->waveNumber = waveNumber;
	this->pos_v = pos_v;
	this->look_v = look_v;
}

void HUD::update(int health, int ammoCartridge, int ammoTotal, int score, int waveNumber, Vector pos_v, Vector look_v) {
	this->health = health;
	this->ammoCartridge = ammoCartridge;
	this->ammoTotal = ammoTotal;
	this->score = score;
	this->waveNumber = waveNumber;
	this->pos_v = pos_v;
	this->look_v = look_v;
}

bool HUD::getTimeUp() {
	return timeUp;
}
void HUD::setRoof(bool roof) {
	this->roof = roof;
}
int HUD::getSeconds() {
	return seconds;
}

int HUD::getMinutes() {
	return minutes;
}

void HUD::updateETA()
{
	if (seconds == 0) {
		this->minutes--;
		this->seconds = 59;
	}
	else
		this->seconds--;
	//this->seconds--;
}

void HUD::renderCrosshair() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Draw the crosshair
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2.0f - 10.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2.0f - 30.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2.0f + 10.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2.0f + 30.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f - 10.0f);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f - 30.0f);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f + 10.0f);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2.0f, glutGet(GLUT_WINDOW_HEIGHT) / 2.0f + 30.0f);
	glEnd();

	//Reset Colors
	glColor3f(0.0f, 1.0f, 0.3f);
	glPopMatrix();

	//Reset 3D
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void HUD::renderHealth() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Draw the health text
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslated(glutGet(GLUT_WINDOW_WIDTH) - 70, glutGet(GLUT_WINDOW_HEIGHT) - 5, 0);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	string healthString = to_string(this->health);
	for (unsigned i = 0; i < healthString.size(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, healthString[i]);
	}

	//Reset Colors
	glColor3f(0.0f, 1.0f, 0.3f);
	glPopMatrix();

	//Reset 3D
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void HUD::renderTotalAmmo() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Draw the ammo text
	glColor3f(0.0f, 0.5f, 1.0f);
	glTranslated(glutGet(GLUT_WINDOW_WIDTH) - 70, glutGet(GLUT_WINDOW_HEIGHT) - 55, 0);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	string ammoTotal = "/" + to_string(this->ammoTotal);
	for (unsigned i = 0; i < ammoTotal.size(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, ammoTotal[i]);
	}

	//Reset Colors
	glColor3f(0.0f, 1.0f, 0.3f);
	glPopMatrix();

	//Reset 3D
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void HUD::renderCurrentAmmo() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Draw the ammo text
	glColor3f(0.0f, 1.0f, 1.0f);
	glTranslated(glutGet(GLUT_WINDOW_WIDTH) - 110, glutGet(GLUT_WINDOW_HEIGHT) - 55, 0);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	string currentAmmo = to_string(this->ammoCartridge);
	for (unsigned i = 0; i < currentAmmo.size(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, currentAmmo[i]);
	}

	//Reset Colors
	glColor3f(0.0f, 1.0f, 0.3f);
	glPopMatrix();

	//Reset 3D
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void HUD::renderScoreText() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Draw the score text
	glColor3f(0.0f, 1.0f, 1.0f);
	glTranslated(0, 40, 0);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	string score = "Score:";
	for (unsigned i = 0; i < score.size(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, score[i]);
	}

	//Reset Colors
	glColor3f(0.0f, 1.0f, 0.3f);
	glPopMatrix();

	//Reset 3D
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void HUD::renderScore() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Draw the score
	glColor3f(0.2f, 1.0f, 0.0f);
	glTranslated(110, 40, 0);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	string score = to_string(this->score);
	for (unsigned i = 0; i < score.size(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, score[i]);
	}

	//Reset Colors
	glColor3f(0.0f, 1.0f, 0.3f);
	glPopMatrix();

	//Reset 3D
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void HUD::renderWaveText() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Draw the wave text
	glColor3f(0.0f, 1.0f, 1.0f);
	glTranslated(glutGet(GLUT_WINDOW_WIDTH) - 150, 40, 0);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	string waveText = "Wave:";
	for (unsigned i = 0; i < waveText.size(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, waveText[i]);
	}

	//Reset Colors
	glColor3f(0.0f, 1.0f, 0.3f);
	glPopMatrix();

	//Reset 3D
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void HUD::renderWave() {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Draw the wave number
	glColor3f(0.2f, 1.0f, 0.0f);
	glTranslated(glutGet(GLUT_WINDOW_WIDTH) - 50, 40, 0);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	string wave = to_string(this->waveNumber);
	for (unsigned i = 0; i < wave.size(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, wave[i]);
	}

	//Reset Colors
	glColor3f(0.0f, 1.0f, 0.3f);
	glPopMatrix();

	//Reset 3D
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void HUD::renderETAText()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Draw the Timer text
	glColor3f(0.0f, 1.0f, 1.0f);
	glTranslated(glutGet(GLUT_WINDOW_WIDTH) - 180, 100, 0);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	string extractionText = "ETA:";
	for (unsigned i = 0; i < extractionText.size(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, extractionText[i]);
	}

	//Reset Colors
	glColor3f(0.0f, 1.0f, 0.3f);
	glPopMatrix();

	//Reset 3D
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void HUD::renderETA()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Draw the count down timer
	if (minutes > 0) {
		glColor3f(0.2f, 1.0f, 0.0f);
	}else{
		if (seconds <= 30) 
			glColor3f(1.0f, 0.0f, 0.0f);
	}
	
	glTranslated(glutGet(GLUT_WINDOW_WIDTH) - 100, 100, 0);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	string timer;
	if (seconds == 0)
		timer = to_string(this->minutes) + ":" + to_string(this->seconds) + "0";
	else
		timer = to_string(this->minutes) + ":" + to_string(this->seconds);
	if (minutes != 10)
		if (seconds < 10)
			timer = "0" + to_string(this->minutes) + ":0" + to_string(this->seconds);
		else
			timer = "0" + to_string(this->minutes) + ":" + to_string(this->seconds);
	for (unsigned i = 0; i < timer.size(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, timer[i]);
	}

	if (minutes == 0 && seconds == 0)
		timeUp = true;
	//Reset Colors
	glColor3f(0.0f, 1.0f, 0.3f);
	glPopMatrix();

	//Reset 3D
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void HUD::renderEndGameScreen()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2d(0.0, 0.0);
	glVertex2d(glutGet(GLUT_WINDOW_WIDTH), 0.0);
	glVertex2d(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glVertex2d(0.0, glutGet(GLUT_WINDOW_HEIGHT));
	glVertex2d(0.0, 0.0);
	glEnd();

	//Draw the game over text
	//glColor3f(1.0f, 0.0f, 0.0f);
	glTranslated((glutGet(GLUT_WINDOW_WIDTH) / 2.0) - 100.0, glutGet(GLUT_WINDOW_HEIGHT) / 2.0, 0);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	string gameover;
	if (roof) {
		gameover = "You Win";
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (!roof || health == 0) {
		gameover = "Game Over";
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	for (unsigned i = 0; i < gameover.size(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, gameover[i]);
	}

	//Reset Colors
	glColor3f(0.0f, 1.0f, 0.3f);
	glPopMatrix();

	//Reset 3D
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void HUD::render() {
	renderCrosshair();
	renderHealth();
	renderCurrentAmmo();
	renderTotalAmmo();
	renderScoreText();
	renderScore();
	renderWaveText();
	renderWave();
	renderETAText();
	renderETA();
	if (health == 0 || timeUp) {
		renderEndGameScreen();
		if(roof)
			bufferEnd.loadFromFile("../You_Win.wav");
		else if (!roof || health == 0) 
		bufferEnd.loadFromFile("../GAME OVER.wav");
		soundEnd.play();
	}
}
