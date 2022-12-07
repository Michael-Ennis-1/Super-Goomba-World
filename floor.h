#pragma once
#include "game_object.h"
#include "primitive_builder.h"

class Floor : public GameObject
{
public:
	// Initializes the Floor's size and it's position.
	void init(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr);

	// Stores information on a ground object, and it's body definition
	GameObject ground_;
	b2BodyDef body_def;

private:
	// Stores the half dimensions of the floor
	gef::Vector4 ground_half_dimensions;

	// Stores the Floor's mesh, body and user data
	gef::Mesh* ground_mesh_;
	b2Body* ground_body_;
	b2BodyUserData ground_data;

	// Stores the Floor's shape, for collision detection
	b2PolygonShape shape;

	// Stores the Floor's fixture variables
	b2FixtureDef fixture_def;
};