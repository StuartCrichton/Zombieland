#pragma once
#include "Vector.h"
#include "Player.h"
#include "Wave.h"
#include "CollisionPlane.h"
#include "World.h"

using namespace std;

class KeyEvent
{
public:
	KeyEvent();
	KeyEvent(Player *player, World world, Wave *wave);
	~KeyEvent();
	void keyOperations();

	bool *keyStates = new bool[256];
private:
	Vector v;
	Player *player;
	World world;
	Wave *wave;
	vector<CollisionPlane*>* planes;
	bool canMove = true; //keeps track if a character can move for collision detection
	void pressedForward();
	void pressedBackwards();
	void pressedLeft();
	void pressedRight();
};