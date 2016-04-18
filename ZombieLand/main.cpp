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
#include "KeyEvent.h"

using namespace std;
// Global variables


Player player;
World world;
Vector v;
bool canMove = true; //keeps track if a character can move for collision detection
vector<CollisionPlane*>* planes;
HUD *hud = new HUD(player.getHealth(), player.getAmmoCartridge(), player.getAmmoTotal(),
	player.getScore(), player.getWaveNumber(), player.getPosition(), player.getLookVector());

sf::SoundBuffer bufferGun;
sf::Sound soundGun(bufferGun);

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
ParticleEffect *muzzleFlash;

//Stuff pertaining to ammo box
AmmoBox ammoBox;

//Multiple key pressed stuff
//KeyEvent keyEvents = KeyEvent(player, world, wave);

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

void MuzzleFlash() {
	glPushMatrix();
	glTranslatef(player.getPosition().getX(),
		player.getPosition().getY(), player.getPosition().getZ());
	glRotatef(-player.getThetha() * 180 / 3.14, 0, 1, 0);
	glTranslatef(0.2, 0, -0.2);
	glRotatef(player.getPhi() * 180 / 3.14, 1, 0, 0);
	glTranslatef(0, -0.3, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float colour[4] = { 0.9f,0.9f,0.2f,0.001f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colour);
	glTranslatef(0, 0.15, -3);
	glutSolidCone(0.1,0.5,16,16);
	glPopMatrix();

	glDisable(GL_BLEND);
}

void render()
{
	// GL_DEPTH_BUFFER_BIT - resets the depth test values for hidden surface removal
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set the camera
	player.lookAt();

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);

	//Draw the building
	GLfloat color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	world.building.Draw(1);
	vector<CollisionPlane*>* planes = world.getPlanes();
	/*for (CollisionPlane* p : *planes) {
		p->debug();
	}*/

	for (int i = 0; i < wave->v_zombies.size(); i++) {
		wave->v_zombies[i]->render(player.getPosition());
	}

	ammoBox.draw();

	/*cout << player.getPosition().getX() << " "
		<< player.getPosition().getY() << " "
		<< player.getPosition().getZ() << endl;*/

		//glRotatef(player.getThetha(), 0, 1, 0);
	glPushMatrix();
	glTranslatef(player.getPosition().getX(),
		player.getPosition().getY(), player.getPosition().getZ());
	glRotatef(-player.getThetha() * 180 / 3.14, 0, 1, 0);
	glTranslatef(0.2, 0, -0.2);
	glRotatef(player.getPhi() * 180 / 3.14, 1, 0, 0);
	glTranslatef(0, -0.3, 0);
	glScalef(0.001, 0.001, 0.001);
	world.gun.Draw(3);
	glPopMatrix();

	//update and display the HUD
	hud->update(player.getHealth(), player.getAmmoCartridge(), player.getAmmoTotal(), player.getScore(), player.getWaveNumber(), player.getPosition(), player.getLookVector());
	hud->render();

	int a = 0;
	int b = 0;
	if (bloodSplatter != nullptr) {
		a = bloodSplatter->update();
		if (a == 1)
			bloodSplatter = nullptr;
	}

	if (muzzleFlash != nullptr) {
		b = muzzleFlash->update();
		if (b == 1)
			muzzleFlash = nullptr;
	}

	glFlush();   // ******** DO NOT FORGET THIS **********
}
void display()
{
	//keyEvents.keyOperations();
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
	player.lookAt(); // called when there is now other event
	int health = player.getHealth();
	if (health == 0) {
		exit(0);
	}
}

void processNormalKeys(unsigned char key, int x1, int y1) {
	/*For keys w,a,s,d simple collision detection is used
	* -The objects mask is updated based on the direction it wants to move
	* -canMove is set to true and only changed if the new mask collides with another object
	* -If the player can move, the apprpriate move method is called
	* -Else the player's mask is reset to before moving
	*/
	float x = player.getPosition().getX();
	float y = player.getPosition().getY();
	float z = player.getPosition().getZ();
	switch (key) {
	case 'r': player.init(); player.lookAt(); break; // shrink
	case 'w': v = player.getNewPosition(player.FORWARD);
		player.mask.update(v);
		canMove = true;
		for (unsigned i = 0; i < wave->v_zombies.size(); i++)
		{
			if (player.mask.intersects(wave->v_zombies[i]->mask)) {
				canMove = false;
				//player.takeDamage();
			}
		}
		planes = world.getPlanes();
		for (CollisionPlane* p : *planes) {
			if (player.mask.intersectsPlane(p)) {
				canMove = false;
			}
		}
		if (canMove)player.moveForward();
		else
			player.mask.update(player.getPosition());
		break; // expand
	case 's': v = player.getNewPosition(player.BACKWARD);
		player.mask.update(v);
		canMove = true;
		for (unsigned i = 0; i < wave->v_zombies.size(); i++)
		{
			if (player.mask.intersects(wave->v_zombies[i]->mask)) {
				canMove = false;
				//player.takeDamage();
			}
		}
		planes = world.getPlanes();
		for (CollisionPlane* p : *planes) {
			if (player.mask.intersectsPlane(p)) {
				canMove = false;
			}
		}
		if (canMove)player.moveBackward();
		else
			player.mask.update(player.getPosition());
		break;
	case 'a': v = player.getNewPosition(player.LEFT);
		player.mask.update(v);
		canMove = true;
		for (unsigned i = 0; i < wave->v_zombies.size(); i++)
		{
			if (player.mask.intersects(wave->v_zombies[i]->mask)) {
				canMove = false;
				//player.takeDamage();
			}
		}
		planes = world.getPlanes();
		for (CollisionPlane* p : *planes) {
			if (player.mask.intersectsPlane(p)) {
				canMove = false;
			}
		}
		if (canMove)player.strafeLeft();
		else
			player.mask.update(player.getPosition());
		break;
	case 'd': v = player.getNewPosition(player.RIGHT);
		player.mask.update(v);
		canMove = true;
		for (unsigned i = 0; i < wave->v_zombies.size(); i++)
		{
			if (player.mask.intersects(wave->v_zombies[i]->mask)) {
				canMove = false;
				//player.takeDamage();
			}
		}
		planes = world.getPlanes();
		for (CollisionPlane* p : *planes) {
			if (player.mask.intersectsPlane(p)) {
				canMove = false;
			}
		}
		if (canMove)player.strafeRight();
		else
			player.mask.update(player.getPosition());
		break;
	case 'c':
		player.crouch();
		break;
	case 27:  exit(0); break;
	}
	if (z >= -49 && z <= -46.5 && x >= 35.5 && x <= 45.5 &&	y <= 5.4)
	{
		float ratio = (player.getPosition().getX() - 35.5) / 10;
		player.setY(ratio*3.5);
	}

	else if (z >= -13.5 && z<= -11 && x >= 15 && x <= 25 &&	y <= 5.4)
	{
		float ratio = (25 - player.getPosition().getX()) / 10;
		player.setY(ratio*3.5);
	}

	else if (z >= -46.5 && z<= -44	&& x >= 35.5 && x <= 45.5 &&
		y >= (5) && y <= (3.5 + 1.7 + 3.5))
	{
		float ratio = (45.5 - player.getPosition().getX()) / 10;
		player.setY(ratio*3.5 + 3.5);
	}

	else {
		if (y >= (4.5) && y <= (6))
			player.setY(5.2 - 1.7);
		else if (y >= (8) && y <= (9.5))
			player.setY(8.7 - 1.7);
		else if (y >= (1) && y <= (2))
			player.setY(0);
	}
	Vector ammoPos = ammoBox.getLocation();
	float aX = ammoPos.getX();
	float aY = ammoPos.getY();
	float aZ = ammoPos.getZ();
	if (x > aX && x < aX + 0.64 && y > aY && y < aY + 3.5 && z > aZ - 0.34 && z < aZ)
		ammoBox.update();//add code to reload
	

	player.lookAt();
	//cout << player.getPosition().getX() << " " << player.getPosition().getY() << " "
	//	<< player.getPosition().getZ() << endl << endl;
}

void mouseMove(int x, int y) {
	player.lookAround(x, y);
}

void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (player.getAmmoTotal() > 0 || player.getAmmoCartridge() > 0)) {
		//generate muzzle flash
		glPushMatrix();
		glTranslatef(player.getPosition().getX(),
			player.getPosition().getY(), player.getPosition().getZ());
		glRotatef(-player.getThetha() * 180 / 3.14, 0, 1, 0);
		glTranslatef(0.2, 0, -0.2);
		glRotatef(player.getPhi() * 180 / 3.14, 1, 0, 0);
		glTranslatef(0, -0.3, 0);
		glScalef(0.001, 0.001, 0.001);
		glutSolidCone(0.1, 0.5, 16, 16);
		glPopMatrix();

		float x = player.getPosition().getX() + 0.1*(sin(player.getThetha()));
		float y = player.getPosition().getY() + 0.1*(sin(player.getPhi()))-1;
		float z = player.getPosition().getZ() - 0.1*(cos(player.getThetha()));
		muzzleFlash = new ParticleEffect(x, y, z, 0.001, 0.9, 0.9, 0.2, 500, 0.01);
		player.shoot();

		bufferGun.loadFromFile("../Gun.wav");
		//soundGun.play(); // Play the sound!
		Ray ray(player.getPosition(), player.getUnitVector());
		float minDistance = 1000;
		unsigned minIndex = 1000;
		bool somethingDies = false;
		for (unsigned i = 0; i < wave->v_zombies.size(); i++) {
			if (ray.intersects(wave->v_zombies[i]->mask)) {
				//generate blood splatter
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
			player.scoreUp();
		}
	}
}

void healthTimer(int value) {
	player.regainHealth();
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
			player.setWaveNumber(wave->waveNumber);
			hud->update(player.getHealth(), player.getAmmoCartridge(), player.getAmmoTotal(), player.getScore(), player.getWaveNumber(), player.getPosition(), player.getLookVector());
			isWave = true;
		}
		else {
			currentTimerDuration -= 1000;
		}
	}

	glutTimerFunc(timerInterval, WaveTimer, 0);
}

void Timer(int t) {
	player.lookAt();
	glutTimerFunc(20, Timer, 0);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv)
{

	sf::Music music;
	music.openFromFile("../Horror-theme-song.wav");
	//music.play();
	music.setLoop(true);

	sf::Music music2;
	music2.openFromFile("../Zombie-sound.wav");
	//music2.play();
	music2.setLoop(true);

	glutInit(&argc, argv);

	glutInitWindowSize(1024, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("ZombieLand Survivor");
	//glutFullScreen();
	world.init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processNormalKeys);
	//glutKeyboardFunc(keyEvents.keyPressed);
	//glutKeyboardUpFunc(keyEvents.keyUp);
	glutTimerFunc(0, WaveTimer, 0);
	glutTimerFunc(0, healthTimer, 0);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMove);

	glutIdleFunc(idle);
	glutTimerFunc(0, Timer, 0);
	initGL();

	glutMainLoop();
	wave->v_zombies.~vector();

	return 0;
}

