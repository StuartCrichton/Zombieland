#include "BloodParticle.h"
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <math.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Vector.h"

using namespace std;

void BloodParticle::update()
{
	this->Ypos = this->Ypos + this->Ymov;
	this->Xpos = this->Xpos + this->Xmov;
	this->Zpos = this->Zpos + this->Zmov;
	this->Direction = this->Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1);
}

double BloodParticle::getRed()
{
	return this->Red;
}

double BloodParticle::getGreen()
{
	return this->Green;
}

double BloodParticle::getBlue()
{
	return this->Blue;
}

float BloodParticle::currentRadius()
{
	Vector v1 = Vector(Xpos, Ypos, Zpos);
	Vector v2 = Vector(initXpos, initYpos, initZpos);
	float distance = v1.getDistance(v2);
	return distance;
}

double BloodParticle::getXpos()
{
	return this->Xpos;
}

double BloodParticle::getYpos()
{
	return this->Ypos;
}

double BloodParticle::getZpos()
{
	return this->Zpos;
}

double BloodParticle::getDirection()
{
	return this->Direction;
}

double BloodParticle::getScalez()
{
	return this->Scalez;
}

void BloodParticle::draw()
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

BloodParticle::BloodParticle(double Xpos, double Ypos, double Zpos, double Scalez)
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

	this->Red = 1.0;
	this->Green = 0.0;
	this->Blue = 0.0;

	this->Scalez = Scalez;
	this->Direction = 0;
	this->Acceleration = ((((((8 - 5 + 2) * rand() % 11) + 5) - 1 + 1) * rand() % 11) + 1) * 0.02;
	this->Deceleration = 0.0025;
}

BloodParticle::~BloodParticle()
{
}
