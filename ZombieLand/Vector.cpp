#include "Vector.h"
#include <math.h>

float Vector::getX()
{
	return this->x;
}
float Vector::getY()
{
	return this->y;
}
float Vector::getZ()
{
	return this->z;
}
void Vector::setX(float a)
{
	this->x = a;
}
void Vector::setY(float a)
{
	this->y = a;
}
void Vector::setZ(float a)
{
	this->z = a;
}
void Vector::setV(float a, float b, float c)
{
	this->setX(a);
	this->setY(b);
	this->setZ(c);
}

float Vector::getDistance(Vector v)
{
	float a = x - v.getX();
	float b = y - v.getY();
	float c = z - v.getZ();
	float d = a*a;
	float e = b*b;
	float f = c*c;
	return sqrt(d + e + f);
}

float Vector::dotProduct()
{
	return x*x + y*y + z*z;
}

float Vector::dotProduct(Vector v2)
{
	return x*v2.getX() + y*v2.getY() + z*v2.getZ();
}

Vector Vector::operator*(float scale) const {
	return Vector(x * scale, y * scale, z * scale);
}

Vector Vector::operator/(float scale) const {
	return Vector(x / scale, y / scale, z / scale);
}

Vector Vector::operator+(const Vector &other) const {
	return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::operator-(const Vector &other) const {
	return Vector(x - other.x, y - other.y, z - other.z);
}

Vector Vector::operator-() const {
	return Vector(-x, -y, -z);
}

const Vector &Vector::operator*=(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

const Vector &Vector::operator/=(float scale) {
	x /= scale;
	y /= scale;
	z /= scale;
	return *this;
}

const Vector &Vector::operator+=(const Vector &other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

const Vector &Vector::operator-=(const Vector &other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector::Vector()
{
	//ctor
}

Vector::Vector(float a, float b, float c)
{
	this->x = a;
	this->y = b;
	this->z = c;
}

Vector::~Vector()
{
	//dtor
}
