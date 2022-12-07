#include "game_screen.h"

void Game_Screen::Init(PrimitiveBuilder* pb, b2World* worldptr, gef::Platform& platref, gef::AudioManager* audioptr)
{
	// Load sounds
	coin_wav = audioptr->LoadSample("audio/coins.wav", platref);
	explosion_wav = audioptr->LoadSample("audio/explosion.wav", platref);
	falling_wav = audioptr->LoadSample("audio/falling.wav", platref);

	// Initializes Player
	object_manager.init(platref, worldptr, pb);

	// Pushback all objects used in the level, including floors, enemies (and their patrols), and collectables

	// Part 1
	object_manager.pushback_floor(10.0f, 0.5f, 0.5f, pb, 0, 0, worldptr);
	object_manager.pushback_collectable(-8, 3, worldptr);
	// Part 2 - Route 1
	object_manager.pushback_moving_floor(5.0f, 0.5f, 0.5f, pb, 44, 3, worldptr);
	object_manager.init_moving_floor_range(18, 0, 3, 0, true);
	object_manager.pushback_collectable(31, 6, worldptr);
	// Part 2 - Route 2
	object_manager.pushback_floor(5.0f, 0.5f, 0.5f, pb, 18, -3, worldptr);
	object_manager.pushback_floor(5.0f, 0.5f, 0.5f, pb, 31, -6, worldptr);
	object_manager.pushback_floor(5.0f, 0.5f, 0.5f, pb, 44, -3, worldptr);
	object_manager.pushback_collectable(31, -1, worldptr);
	object_manager.pushback_collectable(31, -4, worldptr);
	object_manager.pushback_enemy(36, -4, worldptr);
	object_manager.init_enemy_range(26, 0, 2, 0, true);
	// Part 3
	object_manager.pushback_moving_floor(5.0f, 0.5f, 0.5f, pb, 57, -3, worldptr);
	object_manager.init_moving_floor_range(0, 3, 3, 1, false);
	object_manager.pushback_collectable(57, 0, worldptr);
	object_manager.pushback_enemy(51, 3, worldptr);
	object_manager.init_enemy_range(0, -3, 2, 1, false);
	object_manager.pushback_floor(5.0f, 0.5f, 0.5f, pb, 70, 0, worldptr);
	object_manager.pushback_collectable(70, 3, worldptr);
	object_manager.pushback_collectable(78, 3, worldptr);
	object_manager.pushback_floor(5.0f, 0.5f, 0.5f, pb, 86, 0, worldptr);
	object_manager.pushback_enemy(81, 3, worldptr);
	object_manager.init_enemy_range(91, 0, 2, 2, true);
	// Part 4
	object_manager.pushback_moving_floor(5.0f, 0.5f, 0.5f, pb, 99, -3, worldptr);
	object_manager.init_moving_floor_range(0, 17, 4, 2, false);
	object_manager.pushback_collectable(95, 2, worldptr);
	object_manager.pushback_collectable(103, 2, worldptr);
	object_manager.pushback_enemy(104, 5, worldptr);
	object_manager.init_enemy_range(94, 5, 2, 3, true);
	object_manager.pushback_collectable(95, 8, worldptr);
	object_manager.pushback_collectable(103, 8, worldptr);
	object_manager.pushback_enemy(94, 11, worldptr);
	object_manager.init_enemy_range(104, 11, 2, 4, true);
	object_manager.pushback_collectable(95, 14, worldptr);
	object_manager.pushback_collectable(103, 14, worldptr);
	object_manager.pushback_enemy(104, 17, worldptr);
	object_manager.init_enemy_range(94, 17, 2, 5, true);
	object_manager.pushback_floor(5.0f, 0.5f, 0.5f, pb, 109, 17, worldptr);
	// Part 5
	object_manager.pushback_enemy(115, 13, worldptr);
	object_manager.init_enemy_range(0, 18, 2, 6, false);
	object_manager.pushback_floor(5.0f, 0.5f, 0.5f, pb, 122, 14, worldptr);
	object_manager.pushback_collectable(122, 17, worldptr);
	object_manager.pushback_enemy(129, 7, worldptr);
	object_manager.init_enemy_range(0, 15, 2, 7, false);
	object_manager.pushback_floor(5.0f, 0.5f, 0.5f, pb, 135, 11, worldptr);
	object_manager.pushback_collectable(135, 14, worldptr);
	object_manager.pushback_floor(5.0f, 0.5f, 0.5f, pb, 122, 8, worldptr);
	object_manager.pushback_enemy(117, 9, worldptr);
	object_manager.init_enemy_range(127, 0, 2, 8, true);
	object_manager.pushback_collectable(122, 11, worldptr);
	object_manager.pushback_collectable(118, 11, worldptr);
	object_manager.pushback_collectable(126, 11, worldptr);
	object_manager.pushback_floor(5.0f, 0.5f, 0.5f, pb, 148, 8, worldptr);
	object_manager.pushback_collectable(148, 11, worldptr);
	// Part 6
	object_manager.pushback_enemy(135, 4, worldptr);
	object_manager.init_enemy_range(0, 2, 2, 9, false);
	object_manager.pushback_moving_floor(5.0f, 0.5f, 0.5f, pb, 135, 3, worldptr);
	object_manager.init_moving_floor_range(175, 0, 5, 3, true);
	object_manager.pushback_collectable(148, 6, worldptr);
	object_manager.pushback_floor(5.0f, 0.5f, 0.5f, pb, 125, 0, worldptr);
	object_manager.pushback_collectable(121, 3, worldptr);
	object_manager.pushback_collectable(125, 3, worldptr);
	object_manager.pushback_collectable(129, 3, worldptr);
	object_manager.pushback_enemy(155, 4, worldptr);
	object_manager.init_enemy_range(0, 2, 2, 10, false);
	object_manager.pushback_collectable(160, 6, worldptr);
	object_manager.pushback_enemy(165, 2, worldptr);
	object_manager.init_enemy_range(0, 4, 2, 11, false);
	object_manager.pushback_collectable(170, 6, worldptr);
	object_manager.init_goal(5.0f, 0.5f, 0.5f, pb, 188, 3, worldptr);

	// Initialize Models, after all objects have been created
	object_manager.init_models(pb, platref);
}

void Game_Screen::Update(b2World* worldptr, gef::InputManager* inputptr, gef::AudioManager* audioptr, float frame_time)
{
	// Updates timer for player
	timer += frame_time;

	// Updates world simulation
	worldptr->Step(timeStep, velocityIterations, positionIterations);

	// Updates all objects in the game
	object_manager.update();

	// Updates Keyboard and Collision Check
	KeyboardUpdate(inputptr, audioptr);
	CollisionUpdate(worldptr, audioptr);

	// Checks if player is on a platform, and changes whether the player is pushed forwards or backwards based on the Platform's Axis variable
	if (plat_num != -1)
	{
		ChangePlatformSpeed(plat_num, object_manager.moving_floors[plat_num].AxisX);
	}

	// Sends signal to Screen Manager to change to dead state if the player has no lives left
	if (player_lives < 1)
	{
		changeDead = true;
	}
}

void Game_Screen::KeyboardUpdate(gef::InputManager* inputptr, gef::AudioManager* audioptr)
{
	auto keyboard = inputptr->keyboard();

	    // Spacebar
	if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_SPACE) && touching == true)
	{
		// Chuck player in air 
		object_manager.player_object.player_body_->ApplyForceToCenter(b2Vec2(0, 800), true);
		touching = false;
	}   // Right Arrow
	else if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_RIGHT))
	{
		if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_LSHIFT))
		{
			object_manager.player_object.player_body_->SetLinearVelocity(b2Vec2(8 + plat_speed, object_manager.player_object.player_body_->GetLinearVelocity().y));
		}
		else
		{
			object_manager.player_object.player_body_->SetLinearVelocity(b2Vec2(5 + plat_speed, object_manager.player_object.player_body_->GetLinearVelocity().y));
		}
	}   // Left Arrow
	else if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_LEFT))
	{
		if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_LSHIFT))
		{
			object_manager.player_object.player_body_->SetLinearVelocity(b2Vec2(-8 + plat_speed, object_manager.player_object.player_body_->GetLinearVelocity().y));
		}
		else
		{
			object_manager.player_object.player_body_->SetLinearVelocity(b2Vec2(-5 + plat_speed, object_manager.player_object.player_body_->GetLinearVelocity().y));
		}
	}
	else
	{
		// If no input is detected, set velocity to natural state (including platform speed if on moving platform)
		object_manager.player_object.player_body_->SetLinearVelocity(b2Vec2(0 + plat_speed, object_manager.player_object.player_body_->GetLinearVelocity().y));
	}

	// If player falls off
	if (object_manager.player_object.player_body_->GetPosition().y < -20)
	{
		// Lower Player Lives and play sound effect, then set position back to spawn
		player_lives--;
		audioptr->PlaySample(falling_wav, false);
		object_manager.player_object.player_body_->SetTransform(b2Vec2(0, 4), 0);
	}

	// 'P' Key
	if (keyboard->IsKeyDown(gef::Keyboard::KeyCode::KC_P))
	{
		// Sends Signal to Screen Manage to set game state to Pause
		changePause = true;
	}
}

void Game_Screen::CollisionUpdate(b2World* worldptr, gef::AudioManager* audioptr)
{
	// collision detection
	// get the head of the contact list
	b2Contact* contact = worldptr->GetContactList();
	// get contact count
	int contact_count = worldptr->GetContactCount();

	for (int contact_num = 0; contact_num < contact_count; ++contact_num)
	{
		if (contact->IsTouching())
		{

			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();
			GameObject* gameObjectA = (GameObject*)bodyA->GetUserData().pointer;
			GameObject* gameObjectB = (GameObject*)bodyB->GetUserData().pointer;

			// If colliding object is GROUND and PLAYER
			if (gameObjectA->object_type_ == GAME_OBJECT_TYPE::PLAYER && gameObjectB->object_type_ == GAME_OBJECT_TYPE::GROUND
				|| gameObjectA->object_type_ == GAME_OBJECT_TYPE::GROUND && gameObjectB->object_type_ == GAME_OBJECT_TYPE::PLAYER)
			{
				// Sets touching to true so player can jump, sets plat num to -1 and speed to 0
				touching = true;
				plat_num = -1;
				plat_speed = 0;
			}

			// If colliding object is ENEMY and PLAYER
			if (gameObjectA->object_type_ == GAME_OBJECT_TYPE::ENEMY && gameObjectB->object_type_ == GAME_OBJECT_TYPE::PLAYER
				|| gameObjectA->object_type_ == GAME_OBJECT_TYPE::PLAYER && gameObjectB->object_type_ == GAME_OBJECT_TYPE::ENEMY)
			{
				// Lower player lives, play sound effect
				player_lives--;;
				audioptr->PlaySample(explosion_wav, false);

				// Checks all enemies to see which enemy touched the player
				for (int i = 0; i < object_manager.enemies.size(); i++)
				{
					if (bodyA->GetPosition() == object_manager.enemies[i].enemy_body_->GetPosition()
						|| bodyB->GetPosition() == object_manager.enemies[i].enemy_body_->GetPosition())
					{
						// Kill that specific enemy
						object_manager.enemies[i].kill();
					}
				}
			}

			// If colliding object is COLLECTABLE and PLAYER
			if (gameObjectA->object_type_ == GAME_OBJECT_TYPE::COLLECTABLE && gameObjectB->object_type_ == GAME_OBJECT_TYPE::PLAYER
				|| gameObjectA->object_type_ == GAME_OBJECT_TYPE::PLAYER && gameObjectB->object_type_ == GAME_OBJECT_TYPE::COLLECTABLE)
			{
				// Increase player coins, play sound effect
				coins++;
				audioptr->PlaySample(coin_wav, false);

				// Checks all collectables to see which enemy touched the player
				for (int i = 0; i < object_manager.collectables.size(); i++)
				{
					if (bodyA->GetPosition() == object_manager.collectables[i].collectable_body_->GetPosition()
						|| bodyB->GetPosition() == object_manager.collectables[i].collectable_body_->GetPosition())
					{
						// Kill that specific collectable
						object_manager.collectables[i].kill();
					}
				}
			}

			// If colliding object is PLATFORM and PLAYER
			if (gameObjectA->object_type_ == GAME_OBJECT_TYPE::PLATFORM && gameObjectB->object_type_ == GAME_OBJECT_TYPE::PLAYER
				|| gameObjectA->object_type_ == GAME_OBJECT_TYPE::PLAYER && gameObjectB->object_type_ == GAME_OBJECT_TYPE::PLATFORM)
			{
				// Sets touching to true so player can jump
				touching = true;
				for (int i = 0; i < object_manager.moving_floors.size(); i++)
				{
					// Checks all Platforms to see which one the player is touching
					if (bodyA->GetPosition() == object_manager.moving_floors[i].ground_body_->GetPosition()
						|| bodyB->GetPosition() == object_manager.moving_floors[i].ground_body_->GetPosition())
					{
						// Checks that the axis the platform is moving on is the X axis
						if (object_manager.moving_floors[i].Axis_ == true)
						{
							// Sets plat_num to the platform number found
							plat_num = i;
						}
					}
				}
			}

			// If colliding object is GOAL and PLAYER
			if (gameObjectA->object_type_ == GAME_OBJECT_TYPE::GOAL && gameObjectB->object_type_ == GAME_OBJECT_TYPE::PLAYER
				|| gameObjectA->object_type_ == GAME_OBJECT_TYPE::PLAYER && gameObjectB->object_type_ == GAME_OBJECT_TYPE::GOAL)
			{
				// Sends signal to Screen Manager to swap to Win screen
				changeWin = true;
			}
		}
		// Get next contact point
		contact = contact->GetNext();
	}
}

void Game_Screen::RenderGame(gef::Renderer3D* renderptr3D, gef::Platform& platref, gef::SpriteRenderer* renderptr, gef::Font* fontptr)
{
	// setup camera

	// Sets project matrix projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platref.width() / (float)platref.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = platref.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderptr3D->set_projection_matrix(projection_matrix);

	// Sets view based on the Players' position
	gef::Vector4 camera_eye(object_manager.player_object.player_body_->GetPosition().x - 5.0f, object_manager.player_object.player_body_->GetPosition().y + 1.0f, 15.0f);
	gef::Vector4 camera_lookat(object_manager.player_object.player_body_->GetPosition().x, object_manager.player_object.player_body_->GetPosition().y, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderptr3D->set_view_matrix(view_matrix);

	// Renders all objects
	renderptr3D->Begin();
	object_manager.render(renderptr3D);
	renderptr3D->End();

	// Renders Text to show players' Lives and Coins
	renderptr->Begin(false);
	RenderHUD(renderptr, fontptr);
	renderptr->End();

}

void Game_Screen::RenderHUD(gef::SpriteRenderer* renderptr, gef::Font* fontptr)
{
	if (fontptr)
	{
		// Shows player's lives and coins in text on screen
		fontptr->RenderText(renderptr, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xff00ffff, gef::TJ_LEFT, "Coins: %.0f", coins);
		fontptr->RenderText(renderptr, gef::Vector4(0.0f, 510.0f, -0.9f), 1.0f, 0xff0000ff, gef::TJ_LEFT, "Lives: %.0f", player_lives);
	}
}

void Game_Screen::ChangeSpeed(int n)
{
	// Changes enemy speed
	object_manager.change_enemy_speed(n);
}

void Game_Screen::ChangePlatformSpeed(int platNum, int axisX)
{
	// Checks that the floor is moving positively along the x axis, if not sets plat_speed to negative for the player, instead of positive
	if (object_manager.moving_floors[platNum].AxisX == 1)
	{
		if (touching == true)
		{
			plat_speed = object_manager.moving_floors[platNum].speed;
		}
	}
	else
	{
		if (touching == true)
		{
			plat_speed = -object_manager.moving_floors[platNum].speed;
		}
	}
}