#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <GL/glut.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include "Player.h"
#include <vector>
#include "Zombie.h"
#include <algorithm>
#include <iostream>
#include "World.h"
#include "Vector.h"
#include "HUD.h"
#include "Ray.h"
#include "Wave.h";
#include "AmmoBox.h"
#include <SFML/Audio.hpp>
#include "ParticleEffect.h"
#include "MuzzleFlash.h"
#include "KeyEvent.h"
#include "MuzzleFlash.h"
#include "Lighting.h"

using namespace std;
// Global variables
bool roof = false;
bool gameOver = false;
bool canMove = true;

Lighting light;

//Necessary pointers and classes
Player *player = new Player();
World world;
Vector v;
vector<CollisionPlane*>* planes;
HUD *hud = new HUD(player->getHealth(), player->getAmmoCartridge(), player->getAmmoTotal(),
	player->getScore(), player->getWaveNumber(), player->getPosition(), player->getLookVector());

//Stuff pertaining to audio
sf::Music music; 
sf::Music music2; 

int dimx = 60;
int dimz = 80;
GLfloat light_position[] = { dimx + 10, 10, -dimz - 10,0.0 };
GLfloat light_position1[] = { -dimx + 5, 10, dimz - 5, 1.0 };
GLfloat light_position2[] = { dimx / 2 , 30, -(dimz / 2),1.0 };
GLfloat light_position3[] = { dimx / 2, -50, -(dimz / 2), 1.0 };



//Stuff pertraining to the wave
Wave *wave;
float currentTimerDuration;
int timerInterval;
int numOfKilledZombies = 0;
bool isWave = true;

//Stuff pertaining to particles
ParticleEffect *bloodSplatter;
MuzzleFlash *muzzleFlash;

//Stuff pertaining to ammo box
AmmoBox ammoBox;

//Multiple key pressed stuff
KeyEvent keyEvents;

void deletePointers() {
	for (unsigned i = wave->v_zombies.size() - 1; i >= 0; i--)
		delete wave->v_zombies[i];
	delete player;
	delete hud;
	delete bloodSplatter;
	delete muzzleFlash;
}

void initGL()
{
	// Set "clearing" or background color
	glClearColor(0, 0.1, 0.4, 1);

	glutSetCursor(GLUT_CURSOR_NONE);
	//glClearColor(0, 0, 0, 1); // White and opaque

	glEnable(GL_DEPTH_TEST); // turns on hidden surface removal so that objects behind other objects do not get displayed

	ammoBox.update();
}

void render()
{
	// GL_DEPTH_BUFFER_BIT - resets the depth test values for hidden surface removal
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set the camera
	player->lookAt();

	light.lightInitGL();

	//Draw the building
	GLfloat color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	world.building.Draw(1);
	/*vector<CollisionPlane*>* planes = world.getPlanes();
	for (CollisionPlane* p : *planes) {
	p->debug();
	}*/

	for (int i = 0; i < wave->v_zombies.size(); i++) {
		Vector v = wave->v_zombies[i]->update(player->getPosition(), player->floor);
		bool move = true;
		for (unsigned j = 0; j < wave->v_zombies.size(); j++) {
			if (i != j)
				if (wave->v_zombies[j]->mask.intersects(CollisionMask(v, 0.7))) {
					move = false;
					break;
				}
		}
		if (move)
			wave->v_zombies[i]->set(&v);
		wave->v_zombies[i]->render();
	}

	ammoBox.draw();

	//Draw the Gun
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(player->getPosition().getX(),
		player->getPosition().getY(), player->getPosition().getZ());
	glRotatef(-player->getThetha() * 180 / 3.14, 0, 1, 0);
	glTranslatef(0.2, 0, -0.2);
	glRotatef(player->getPhi() * 180 / 3.14, 1, 0, 0);
	glTranslatef(0, -0.3, 0);
	glScalef(0.001, 0.001, 0.001);
	world.gun.Draw(3);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

	int a;
	if (bloodSplatter != nullptr) {
		a = bloodSplatter->update();
		if (a == 1)
			bloodSplatter = nullptr;
	}

	int b = 0;
	if (muzzleFlash != nullptr) {
		b = muzzleFlash->update();
		if (b == 1)
			muzzleFlash = nullptr;
	}

	//update and display the HUD
	hud->update(player->getHealth(), player->getAmmoCartridge(), player->getAmmoTotal(), player->getScore(), player->getWaveNumber(), player->getPosition(), player->getLookVector());
	hud->render();

	glFlush();   // ******** DO NOT FORGET THIS **********
	glutSwapBuffers();
}

void display()
{
	if (!gameOver) {
		if (player->getPosition().getY() > 8.5) {
			//cout << "ROOF" << endl;
			music.stop();
			roof = true;
			hud->setRoof(roof);
		}
		else {
			//cout << "NOT ROOF" << endl;
			roof = false;
			hud->setRoof(roof);
		}

		if (player->getShooting() == true) {
			float newTimeShoot = glutGet(GLUT_ELAPSED_TIME);
			float difference = newTimeShoot - player->getPrevTimeShoot();
			//player->previousTime = newTime;
			//difference /= 1000;
			//cout << player->getcanShoot() << "   " << difference << endl;
			if (difference >= 300) {
				//cout << difference << endl;
				player->setNoShoot(true);
				player->setPrevTimeShoot(newTimeShoot);
				player->setShooting(false);
			}
		}
		if (player->getReloading() == true) {
			float newTimeRel = glutGet(GLUT_ELAPSED_TIME);
			float difference = newTimeRel - player->getPrevTimeRel();
			//player->previousTime = newTime;
			//difference /= 1000;
			//cout << player->getcanShoot() << "   " << difference << endl;
			if (difference >= 3500) {
				//cout << difference << endl;
				player->setNoRel(true);
				player->setPrevTimeRel(newTimeRel);
				player->setReloading(false);
			}
		}
		keyEvents.keyOperations();
	render();
}
	if (gameOver) {
		music.stop();
		music2.stop();
	}
	}

void reshape(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)	h = 1;

	GLfloat ratio = 1.0f * (GLfloat)w / (GLfloat)h;

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the clipping volume
	gluPerspective(45, ratio, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouseMove(int x, int y) {
	if (!gameOver)
	player->lookAround(x, y);
}

void mouseClick(int button, int state, int x, int y) {
	if (!gameOver) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (player->getAmmoCartridge() > 0)) {
			//if (player->getcanShoot() == true) {
			if (player->getNoRel() == true && player->getNoShoot() == true) {
				muzzleFlash = new MuzzleFlash(player);
				player->shoot();
				Ray ray(player->getPosition(), player->getUnitVector());
				float minDistance = 1000;
				unsigned minIndex = 1000;
				bool somethingDies = false;
				for (unsigned i = 0; i < wave->v_zombies.size(); i++) {
					if (ray.intersects(wave->v_zombies[i]->mask)) {
						bloodSplatter = new ParticleEffect(wave->v_zombies[i]->getPosition().getX(), wave->v_zombies[i]->getPosition().getY() + 1, wave->v_zombies[i]->getPosition().getZ(), 0.05, 1.0, 0.0, 0.0, 1000, 0.5);
						wave->v_zombies[i]->takeDamage();
						if (wave->v_zombies[i]->getHealth() == 0) {
							somethingDies = true;
						}
						float d = ray.getDistance();
						if (d < minDistance) {
							minDistance = d;
							minIndex = i;
						}
					}
						if (ray.intersects(wave->v_zombies[i]->head)) {
							bloodSplatter = new ParticleEffect(wave->v_zombies[i]->getPosition().getX(), wave->v_zombies[i]->getPosition().getY() + 1, wave->v_zombies[i]->getPosition().getZ(), 0.05, 1.0, 0.0, 0.0, 1000, 0.5);
							somethingDies = true;
							float d = ray.getDistance();
							if (d < minDistance) {
								minDistance = d;
								minIndex = i;
							}
						}
				}
				if (somethingDies) {
					//bufferDie.loadFromFile("../Dying.wav");
					//soundDie.play(); // Play the sound!
					numOfKilledZombies++;
					wave->v_zombies.erase(wave->v_zombies.begin() + minIndex);
					player->scoreUp();
				}
			}
		}
	}
}

void healthTimer(int value) {
	if (!gameOver) {
		player->regainHealth();
		glutTimerFunc(2000, healthTimer, 0);
	}
}

void WaveTimer(int value) {
	if (!gameOver) {
		/*
		If it is a wave, repeat at the zombie spawn interval
		*/
		if (isWave) {
			if (currentTimerDuration - timerInterval <= 0 && numOfKilledZombies == wave->numOfZombies) {
				currentTimerDuration = wave->WAVE_COOLDOWN;
				wave->incrementWaveNumber();
				numOfKilledZombies = 0;
				timerInterval = 1000;
				isWave = false;
			}
			else if (currentTimerDuration > 0) {
				wave->addNewZombie();
				currentTimerDuration -= wave->getZombieSpawnInterval();
			}
		}

		/*
		If it isn't a wave, repeat once every second
		*/
		else {
			if (currentTimerDuration - 1000 < 0) {
				currentTimerDuration = wave->WAVE_DURATION;
				timerInterval = wave->getZombieSpawnInterval();
				player->setWaveNumber(wave->waveNumber);
				hud->update(player->getHealth(), player->getAmmoCartridge(), player->getAmmoTotal(), player->getScore(), player->getWaveNumber(), player->getPosition(), player->getLookVector());
				isWave = true;
			}
			else {
				currentTimerDuration -= 1000;
			}
		}

		glutTimerFunc(timerInterval, WaveTimer, 0);
	}
}

void Timer(int t) {
	if (!gameOver) {
		player->lookAt();
		int health = player->getHealth();
		if (health == 0)
			gameOver = true;
		if (hud->getTimeUp() == true) {
			gameOver = true;
		}
		glutTimerFunc(20, Timer, 0);
	}
}

void ETATimer(int time) {
	if (!gameOver) {
		hud->updateETA();
		if (hud->getMinutes() == 0 && hud->getSeconds() == 0)
			return;
		glutTimerFunc(1000, ETATimer, 0);
	}
}

void keyPressed(unsigned char key, int x, int y) {
	if (key != 27) {
		keyEvents.keyStates[key] = true;
	}
	else {
		//deletePointers();
		exit(0);
	}
}

void keyUp(unsigned char key, int x, int y) {
	keyEvents.keyStates[key] = false;
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv)
{
	//cout << ammoBox.getLocation().getX() << endl;
	//cout << ammoBox.getLocation().getY() << endl;
	//cout << ammoBox.getLocation().getZ() << endl;
	music.openFromFile("../Horror-theme-song.wav");
	//music.play();
	music.setVolume(25);
	music.setLoop(true);

	music2.openFromFile("../Zombie-sound.wav");
	music2.setVolume(25);
	//music2.play();
	music2.setLoop(true);

	glutInit(&argc, argv);

	glutInitWindowSize(1024, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("ZombieLand Survivor");
	//glutFullScreen();
	world.init();
	wave = new Wave(&world);
	currentTimerDuration = wave->WAVE_DURATION;
	timerInterval = wave->getZombieSpawnInterval();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	keyEvents = KeyEvent(player, world, wave, &ammoBox);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMove);
	glutMotionFunc(mouseMove);

	glutTimerFunc(0, WaveTimer, 0);
	glutTimerFunc(0, healthTimer, 0);
	glutTimerFunc(2000, ETATimer, 0);
	glutTimerFunc(0, Timer, 0);
	//glutTimerFunc(1000, soundTimer, 0);

	initGL();

	glutMainLoop();
	deletePointers();

	return 0;
}

