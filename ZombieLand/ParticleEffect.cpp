#include "ParticleEffect.h"
#include "Particle.h"
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <vector>
#include <iostream>

using namespace std;


int ParticleEffect::update()
{
	for (int i = 0; i < particles.size(); i++) {
		particles[i].update();

		if (particles[i].currentRadius() >= particleRadius)
		{
			particles.erase(particles.begin() + i);
		}

		if (particles.size() < (this->particleCount/1.2)) {
			particles.clear();
		}
	}

	this->draw();

	if (particles.size() == 0)
		return 1;
	return 0;
}

void ParticleEffect::draw()
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].draw();
	}
}

ParticleEffect::ParticleEffect(double Xpos, double Ypos, double Zpos, double Size, double red, double green, double blue, int particleCount, double particleRadius)
{
	this->particleRadius = particleRadius;
	this->particleCount = particleCount;

	for (int i = 0; i < particleCount; i++)
	{
		Particle particle = Particle(Xpos, Ypos, Zpos, Size, red, green, blue);
		particles.push_back(particle);
	}

	draw();
}

ParticleEffect::~ParticleEffect()
{
	delete this;
}