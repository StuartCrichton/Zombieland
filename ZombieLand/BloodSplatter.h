#pragma once
#ifndef BLOODSPLATTER_H
#define BLOODSPLATTER_H
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include "Particle.h"

using namespace std;

class BloodSplatter
{
public:
	BloodSplatter(double Xpos, double Ypos, double Zpos);
	~BloodSplatter();
	int update();
	void draw();
private:
	vector<Particle> particle;
	const int bloodParticleCount = 1000;
};
#endif // BLOODSPLATTER_H

