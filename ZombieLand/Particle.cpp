#include "Particle.h"
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <math.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Vector.h"
#include <time.h>

using namespace std;

void Particle::update()
{
	this->Ypos = this->Ypos + this->Ymov;
	this->Xpos = this->Xpos + this->Xmov;
	this->Zpos = this->Zpos + this->Zmov;
	this->Direction = this->Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1);
}

double Particle::getRed()
{
	return this->Red;
}

double Particle::getGreen()
{
	return this->Green;
}

double Particle::getBlue()
{
	return this->Blue;
}

float Particle::currentRadius()
{
	Vector v1 = Vector(Xpos, Ypos, Zpos);
	Vector v2 = Vector(initXpos, initYpos, initZpos);
	float distance = v1.getDistance(v2);
	return distance;
}

double Particle::getXpos()
{
	return this->Xpos;
}

double Particle::getYpos()
{
	return this->Ypos;
}

double Particle::getZpos()
{
	return this->Zpos;
}

double Particle::getDirection()
{
	return this->Direction;
}

double Particle::getScalez()
{
	return this->Scalez;
}

void Particle::draw()
{
	glPushMatrix();
	GLfloat color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color);
	glTranslatef(Xpos, Ypos, Zpos);
	//glRotatef(Direction - 90, 0, 0, 1);
	glScalef(Scalez, Scalez, Scalez);

	//Draw Shere
	glutSolidSphere(0.1, 16, 16);

	glPopMatrix();
}

Particle::Particle(double Xpos, double Ypos, double Zpos, double Scalez, double Red, double Green, double Blue)
{
	this->Xpos = Xpos;
	this->Ypos = Ypos;
	this->Zpos = Zpos;

	this->initXpos = Xpos;
	this->initYpos = Ypos;
	this->initZpos = Zpos;

	this->Xmov = (rand() % 20 - 10)*0.03;
	this->Zmov = (rand() % 20 - 10)*0.03;
	this->Ymov = (rand() % 20 - 10)*0.03;

	this->Red = Red;
	this->Green = Green;
	this->Blue = Blue;

	this->Scalez = Scalez;
	this->Direction = 0;
	this->Acceleration = ((((((8 - 5 + 2) * rand() % 11) + 5) - 1 + 1) * rand() % 11) + 1) * 0.02;
	this->Deceleration = 0.0025;
}

Particle::~Particle()
{
}
