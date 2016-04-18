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

using namespace std;
// Global variables

//bool canShoot = true;
Player *player = new Player();
World world;
Vector v;
bool canMove = true; //keeps track if a character can move for collision detection
vector<CollisionPlane*>* planes;
HUD *hud = new HUD(player->getHealth(), player->getAmmoCartridge(), player->getAmmoTotal(),
	player->getScore(), player->getWaveNumber(), player->getPosition(), player->getLookVector());

//sf::SoundBuffer bufferShot;
//sf::Sound soundShot(bufferShot);

int dimx = 60;
int dimz = 80;
GLfloat light_position[] = { dimx + 10, 10, -dimz - 10,0.0 };
GLfloat light_position1[] = { -dimx + 5, 10, dimz - 5, 1.0 };
GLfloat light_position2[] = { dimx / 2 , 30, -(dimz / 2),1.0 };
GLfloat light_position3[] = { dimx / 2, -50, -(dimz / 2), 1.0 };

//Stuff pertraining to the wave
Wave *wave = new Wave();
float currentTimerDuration = wave->WAVE_DURATION;
int timerInterval = wave->getZombieSpawnInterval();
int numOfKilledZombies = 0;
bool isWave = true;

//Stuff pertaining to particles
ParticleEffect *bloodSplatter;
MuzzleFlash *muzzleFlash;

//Stuff pertaining to ammo box
AmmoBox ammoBox;

//Multiple key pressed stuff
KeyEvent keyEvents;

void initGL()
{
	// Set "clearing" or background color
	glClearColor(0, 0.1, 0.4, 1);
	glutSetCursor(GLUT_CURSOR_NONE);
	//glClearColor(0, 0, 0, 1); // White and opaque

	glEnable(GL_LIGHTING); // turns on the lighting model in OpenGL

	GLfloat diffuse0[] = { 0.9, 0.9, 0.9, 1.0 };

	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambient[] = { 1.0,1.0,1.0,1 };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);

	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular);


	GLfloat ambientColor[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	GLfloat mat_amb[] = { 1.0,1.0,1.0,1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);

	glEnable(GL_LIGHT0);//corner1
	glEnable(GL_LIGHT1);//middle
	glEnable(GL_LIGHT2);//corner2
	glEnable(GL_LIGHT3);//below

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

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);

	//Draw the building
	GLfloat color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	world.building.Draw(1);
	/*vector<CollisionPlane*>* planes = world.getPlanes();
	for (CollisionPlane* p : *planes) {
	p->debug();
	}*/

	for (int i = 0; i < wave->v_zombies.size(); i++) {
		wave->v_zombies[i]->render(player->getPosition());
	}

	ammoBox.draw();

	/*cout << player.getPosition().getX() << " "
	<< player.getPosition().getY() << " "
	<< player.getPosition().getZ() << endl;*/

	//glRotatef(player.getThetha(), 0, 1, 0);
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

	//update and display the HUD
	hud->update(player->getHealth(), player->getAmmoCartridge(), player->getAmmoTotal(), player->getScore(), player->getWaveNumber(), player->getPosition(), player->getLookVector());
	hud->render();

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

	glFlush();   // ******** DO NOT FORGET THIS **********
}
void display()
{
	if (player->getReloading() == true) {
		float newTime = glutGet(GLUT_ELAPSED_TIME);
		float difference = newTime - player->getPrevTime();
		//player->previousTime = newTime;
		//difference /= 1000;
		cout << player->getcanShoot() << "   " << difference << endl;
		if (difference >= 3500) {
			//cout << difference << endl;
			player->setcanShoot(true);
			player->setPrevTime(newTime);
			player->setReloading(false);
		}
	}
	render();
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

void idle() {
	player->lookAt(); // called when there is now other event
	int health = player->getHealth();
	if (health == 0) {
		exit(0);
	}
}

void mouseMove(int x, int y) {
	player->lookAround(x, y);
}

void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (player->getAmmoTotal() > 0 || player->getAmmoCartridge() > 0)) {
		if (player->getcanShoot() == true) {
			muzzleFlash = new MuzzleFlash(player);
			player->shoot();
			Ray ray(player->getPosition(), player->getUnitVector());
			float minDistance = 1000;
			unsigned minIndex = 1000;
			bool somethingDies = false;
			for (unsigned i = 0; i < wave->v_zombies.size(); i++) {
				if (ray.intersects(wave->v_zombies[i]->mask)) {
					bloodSplatter = new ParticleEffect(wave->v_zombies[i]->getPosition().getX(), wave->v_zombies[i]->getPosition().getY(), wave->v_zombies[i]->getPosition().getZ(), 0.05, 1.0, 0.0, 0.0, 1000, 0.5);
					somethingDies = true;
					float d = ray.getDistance();
					if (d < minDistance) {
						minDistance = d;
						minIndex = i;
					}
				}
			}
			if (somethingDies) {
				//	bufferShot.loadFromFile("../Zombie In Pain.wav");
				//soundShot.play(); // Play the sound!
				numOfKilledZombies++;
				wave->v_zombies.erase(wave->v_zombies.begin() + minIndex);
				player->scoreUp();
			}
		}
	}
}

void healthTimer(int value) {
	player->regainHealth();
	glutTimerFunc(1000, healthTimer, 0);
}

void WaveTimer(int value) {
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

void Timer(int t) {
	player->lookAt();
	glutTimerFunc(20, Timer, 0);
}

 //void shootTimer(int value) {
//	player->setShoot();
//}


void keyPressed(unsigned char key, int x, int y) {
	keyEvents.keyStates[key] = true;
	keyEvents.keyOperations();
}

void keyUp(unsigned char key, int x, int y) {
	keyEvents.keyStates[key] = false;
	keyEvents.keyOperations();
}

void deletePointers() {
	for (unsigned i = wave->v_zombies.size()-1; i >= 0; i--)
		delete wave->v_zombies[i];
	delete player;
	player = NULL;
	delete hud;
	hud = NULL;
	delete bloodSplatter;
	bloodSplatter = NULL;
	delete muzzleFlash;
	muzzleFlash = NULL;
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv)
{

	sf::Music music;
	music.openFromFile("../Horror-theme-song.wav");
	music.play();
	music.setLoop(true);

	sf::Music music2;
	music2.openFromFile("../Zombie-sound.wav");
	music2.play();
	music2.setLoop(true);

	glutInit(&argc, argv);

	glutInitWindowSize(1024, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("ZombieLand Survivor");
	//glutFullScreen();
	world.init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	keyEvents = KeyEvent(player, world, wave);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(0, WaveTimer, 0);
	glutTimerFunc(0, healthTimer, 0);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMove);
	glutMotionFunc(mouseMove);

	glutTimerFunc(0, Timer, 0);
	initGL();

	glutMainLoop();
	deletePointers();

	return 0;
}

