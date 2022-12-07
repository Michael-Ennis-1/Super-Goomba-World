#include "collectable.h"

void Collectable::init(int posX, int posY, b2World* worldptr)
{
	// Assign COLLECTABLE type
    object_type_ = GAME_OBJECT_TYPE::COLLECTABLE;

	// Sets user data for collectalbe
	b2BodyUserData user_data;
	user_data.pointer = (uintptr_t)this;

	// Assign variables to the object's body, including what type of body it is, it's position and it's user_data (which is the object type)
	b2BodyDef body_def;
	body_def.type = b2_staticBody;
	body_def.position = b2Vec2(posX, posY);
	body_def.userData = user_data;

	// Create the collectable in the world, according to the data defined in body_def
	collectable_body_ = worldptr->CreateBody(&body_def);

	// Create a shape for the fixture to use as a collision box
	b2PolygonShape collectable_shape;
	collectable_shape.SetAsBox(0.5f, 0.5f);

	// Assign a fixture to the collectable for other objects to collide with
	b2FixtureDef fixture_def;
	fixture_def.shape = &collectable_shape;
	fixture_def.density = 1.0f;

	// Create the fixture
	collectable_body_->CreateFixture(&fixture_def);

	// Initialize the physics simulation
	UpdateFromSimulation(collectable_body_);
}

void Collectable::kill()
{
	// Set bool variable to true, so that the render function won't render it anymore
	isDead = true;

	// Sets position to very far off screen, so no longer needing to worry about it
	collectable_body_->SetTransform(b2Vec2(-100, -100), 0);
}

bool Collectable::amIDead()
{
	// Returns isDead boolean
	return isDead;
}
