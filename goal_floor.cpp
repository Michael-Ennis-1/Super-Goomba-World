#include "goal_floor.h"

void Goal_Floor::init(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr)
{
	// Goal dimensions
	ground_half_dimensions = gef::Vector4(sX, sY, sZ);

	// Setup the mesh for the ground and set object type to GOAL (used to win game)
	ground_mesh_ = pb->CreateBoxMesh(ground_half_dimensions); //- Try creating this outside of the class so we don't need to pass the pb here
	set_mesh(ground_mesh_);
	object_type_ = GAME_OBJECT_TYPE::GOAL;

	// Setup user data for goal
	ground_data.pointer = (uintptr_t)this;

	// Create a physics body
	body_def.type = b2_staticBody;
	body_def.position = b2Vec2(posX, posY);
	body_def.userData = ground_data;

	// Want this section in the Manager, but temporarily can have it in here
	ground_body_ = worldptr->CreateBody(&body_def);

	// Create Shape for the fixture to use as a collision box
	shape.SetAsBox(ground_half_dimensions.x(), ground_half_dimensions.y());

	// Assign shape information
	fixture_def.shape = &shape;

	// Create the Fixture
	ground_body_->CreateFixture(&fixture_def);

	// Initialize the physics simulation
	UpdateFromSimulation(ground_body_);
}