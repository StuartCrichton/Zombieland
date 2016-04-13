#include "BloodSplatter.h"
#include "BloodParticle.h"
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <vector>
#include <iostream>

using namespace std;


int BloodSplatter::update()
{
	for (int i = 0; i < particle.size(); i++) {
		particle[i].update();

		if (particle[i].currentRadius() >= (0.5))
		{
			particle.erase(particle.begin() + i);
		}

		if (particle.size() < 800) {
			particle.clear();
		}
	}

	this->draw();

	if (particle.size() == 0)
		return 1;
	return 0;
}

void BloodSplatter::draw()
{
	for (int i = 0; i < particle.size(); i++)
	{
		particle[i].draw();
	}
}

BloodSplatter::BloodSplatter(double Xpos, double Ypos, double Zpos)
{
	for (int i = 0; i < bloodParticleCount; i++)
	{
		BloodParticle bloodParticle = BloodParticle(Xpos, Ypos+1, Zpos, 0.05);
		particle.push_back(bloodParticle);
	}

	draw();
}

BloodSplatter::~BloodSplatter()
{
	delete this;
}

