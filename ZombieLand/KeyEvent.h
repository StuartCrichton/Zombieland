#pragma once
#ifndef KEYEVENT_H
#define KEYEVENT_H
#include "Vector.h"
#include "Player.h"
#include "Wave.h"
#include "CollisionPlane.h"
#include "World.h"

using namespace std;

class KeyEvent
{
public:
	KeyEvent(Player player, World world, Wave *wave);
	~KeyEvent();
	void keyPressed(unsigned char key, int x, int y);
	void keyUp(unsigned char key, int x, int y);
	void keyOperations(void);

	bool *keyStates = new bool[256];
private:
	Vector v;
	Player player();
	World world;
	Wave *wave;
	vector<CollisionPlane*>* planes;
	bool canMove = true; //keeps track if a character can move for collision detection
	void pressedForward();
	void pressedBackwards();
	void pressedLeft();
	void pressedRight();
};

#endif //KEYEVENT_H