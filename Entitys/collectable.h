#pragma once
#include "game_object.h"

class Collectable : public GameObject
{
public:
    // Initialize collectable's position using the b2world pointer, based on input
	void init(int posX, int posY, b2World* worldptr);

	// Remove the collectable from game
	void kill();

	// Check to see if collectable is dead, so it won't be rendered or it's physics calculated
	bool amIDead();

	// Stores body information
	b2Body* collectable_body_;

private:
	// Stores whether collectable is dead or not
	bool isDead = false;
};