#pragma once
#ifndef LIGHTING_H
#define LIGHTING_H
#include <math.h>
#include <GL/glut.h>

class Lighting
{
public:
	Lighting();
	void lightInitGL();
	void update();
	~Lighting();

protected:

private:
	float light_X = 150.0;
	float light_Y = 10.0;
	float light_Z = -150.0;
	float angle = 15;
	int time_Prev = 0;
};
#endif