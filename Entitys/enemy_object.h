#pragma once
#include "game_object.h"

class enemy_object : public GameObject
{
public:
	// Initialize enemy position using the b2world pointer, based on input
	void init(int posX, int posY, b2World* worldptr);

	// Initialize enemy target coordinates, speed and which axis it is moving on
	void initRange(float targetX, float targetY, int s, bool Axis);
	
	// Update decides whether to run Horizontal/Vertical update, and those two functions handle movement of enemy
	void update();
	void horizontalUpdate();
	void verticalUpdate();

	// Remove enemy from game
	void kill();

	// Check to see if collectable is dead, so it won't be rendered or it's physics calculated
	bool amIDead();

	// Stores body information
	b2Body* enemy_body_;

	// Checks whether enemy is patrolling
	bool targeting = false;

	// Stores enemy speed
	int speed;

private:
	// Stores information on target and original coords, temp coords allow swapping between the two for patrolling
	b2Vec2 target;
	b2Vec2 original;
	b2Vec2 temp;

	// Stores whether enemy is dead, it's axis information (positive/negative) and which axis is the enemy moving along (X or Y)
	bool dead = false;
	int AxisX = 1;
	int AxisY = 1;
	int Axis_;

};