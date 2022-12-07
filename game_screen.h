#pragma once
#include "base_screen.h"
#include "objectManager.h"
#include "audio/audio_manager.h"
#include "input/keyboard.h"
#include "input/input_manager.h"
#include "graphics/font.h"
#include <box2d/Box2D.h>
#include <maths/math_utils.h>

class Game_Screen : public Screen
{
public:
	// Initialize sound effects and all the objects in the world, as well as their models
	void Init(PrimitiveBuilder* pb, b2World* worldptr, gef::Platform& platref, gef::AudioManager* audioptr);

	// Update Object Manager, World, Keyboard, Collision etc
	void Update(b2World* worldptr, gef::InputManager* inputptr, gef::AudioManager* audioptr, float frame_time);

	// Update Keyboard Input
	void KeyboardUpdate(gef::InputManager* inputptr, gef::AudioManager* audioptr);

	// Update Collision Detection
	void CollisionUpdate(b2World* worldptr, gef::AudioManager* audioptr);

	// Render Game
	void RenderGame(gef::Renderer3D* renderptr3D, gef::Platform& platref, gef::SpriteRenderer* renderptr, gef::Font* fontptr);

	// Render Text on screen
	void RenderHUD(gef::SpriteRenderer* renderptr, gef::Font* fontptr);

	// Change Enemy Speed
	void ChangeSpeed(int n);

	// Change Player Platform Speed
	void ChangePlatformSpeed(int platNum, int axisX);

	// Stores players lives, coins and timer
	float player_lives = 3, coins = 0, timer = 0;

	// Send Signals to signal screen manager to change screens
	bool changePause = false, changeDead = false, changeWin = false;;

private:
	// Stores World Step variables
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// Store Sounds
	Int32 coin_wav;
	Int32 explosion_wav;
	Int32 falling_wav;

	// Store Platform Speed and Number
	int plat_speed = 0;
	int plat_num = -1;

	// Create Object Manager
	Manager object_manager;

	// Stores if Player is touching floor
	bool touching = false;
};
