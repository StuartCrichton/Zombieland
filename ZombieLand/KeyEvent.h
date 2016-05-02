#pragma once
#include "Vector.h"
#include "Player.h"
#include "Wave.h"
#include "CollisionPlane.h"
#include "World.h"
#include "AmmoBox.h"

using namespace std;

class KeyEvent
{
public:
	KeyEvent();
	KeyEvent(Player *player, World *world, Wave *wave, AmmoBox *box);
	~KeyEvent();
	void keyOperations();
	bool *keyStates = new bool[256];
private:
	Vector v;
	Player *player;
	World* world;
	Wave *wave;
	AmmoBox *box;
	vector<CollisionPlane*>* planes;
	bool canMove = true;
	void pressedForward();
	void pressedBackwards();
	void pressedLeft();
	void pressedRight();	
};