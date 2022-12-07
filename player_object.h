#pragma once
#include "game_object.h"
#include "obj_mesh_loader.h"
#include "primitive_builder.h"
class Player_Object : public GameObject
{
public:
	// Initializes the player, putting the player at a predefined location
	void Init(gef::Platform& platref, b2World* worldptr, PrimitiveBuilder* pb);

	// Updates the physics simulation for the player
	void Update();

	// Stores the player body
	b2Body* player_body_;
};
