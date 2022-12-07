#include "objectManager.h"
void Manager::init(gef::Platform& platref, b2World* worldptr, PrimitiveBuilder* pb)
{
	// Initialize player
	player_object.Init(platref, worldptr, pb);
}

void Manager::init_models(PrimitiveBuilder* pb, gef::Platform& platref)
{
	// Initialize Textures
	ground_texture = CreateTextureFromPNG("base_textures/grass_texture.png", platref);
	ground_material.set_texture(ground_texture);

	metal_texture = CreateTextureFromPNG("base_textures/metal_texture.png", platref);
	metal_material.set_texture(metal_texture);

	goal_texture = CreateTextureFromPNG("base_textures/goal_texture.png", platref);
	goal_material.set_texture(goal_texture);

	// Initialize Pbject Loader
	OBJMeshLoader obj_loader;
	MeshMap mesh_map;

	// Runs through all Enemies found in the object_manager, and assigns models to them
	for (int i = 0; i < enemies.size(); i++)
	{
		if (obj_loader.Load("enemy/enemy_ball_small.obj", platref, mesh_map))
		{
			gef::Mesh* enemy_mesh = mesh_map["vsn_mesh_0__mesh_0_"];
			if (enemy_mesh)
			{
				// assign the mesh to enemy object[i]
				enemies[i].set_mesh(enemy_mesh);
			}
		}
		else
		{
			// Backup incase model doesn't work
			enemies[i].set_mesh(pb->GetDefaultCubeMesh());
		}
	}

	// Runs through all Collectables found in the object_manager, and assigns models to them
	for (int i = 0; i < collectables.size(); i++)
	{
		if (obj_loader.Load("coin/coin.obj", platref, mesh_map))
		{
			gef::Mesh* collectable_mesh = mesh_map["Carrot_Coin"];
			if (collectable_mesh)
			{
				// assign the mesh collectable object[i]
				collectables[i].set_mesh(collectable_mesh);
			}
		}
		else
		{
			// Backup incase model doesn't work
			collectables[i].set_mesh(pb->GetDefaultCubeMesh());
		}
	}

	if (obj_loader.Load("player/player_fixed.obj", platref, mesh_map))
	{
		gef::Mesh* player_mesh = mesh_map["n0b0_ID10"];
		if (player_mesh)
		{
			// assign the mesh to my player gameobject
			player_object.set_mesh(player_mesh);
		}
	}
	else
	{
		// Backup incase model doesn't work
		player_object.set_mesh(pb->GetDefaultCubeMesh());
	}
}

void Manager::init_goal(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr)
{
	// Initialize the Goal 
	g.init(sX, sY, sZ, pb, posX, posY, worldptr);
}

void Manager::pushback_floor(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr)
{
	// Creates an instance of Floor, and pushes it into the vector stack
	f.init(sX, sY, sZ, pb, posX, posY, worldptr);
	floors.push_back(f);
}

void Manager::pushback_moving_floor(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr)
{
	// Creates an instance of Moving Floor, and pushes it into the vector stack
	m.init(sX, sY, sZ, pb, posX, posY, worldptr);
	moving_floors.push_back(m);
}

void Manager::pushback_enemy(int posX, int posY, b2World* worldptr)
{
	// Creates an instance of Enemy, and pushes it into the vector stack
	e.init(posX, posY, worldptr);
	enemies.push_back(e);
}

void Manager::pushback_collectable(int posX, int posY, b2World* worldptr)
{
	// Creates an instance of Collectable, and pushes it into the vector stack
	c.init(posX, posY, worldptr);
	collectables.push_back(c);
}

void Manager::init_enemy_range(float tX, float tY, int spd, int enemyNum, bool axis)
{
	// Sets a specific Enemy's Target coords, speed and axis
	enemies[enemyNum].initRange(tX, tY, spd, axis);
}

void Manager::init_moving_floor_range(float tX, float tY, int spd, int floorNum, bool axis)
{
	// Sets a specific Moving Floor's Target coords, speed and axis
	moving_floors[floorNum].initRange(tX, tY, spd, axis);
}

void Manager::change_enemy_speed(int spd)
{
	// Changes all Enemies speed
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].speed = spd;
	}
}

void Manager::update()
{
	// Updates Enemies if they aren't dead, and they are targeting specific coords
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].amIDead() == false)
		{
			enemies[i].UpdateFromSimulation(enemies[i].enemy_body_);

			if (enemies[i].targeting == true)
			{
				enemies[i].update();
			}
			if (enemies[i].enemy_body_->GetPosition().y < -20)
			{
				enemies[i].kill();
			}
		}
	}

	// Updates Moving Floors
	for (int i = 0; i < moving_floors.size(); i++)
	{
		moving_floors[i].UpdateFromSimulation(moving_floors[i].ground_body_);
		moving_floors[i].update();
	}

	// Updates Player
	player_object.Update();
}

void Manager::render(gef::Renderer3D* renderptr)
{
	// Renders Player
	renderptr->DrawMesh(player_object);

	// Overrides renderer with the appropriate material, and renders Goal
	renderptr->set_override_material(&goal_material);
	renderptr->DrawMesh(g);
	renderptr->set_override_material(NULL);

	// Overrides renderer with the appropriate material, and renders all Floors
	renderptr->set_override_material(&ground_material);
	for (int i = 0; i < floors.size(); i++)
	{
		renderptr->DrawMesh(floors[i].ground_);
	}
	renderptr->set_override_material(NULL);

	// Overrides renderer with the appropriate material, and renders all Floors
	renderptr->set_override_material(&metal_material);
	for (int i = 0; i < moving_floors.size(); i++)
	{
		renderptr->DrawMesh(moving_floors[i]);
	}
	renderptr->set_override_material(NULL);

	// Renders all collectables, as long as they aren't dead
	for (int i = 0; i < collectables.size(); i++)
	{
		if (collectables[i].amIDead() == false)
		{
			renderptr->DrawMesh(collectables[i]);
		}
	}

	// Renders all enemies, as long as they aren't dead
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].amIDead() == false)
		{
			renderptr->DrawMesh(enemies[i]);
		}
	}
}