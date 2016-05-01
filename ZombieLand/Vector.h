#pragma once
class Vector
{
public:
	Vector();
	Vector(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setV(float x, float y, float z);
	float getDistance(Vector* v);
	float dotProduct();
	float dotProduct(Vector v);

	Vector operator*(float scale) const;
	Vector operator/(float scale) const;
	Vector operator+(const Vector &other) const;
	Vector operator-(const Vector &other) const;
	Vector operator-() const;

	const Vector &operator*=(float scale);
	const Vector &operator/=(float scale);
	const Vector &operator+=(const Vector &other);
	const Vector &operator-=(const Vector &other);
	const Vector &operator=(const Vector &other);

	~Vector();
private:
	float x = 0, y = 0, z = 0;
};
