#pragma once
#include "game_object.h"
#include "primitive_builder.h"

class Moving_Floor : public GameObject
{
public:
	// Initialize size, and position based on input
	void init(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr);

	// Initialize target coordinates, speed and which axis it is moving on
	void initRange(float targetX, float targetY, int s, bool Axis);

	// Update decides whether to run Horizontal/Vertical update, and those two functions handle movement of floor
	void update();
	void horizontalUpdate();
	void verticalUpdate();

	// Stores body information, and pointer to ground_body_ to be used when moving
	b2BodyDef body_def;
	b2Body* ground_body_;

	// Stores the speed and which axis it moves on. Also stores the positive/negative direction that it will move upon them 
	int speed;
	bool Axis_;
	int AxisX = 1;
	int AxisY = 1;

private:
	// Stores size of Moving Floor
	gef::Vector4 ground_half_dimensions;

	// Stores mesh and userdata
	gef::Mesh* ground_mesh_;
	b2BodyUserData ground_data;

	// Stores the shape 
	b2PolygonShape shape;

	// Stores the fixture variables
	b2FixtureDef fixture_def;

	// Stores information on target and original coords, temp coords allow swapping between the two for patrolling
	b2Vec2 target;
	b2Vec2 original;
	b2Vec2 temp;
};
