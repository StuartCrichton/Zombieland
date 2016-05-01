#include "Bullet.h"



Bullet::Bullet(Vector* position, Vector* direction)
{
	this->position = *position;
	this->direction = *direction;
	this->mask = CollisionMask(this->position, 0.02);
}

void Bullet::update() {
	float x = position.getX() + 0.5*direction.getX();
	float y = position.getY() + 0.5*direction.getY();
	float z = position.getZ() + 0.5*direction.getZ();

	this->position.setV(x, y, z);
	this->mask.update(position);
	this->steps++;
}

void Bullet::render() {

	glPushMatrix();
	GLfloat color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glTranslatef(position.getX(), position.getY(), position.getZ());
	glutSolidSphere(0.02, 16, 16);
	glPopMatrix();
}

int Bullet::getSteps() {
	return steps;
}

Vector Bullet::getPosition() {
	return position;
}

Bullet::~Bullet()
{
}
