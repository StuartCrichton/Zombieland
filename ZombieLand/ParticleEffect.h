#pragma once
#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include "Particle.h"

using namespace std;

class ParticleEffect
{
public:
	ParticleEffect(double Xpos, double Ypos, double Zpos, double Size, double red, double green, double blue, int particleCount, double particleRadius);
	~ParticleEffect();
	int update();
	void draw();
private:
	vector<Particle> particles;
	double particleRadius;
	int particleCount;
};
#endif // PARTICLEEFFECT_H

