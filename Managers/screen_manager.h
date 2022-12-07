#pragma once
#include "pause_screen.h"
#include "menu_screen.h"
#include "controls_screen.h"
#include "game_screen.h"
#include "splash_screen.h"
#include "options_screen.h"
#include "dead_screen.h"
#include "win_screen.h"
#include "game_states.h"
#include "button_manager.h"
#include "audio/audio_manager.h"

class Screen_Manager
{
public:
	// Initializes all the screens, and the buttons
	void Init(gef::Platform& platref, gef::SpriteRenderer* renderptr, PrimitiveBuilder* pb, b2World* worldptr, gef::AudioManager* audioptr);

	void Update(gef::Vector2 tp, b2World* worldptr, gef::InputManager* inputptr, gef::AudioManager* audioptr, gef::Platform& platref, float frame_time);

	void Render(gef::SpriteRenderer* renderptr, gef::Renderer3D* renderptr3D, gef::Platform& platref, gef::Font* fontptr);

	void Music_Change(gef::AudioManager* audioptr, gef::Platform& platref, int n);

private:
	// Stores Screens
	Pause_Screen pause_screen;
	Menu_Screen menu_screen;
	Controls_Screen controls_screen;
	Game_Screen game_screen;
	Splash_Screen splash_screen;
	Options_Screen options_screen;
	Dead_Screen dead_screen;
	Win_Screen win_screen;

	// Stores Button Manager
	Button_Manager button_manager;

	// Stores Game State
	GAME_STATES game_state;

	// Stores Touch Position, to be given to the Button Manager
	gef::Vector2 tp_;
};
