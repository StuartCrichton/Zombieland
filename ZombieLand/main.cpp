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
//#include "Ray.h"
#include "Bullet.h"
#include "Wave.h";
#include "AmmoBox.h"
#include <SFML/Audio.hpp>
#include "ParticleEffect.h"
#include "MuzzleFlash.h"
#include "KeyEvent.h"
#include "MuzzleFlash.h"
#include "Lighting.h"
#include "Imageloader.h"

using namespace std;
// Global variables
bool roof = false;
bool gameOver = false;
bool canMove = true;

Lighting light;

//Necessary pointers and classes
Player *player = new Player();
World *world = new World();
Vector v;
vector<CollisionPlane*>* planes;
Bullet* bullet;
HUD *hud = new HUD(player->getHealth(), player->getAmmoCartridge(), player->getAmmoTotal(),
	player->getScore(), player->getWaveNumber(), player->getPosition(), player->getLookVector());

//Stuff pertaining to audio
sf::Music music;
sf::Music music2;

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
KeyEvent *keyEvents;

void deletePointers() {
	delete player;
	delete wave;
	delete world;
	delete hud;
	delete bullet;	
	delete bloodSplatter;
	delete muzzleFlash;
	delete keyEvents;	
}

void initGL()
{
	glClearColor(0, 0.1, 0.4, 1);

	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_DEPTH_TEST);

	ammoBox.update();
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture

void initRendering() {
	glEnable(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_NORMALIZE);
	//glEnable(GL_COLOR_MATERIAL);

	//	Image* image = loadBMP("../sky_103.bmp");
	Image* image = loadBMP("../sky.bmp");
	_textureId = loadTexture(image);
	delete image;
}

void render()
{
	// GL_DEPTH_BUFFER_BIT - resets the depth test values for hidden surface removal
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat ambient1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient1);

	// Set the camera
	player->lookAt();

	light.lightInitGL();

	//Sky Texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.5f, 0.5f, 0.5f);
	glDisable(GL_LIGHTING);

	int xgap = 100;
	int zgap = 100;
	int x = 180;
	int z = -200;
	GLfloat color2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glBegin(GL_QUADS);
	for (int i = 0; i < 3; i++) {//z
		for (int j = 0; j < 4; j++) {//x
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f((x - (j*xgap)), 12.0f, z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f((x - (j*xgap)) - xgap, 12.0f, z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f((x - (j*xgap)) - xgap, 12.0f, z + zgap);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f((x - (j*xgap)), 12.0f, z + zgap);
		}
		z = z + zgap;
	}	glEnd();

	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//light.lightInitGL();

	//Draw the building
	GLfloat color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	world->building.Draw(1);

	//draw bullets
	if(bullet != nullptr) {
		/////////////////////////////////////////////create series of spheres 
		for (int i = 0; i < 30; i++)//check 20 tiny steps of bullet
		{
			if (bullet != nullptr) {
				bullet->update();
				if (bullet->getSteps() < 800) {
					for (unsigned j = 0; j < wave->v_zombies.size(); j++) {
						if (bullet->mask.intersects(wave->v_zombies[j]->head)) {
							bloodSplatter = new ParticleEffect(bullet->getPosition().getX(), bullet->getPosition().getY(), bullet->getPosition().getZ(), 0.05, 1.0, 0.0, 0.0, 1000, 0.5);
							delete bullet;
							bullet = nullptr;
							delete wave->v_zombies[j];
							numOfKilledZombies++;
							wave->v_zombies.erase(wave->v_zombies.begin() + j);
							player->scoreUp();
							break;
						}
						else if (bullet->mask.intersects(wave->v_zombies[j]->mask)) {
							bloodSplatter = new ParticleEffect(bullet->getPosition().getX(), bullet->getPosition().getY(), bullet->getPosition().getZ(), 0.05, 1.0, 0.0, 0.0, 1000, 0.5);
							delete bullet;
							bullet = nullptr;
							wave->v_zombies[j]->takeDamage();
							if (wave->v_zombies[j]->getHealth() == 0) {
								delete wave->v_zombies[j];
								numOfKilledZombies++;
								wave->v_zombies.erase(wave->v_zombies.begin() + j);
								player->scoreUp();
							}
							break;
						}
					}
				}
				else {
					delete bullet;
					bullet = nullptr;
				}
			}
		}
		if (bullet!=nullptr)
			bullet->render();
	}


	for (int i = 0; i < wave->v_zombies.size(); i++) {
		Vector v = wave->v_zombies[i]->update(player->getPosition(), player->floor);
		if (v == wave->v_zombies[i]->getPosition()) {
			player->takeDamage();
		}
		bool move = true;
		for (unsigned j = 0; j < wave->v_zombies.size(); j++) {
			if (i != j)
				if (wave->v_zombies[j]->mask.intersects(CollisionMask(v, 0.7))) {
					move = false;
					//wave->v_zombies[j]->moveBackward(1);
					break;
				}
		}
		if (move)
			wave->v_zombies[i]->set(&v);
		wave->v_zombies[i]->render();
	}


	//debug ray cast
	/*glPushMatrix();
	glTranslatef(player->getPosition().getX() + 20 * player->getUnitVector().getX(),
		player->getPosition().getY() + 20 * player->getUnitVector().getY(),
		player->getPosition().getZ() + 20 * player->getUnitVector().getZ());
	glutSolidSphere(1, 16, 16);
	glPopMatrix();*/


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
	world->gun.Draw(3);
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

	//light.lightInitGL();

	//glFlush();   // ******** DO NOT FORGET THIS **********
	glutSwapBuffers();
}

void display()
{
	if (!gameOver) {
		if (player->getPosition().getY() > 8.5) {
			roof = true;
			hud->setRoof(roof);
		}
		else {
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
				player->setNoRel(true);
				player->setPrevTimeRel(newTimeRel);
				player->setReloading(false);
			}
		}
		keyEvents->keyOperations();
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
			if (player->getNoRel() == true && player->getNoShoot() == true) {
				muzzleFlash = new MuzzleFlash(player);
				player->shoot();
				bullet = new Bullet(&player->getPosition(), &player->getUnitVector());
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
		if (key == 'w' || key == 'W')
			keyEvents->keyStates['w'] = true;
		else if (key == 'a' || key == 'A')
			keyEvents->keyStates['a'] = true;
		else if (key == 's' || key == 'S')
			keyEvents->keyStates['s'] = true;
		else if (key == 'd' || key == 'D')
			keyEvents->keyStates['d'] = true;
		else if (key == 'r' || key == 'R')
			keyEvents->keyStates['r'] = true;
	}
	else {
		deletePointers();
		exit(0);
	}
}

void keyUp(unsigned char key, int x, int y) {
	if (key == 'w' || key == 'W')
		keyEvents->keyStates['w'] = false;
	else if (key == 'a' || key == 'A')
		keyEvents->keyStates['a'] = false;
	else if (key == 's' || key == 'S')
		keyEvents->keyStates['s'] = false;
	else if (key == 'd' || key == 'D')
		keyEvents->keyStates['d'] = false;
	else if (key == 'r' || key == 'R')
		keyEvents->keyStates['r'] = false;
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv)
{
	//cout << ammoBox.getLocation().getX() << endl;
	//cout << ammoBox.getLocation().getY() << endl;
	//cout << ammoBox.getLocation().getZ() << endl;
	music.openFromFile("../Horror-theme-song.wav");
	music.play();
	music.setVolume(25);
	music.setLoop(true);

	music2.openFromFile("../Zombie-sound.wav");
	music2.setVolume(25);
	music2.play();
	music2.setLoop(true);

	glutInit(&argc, argv);

	glutInitWindowSize(1024, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("ZombieLand Survivor");
	glutFullScreen();

	initRendering();

	world->init();
	wave = new Wave(world);
	currentTimerDuration = wave->WAVE_DURATION;
	timerInterval = wave->getZombieSpawnInterval();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	keyEvents = new KeyEvent(player, world, wave, &ammoBox);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMove);
	glutMotionFunc(mouseMove);

	glutTimerFunc(0, WaveTimer, 0);
	glutTimerFunc(0, healthTimer, 0);
	glutTimerFunc(1000, ETATimer, 0);
	glutTimerFunc(0, Timer, 0);
	//glutTimerFunc(1000, soundTimer, 0);

	initGL();

	glutMainLoop();
	deletePointers();

	return 0;
}

