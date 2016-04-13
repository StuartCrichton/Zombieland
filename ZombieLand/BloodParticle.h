#pragma once
#ifndef BLOODPARTICLE_H
#define BLOODPARTICLE_H
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

class BloodParticle
{
public:
	BloodParticle(double Xpos, double Ypos, double Zpos, double Scalez);
	~BloodParticle();
	void update();
	double getRed();
	double getGreen();
	double getBlue();
	float currentRadius();
	double getXpos();
	double getYpos();
	double getZpos();
	double getDirection();
	double getScalez();
	void draw();

private:
	double Xpos;
	double Ypos;
	double Zpos;

	double initXpos;
	double initYpos;
	double initZpos;

	double Xmov;
	double Zmov;
	double Ymov;

	double Red;
	double Blue;
	double Green;

	double Direction;//Angle of rotation.
	double Acceleration;//Acceleration upwards
	double Deceleration;//deceleration downwards
	double Scalez;//How much we wish to scale it.
};
#endif // BLOODPARTICLE_

