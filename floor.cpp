#include "floor.h"

void Floor::init(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr)
{
	// Sets half dimensions for Floor
	ground_half_dimensions = gef::Vector4(sX, sY, sZ);

	// Sets up the mesh for Floor, and sets it's object type to GROUND
	ground_mesh_ = pb->CreateBoxMesh(ground_half_dimensions); //- Try creating this outside of the class so we don't need to pass the pb here
	ground_.set_mesh(ground_mesh_);
	ground_.object_type_ = GAME_OBJECT_TYPE::GROUND;

	// Setup Floor's user data
	ground_data.pointer = (uintptr_t)&ground_;

	// Assign variables to the Floor's body, including what type of body it is, it's position and it's user_data (which is the object type)
	body_def.type = b2_staticBody;
	body_def.position = b2Vec2(posX, posY);
	body_def.userData = ground_data;

	// Create the Floor in the world, according to the data defined in body_def
	ground_body_ = worldptr->CreateBody(&body_def);

	// Assign a fixture to the Floor for other objects to collide with, based on it's half dimensions
	shape.SetAsBox(ground_half_dimensions.x(), ground_half_dimensions.y());

	// Create the Fixture
	fixture_def.shape = &shape;

	// Assign the fixture to the body
	ground_body_->CreateFixture(&fixture_def);

	// Initialize the physics simulation
	ground_.UpdateFromSimulation(ground_body_);
}