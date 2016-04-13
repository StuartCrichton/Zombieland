#pragma once
#include "Vector.h"
#include "CollisionMask.h"

class Character
{
public:
	CollisionMask mask;
	Character();
	void turnLeft();
	void turnRight();
	void rotateX(int angle);
	void moveForward();
	void moveForward(float steps);
	Vector getPosition();
	Vector getLookVector();
	Vector getNewPosition(int id);
	Vector getUnitVector();
	const int FORWARD = 0;
	const int BACKWARD = 1;
	const int LEFT = 2;
	const int RIGHT = 3;
	static Vector playerPos;
	virtual ~Character();

protected:
	int health = 0;
	Vector pos_v;
	Vector look_v;
	float thetha = 0;
	float phi = 0;
	float step = 0.5;
	const float M_PI = 3.141592653589793238463;
	
private:

};

