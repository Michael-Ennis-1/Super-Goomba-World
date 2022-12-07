#pragma once
#include "game_object.h"
#include "primitive_builder.h"

class Goal_Floor : public GameObject
{
public:
	// Initialize size and position of Goal
	void init(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr);

	// Stores body specific information
	b2BodyDef body_def;

private:
	// Stores the half size of the Goal object
	gef::Vector4 ground_half_dimensions;

	// Stores the mesh, body and data information of the Goal object
	gef::Mesh* ground_mesh_;
	b2Body* ground_body_;
	b2BodyUserData ground_data;

	// Stores the shape information that is used to create a collision boc
	b2PolygonShape shape;

	// Stores fixture information
	b2FixtureDef fixture_def;

};