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
#include "BloodSplatter.h"
#include "AmmoBox.h"

using namespace std;
// Global variables


Player player;
World world;
Vector v;
bool canMove = true; //keeps track if a character can move for collision detection
vector<CollisionPlane*>* planes;
HUD *hud = new HUD(player.getHealth(), player.getAmmoCartridge(), player.getAmmoTotal(),
	player.getScore(), player.getWaveNumber());

int dimx = 60;
int dimy = 5;
int dimz = 80;
GLfloat light_position[] = { dimx, 10, -dimz,0.0 };
GLfloat light_position1[] = { 1,1,0,1.0 };
GLfloat light_position3[] = { -dimx, 10, dimz, 1.0 };
GLfloat light_position2[] = { dimx / 2 , 10, -(dimz / 2),0.0 };
GLfloat light_position4[] = { dimx / 2, dimy, 0.0, 1.0 };
GLfloat light_position5[] = { dimx / 2, dimy, -dimz, 1.0 };
GLfloat light_position6[] = { dimx / 2, 50, -(dimz / 2), 1.0 };
GLfloat light_position7[] = { dimx / 2, -50, -(dimz / 2), 1.0 };
//GLfloat spot_direction[] = { dimx/2, dimy, -(dimz/2) };

//Stuff pertraining to the wave
Wave *wave = new Wave();
float currentTimerDuration = wave->WAVE_DURATION;
int timerInterval = wave->getZombieSpawnInterval();
int numOfKilledZombies = 0;
bool isWave = true;

//Stuff pertaining to particles
BloodSplatter *bloodSplatter;

//Stuff pertaining to ammo box
AmmoBox ammoBox;

void initGL()
{
	// Set "clearing" or background color
	glClearColor(0, 0.1, 0.4, 1);
	glutSetCursor(GLUT_CURSOR_NONE);
	//glClearColor(0, 0, 0, 1); // White and opaque

	glEnable(GL_LIGHTING); // turns on the lighting model in OpenGL
	float ambientCol[] = { 1.0f,1.0f,1.0f,1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientCol);

	GLfloat diffuse0[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambient0[] = { 0,0,0,1 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);

	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);

	GLfloat diffuse_prop2[] = { 1.0f,1.0f,1.0f,1.0f };
	//GLfloat diffuse_prop2[] = { 0.5f,0.5f,0.5f,1.0f };
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse_prop2);

	GLfloat specular_prop2[] = { 0.5f,0.5f,0.5f,1.0f };
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular_prop2);

	glLightfv(GL_LIGHT7, GL_POSITION, light_position7);

	GLfloat diffuse_prop6[] = { 1.0f,1.0f,1.0f,1.0f };
	glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuse_prop6);
	glLightfv(GL_LIGHT7, GL_AMBIENT, diffuse_prop6);

	GLfloat specular_prop6[] = { 0.5f,0.5f,0.5f,1.0f };
	glLightfv(GL_LIGHT7, GL_SPECULAR, specular_prop6);


	glEnable(GL_LIGHT0);//corner1
	glEnable(GL_LIGHT3);//corner2
	glEnable(GL_LIGHT7);//below

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
	player.lookAt();

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
	glLightfv(GL_LIGHT4, GL_POSITION, light_position4);
	glLightfv(GL_LIGHT5, GL_POSITION, light_position5);
	glLightfv(GL_LIGHT6, GL_POSITION, light_position6);
	glLightfv(GL_LIGHT7, GL_POSITION, light_position7);

	//Draw the building
	GLfloat color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	world.building.Draw(1);
	/*vector<CollisionPlane*>* planes = world.getPlanes();
	for (CollisionPlane* p : *planes) {
		p->debug();
	}*/

	for (int i = 0; i < wave->v_zombies.size(); i++) {
		wave->v_zombies[i]->render(player.getPosition());
	}

	ammoBox.draw();

	/*cout << player.getPosition().getX() << " "
		<< player.getPosition().getY() << " "
		<< player.getPosition().getZ() << endl;*/

		//update and display the HUD
	hud->update(player.getHealth(), player.getAmmoCartridge(), player.getAmmoTotal(), player.getScore(), player.getWaveNumber());
	hud->render();

	int a;
	if (bloodSplatter != nullptr) {
		a = bloodSplatter->update();
		if (a == 1)
			bloodSplatter = nullptr;
	}

	glFlush();   // ******** DO NOT FORGET THIS **********

}
void display()
{
	//update();
	render();
}
void update()
{

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

void processNormalKeys(unsigned char key, int x, int y) {
	/*For keys w,a,s,d simple collision detection is used
	* -The objects mask is updated based on the direction it wants to move
	* -canMove is set to true and only changed if the new mask collides with another object
	* -If the player can move, the apprpriate move method is called
	* -Else the player's mask is reset to before moving
	*/
	switch (key) {
	case 'r': player.init(); player.lookAt(); break; // shrink
	case 'w': v = player.getNewPosition(player.FORWARD);
		player.mask.update(v);
		canMove = true;
		for (unsigned i = 0; i < wave->v_zombies.size(); i++)
		{
			if (player.mask.intersects(wave->v_zombies[i]->mask)) {
				canMove = false;
				player.takeDamage();
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
				player.takeDamage();
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
				player.takeDamage();
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
				player.takeDamage();
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
	if (player.getPosition().getZ() >= -49 && player.getPosition().getZ() <= -46.5 &&
		player.getPosition().getX() >= 35.5 && player.getPosition().getX() <= 45.5 &&
		player.getPosition().getY() <= 5.4)
	{
		float ratio = (player.getPosition().getX() - 35.5) / 10;
		player.setY(ratio*3.5);
	}

	else if (player.getPosition().getZ() >= -13.5 && player.getPosition().getZ() <= -11 &&
		player.getPosition().getX() >= 15 && player.getPosition().getX() <= 25 &&
		player.getPosition().getY() <= 5.4)
	{
		float ratio = (25 - player.getPosition().getX()) / 10;
		player.setY(ratio*3.5);
	}

	else if (player.getPosition().getZ() >= -46.5 && player.getPosition().getZ() <= -44
		&& player.getPosition().getX() >= 35.5 && player.getPosition().getX() <= 45.5 &&
		player.getPosition().getY() >= (5) && player.getPosition().getY() <= (3.5 + 1.7 + 3.5))
	{
		float ratio = (45.5 - player.getPosition().getX()) / 10;
		player.setY(ratio*3.5 + 3.5);
	}

	else {
		if (player.getPosition().getY() >= (4.5) && player.getPosition().getY() <= (6))
			player.setY(5.2 - 1.7);
		else if (player.getPosition().getY() >= (8) && player.getPosition().getY() <= (9.5))
			player.setY(8.7 - 1.7);
		else if (player.getPosition().getY() >= (1) && player.getPosition().getY() <= (2))
			player.setY(0);
	}


	player.lookAt();
	cout << player.getPosition().getX() << " " << player.getPosition().getY() << " "
		<< player.getPosition().getZ() << endl << endl;
}

void mouseMove(int x, int y) {
	player.lookAround(x, y);
}

void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (player.getAmmoTotal() > 0 || player.getAmmoCartridge() > 0)) {
		player.shoot();
		PlaySound(TEXT("../Gun.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Ray ray(player.getPosition(), player.getUnitVector());
		float minDistance = 1000;
		unsigned minIndex = 1000;
		bool somethingDies = false;
		for (unsigned i = 0; i < wave->v_zombies.size(); i++) {
			if (ray.intersects(wave->v_zombies[i]->mask)) {
				bloodSplatter = new BloodSplatter(wave->v_zombies[i]->getPosition().getX(), wave->v_zombies[i]->getPosition().getY(), wave->v_zombies[i]->getPosition().getZ());

				somethingDies = true;
				float d = ray.getDistance();
				if (d < minDistance) {
					minDistance = d;
					minIndex = i;
				}

			}
		}
		if (somethingDies) {
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
			hud->update(player.getHealth(), player.getAmmoCartridge(), player.getAmmoTotal(), player.getScore(), player.getWaveNumber());
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
	//PlaySound(TEXT("../ChillingMusic.wav"), NULL, SND_FILENAME | SND_ASYNC);
	glutInit(&argc, argv);

	glutInitWindowSize(1024, 720);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("ZombieLand Survivor");
	glutFullScreen();
	world.init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processNormalKeys);
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

