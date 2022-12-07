#pragma once
#include "game_object.h"
#include "graphics/renderer_3d.h"
#include "graphics/material.h"
#include "obj_mesh_loader.h"
#include "load_texture.h"
#include <vector>

// Entity Includes
#include "floor.h"
#include "enemy_object.h"
#include "collectable.h"
#include "player_object.h"
#include "moving_floor.h"
#include "goal_floor.h"

class Manager
{
public:
	// Initialize the Player only
	void init(gef::Platform& platref, b2World* worldptr, PrimitiveBuilder* pb);

	// Initializes the models of all objects, and the textures
	void init_models(PrimitiveBuilder* pb, gef::Platform& platref);

	// Initializes the Goal
	void init_goal(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr);

	// Defines a Floor and pushes it onto the vector stack
	void pushback_floor(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr);

	// Defines a Moving Floor and pushes it onto the vector stack
	void pushback_moving_floor(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr);

	// Defines an Enemy and pushes it onto the vector stack
	void pushback_enemy(int posX, int posY, b2World* worldptr);

	// Defines a Collectable and pushes it onto the vector stack
	void pushback_collectable(int posX, int posY, b2World* worldptr);

	// Initializes a specific Enemy's target
	void init_enemy_range(float tX, float tY, int spd, int enemyNum, bool axis);

	// Initializes a specific Moving Platform's target
	void init_moving_floor_range(float tx, float ty, int spd, int floorNum, bool axis);

	// Changes all Enemy's speeds
	void change_enemy_speed(int spd);
	
	// Updates Enemies if they aren't dead, updates Moving Platforms and update the Player
	void update();

	// Renders all objects in the game, and assigns meshes
	void render(gef::Renderer3D* renderptr);

	// Stores all instances of a specific game object, in their own defined vector stack
	std::vector<Floor> floors;
	std::vector<Moving_Floor> moving_floors;
	std::vector<enemy_object> enemies;
	std::vector<Collectable> collectables;

	// Stores player information
	Player_Object player_object;

private:
	// Stores object information, to be used when pushing onto the stack
	Floor f;
	Moving_Floor m;
	enemy_object e;
	Collectable c;
	Goal_Floor g;

	// Stores Floor texture and material
	gef::Texture* ground_texture;
	gef::Material ground_material;

	// Stores Moving Floor texture and material
	gef::Texture* metal_texture;
	gef::Material metal_material;

	// Stores Goal texture and material
	gef::Texture* goal_texture;
	gef::Material goal_material;
};
