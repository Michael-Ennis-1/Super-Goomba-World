#include "player_object.h"

void Player_Object::Init(gef::Platform& platref, b2World* worldptr, PrimitiveBuilder* pb)
{
	// Create the OBJ loader
	OBJMeshLoader obj_loader;
	MeshMap mesh_map;

	// Set 'Player' object type
	object_type_ = GAME_OBJECT_TYPE::PLAYER;

	// Player User Data
	b2BodyUserData user_data;
	user_data.pointer = (uintptr_t)this;

	// Create a physics body for the player
	b2BodyDef player_body_def;
	player_body_def.type = b2_dynamicBody;
	player_body_def.position = b2Vec2(0.0f, 4.0f);
	player_body_def.userData = user_data;

	player_body_ = worldptr->CreateBody(&player_body_def);

	// Create the shape for the player
	b2PolygonShape player_shape;
	player_shape.SetAsBox(0.8f, 0.8f);

	// Create the fixture definition
	b2FixtureDef player_fixture_def;
	player_fixture_def.shape = &player_shape;
	player_fixture_def.density = 1.0f;

	// Create the fixture from its definition
	player_body_->CreateFixture(&player_fixture_def);

	// Update physics simulation
	UpdateFromSimulation(player_body_);
}

void Player_Object::Update()
{
	// Update physics simulation
	UpdateFromSimulation(player_body_);
}