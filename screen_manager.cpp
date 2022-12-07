#include "screen_manager.h"

void Screen_Manager::Init(gef::Platform& platref, gef::SpriteRenderer* renderptr, PrimitiveBuilder* pb, b2World* worldptr, gef::AudioManager* audioptr)
{
	// Plays Menu music
	audioptr->LoadMusic("audio/music/stomping-rock-four-shots.wav", platref);
	audioptr->PlayMusic();

	// Initialze game state, and tells button manager
	game_state = GAME_STATES::MENU;
	button_manager.game_state = game_state;

	// Intialize all screens
	game_screen.Init(pb, worldptr, platref, audioptr);
	pause_screen.Init("base_textures/pause.png", platref);
	menu_screen.Init("base_textures/title.png", platref);
	controls_screen.Init("base_textures/controls.png", platref);
	splash_screen.Init("base_textures/splash.png", platref);
	options_screen.Init("base_textures/options.png", platref);
	dead_screen.Init("base_textures/dead.png", platref);
	win_screen.Init("base_textures/win.png", platref);

	// ***Buttons for Menu***
	// Start Button
	button_manager.pushback_button(128, 64, platref.width() / 4, (platref.height() / 3) * 2, 1, 1, "base_textures/button1.png", platref);
	// Controls Button
	button_manager.pushback_button(128, 64, (platref.width() / 4) * 3, (platref.height() / 3) * 2, 1, 2, "base_textures/button3.png", platref);

	// ***Buttons for Pause***
	// Continue Button
	button_manager.pushback_button(128, 64, platref.width() / 4, (platref.height() / 4) * 3, 2, 1, "base_textures/button2.png", platref);
	// Controls Button
	button_manager.pushback_button(128, 64, (platref.width() / 4) * 3, (platref.height() / 4) * 3, 2, 2, "base_textures/button3.png", platref);
	// Options Button
	button_manager.pushback_button(128, 64, (platref.width() / 4) * 2, (platref.height() / 4) * 3, 2, 3, "base_textures/button5.png", platref);

	// ***Buttons for Controls***
	// Back Button
	button_manager.pushback_button(128, 64, (platref.width() / 6) * 5, (platref.height() / 8) * 7, 3, 1, "base_textures/button4.png", platref);

	// ***Buttons for Options***
	// Back Button
	button_manager.pushback_button(128, 64, (platref.width() / 6) * 1, (platref.height() / 8) * 7, 4, 1, "base_textures/button4.png", platref);
	// Mute Button
	button_manager.pushback_button(128, 64, (platref.width() / 6) * 5, (platref.height() / 8) * 7, 4, 2, "base_textures/button6.png", platref);
	// Unmute Button
	button_manager.pushback_button(128, 64, (platref.width() / 6) * 5, (platref.height() / 8) * 5, 4, 3, "base_textures/button9.png", platref);
	// High Volume Button
	button_manager.pushback_button(128, 64, (platref.width() / 6) * 1, (platref.height() / 8) * 1, 4, 4, "base_textures/button11.png", platref);
	// Reset Volume Button
	button_manager.pushback_button(128, 64, (platref.width() / 6) * 1, (platref.height() / 8) * 3, 4, 5, "base_textures/button12.png", platref);
	// Low Volume Button
	button_manager.pushback_button(128, 64, (platref.width() / 6) * 1, (platref.height() / 8) * 5, 4, 6, "base_textures/button10.png", platref);
	// Low Difficulty Button
	button_manager.pushback_button(128, 64, (platref.width() / 6) * 5, (platref.height() / 8) * 3, 4, 7, "base_textures/button14.png", platref);
	// High Difficulty Button
	button_manager.pushback_button(128, 64, (platref.width() / 6) * 5, (platref.height() / 8) * 1, 4, 8, "base_textures/button13.png", platref);
	// Reset Difficulty Button
	button_manager.pushback_button(128, 64, (platref.width() / 6) * 3, (platref.height() / 8) * 7, 4, 9, "base_textures/button15.png", platref);

	
}

void Screen_Manager::Update(gef::Vector2 tp, b2World* worldptr, gef::InputManager* inputptr, gef::AudioManager* audioptr, gef::Platform& platref, float frame_time)
{
	// Sets Touch Position
	tp_ = tp;

	// Updates specific screens based on what Game State the game is currently in
	switch (game_state)
	{
	case GAME_STATES::MENU:
		// Updates button manager with the appropriate Touch Input and what Render Number buttons should have to update
		button_manager.Update(tp_, 1, audioptr);
		break;
	case GAME_STATES::SPLASH:
		splash_screen.Update(frame_time);
		break;
	case GAME_STATES::GAME:
		game_screen.Update(worldptr, inputptr, audioptr, frame_time);
		break;
	case GAME_STATES::DEAD:
		break;
	case GAME_STATES::PAUSE:
		button_manager.Update(tp_, 2, audioptr);
		break;
	case GAME_STATES::CONTROLS:
		button_manager.Update(tp_, 3, audioptr);
		break;
	case GAME_STATES::OPTIONS:
		button_manager.Update(tp_, 4, audioptr);
		break;
	case GAME_STATES::WIN:
		break;
	}

	tp_ = gef::Vector2(0, 0);

	// Accepts information if a change in screen is required
	if (button_manager.change == true)
	{
		// Changes screen based on button press
		game_state = button_manager.temp_state;
		button_manager.game_state = button_manager.temp_state;
		button_manager.change = false;
	}
	if (splash_screen.change == true)
	{
		// Splash Screen Signal
		// Changes screen and Music after recieving a signal from Splash
		if (button_manager.musicPlaying)
		{
			// Changes the music
			Music_Change(audioptr, platref, 4);
		}
		// Informs both the Screen Manager and the Button Manager
		game_state = GAME_STATES::GAME;
		button_manager.game_state = game_state;
		splash_screen.change = false;
	}
	if (game_screen.changePause == true)
	{
		// Game Screen Signal Pause
		if (button_manager.musicPlaying)
		{
			Music_Change(audioptr, platref, 3);
		}
		game_state = GAME_STATES::PAUSE;
		button_manager.game_state = game_state;
		game_screen.changePause = false;
	}
	if (game_screen.changeDead == true)
	{
		// Game Screen Signal Dead
		game_state = GAME_STATES::DEAD;
		if (button_manager.musicPlaying)
		{
			Music_Change(audioptr, platref, 2);
		}
		game_screen.changeDead = false;
	}
	if (game_screen.changeWin == true)
	{
		// Game Screen Signal Win
		game_state = GAME_STATES::WIN;
		if (button_manager.musicPlaying)
		{
			Music_Change(audioptr, platref, 5);
		}
		game_screen.changeWin = false;
	}
	if (button_manager.changeMusicBack == true)
	{
		// Change Music Back after Pause
		if (button_manager.musicPlaying)
		{
			Music_Change(audioptr, platref, 4);
		}
		button_manager.changeMusicBack = false;
	}
	if (button_manager.changeDifficulty == true)
	{
		// Button Manager Signal
		game_screen.ChangeSpeed(button_manager.difficulty);
		button_manager.changeDifficulty = false;
	}
}

void Screen_Manager::Render(gef::SpriteRenderer* renderptr, gef::Renderer3D* renderptr3D, gef::Platform& platref, gef::Font* fontptr)
{
	// Renders specific screen depending on what Game State the game is currently in
	switch (game_state)
	{
	case GAME_STATES::MENU:
		menu_screen.Render(renderptr);
		button_manager.Render(renderptr, 1);
		break;
	case GAME_STATES::SPLASH:
		splash_screen.Render(renderptr);
		break;
	case GAME_STATES::GAME:
		game_screen.RenderGame(renderptr3D, platref, renderptr, fontptr);
		break;
	case GAME_STATES::DEAD:
		// Informs the dead screen of what coins the player got, and how long the player took
		dead_screen.coins = game_screen.coins;
		dead_screen.timer = game_screen.timer;
		dead_screen.RenderDead(renderptr, fontptr);
		break;
	case GAME_STATES::PAUSE:
		pause_screen.Render(renderptr);
		button_manager.Render(renderptr, 2);
		break;
	case GAME_STATES::CONTROLS:
		controls_screen.Render(renderptr);
		button_manager.Render(renderptr, 3);
		break;
	case GAME_STATES::OPTIONS:
		options_screen.Render(renderptr);
		button_manager.Render(renderptr, 4);
		break;
	case GAME_STATES::WIN:
		// Informs the win screen of what coins the player got, and how long the player took
		win_screen.coins = game_screen.coins;
		win_screen.timer = game_screen.timer;
		win_screen.RenderWin(renderptr, fontptr);
		break;
	}
}

void Screen_Manager::Music_Change(gef::AudioManager* audioptr, gef::Platform& platref, int n)
{
	// Changes the music based on input
	switch (n)
	{
	case 1:
		audioptr->LoadMusic("audio/music/stomping-rock-four-shots.wav", platref);
		break;
	case 2:
		audioptr->LoadMusic("audio/music/loneliness_of_the_winner.wav", platref);
		break;
	case 3:
		audioptr->LoadMusic("audio/music/morning-garden-acoustic-chill.wav", platref);
		break;
	case 4:
		audioptr->LoadMusic("audio/music/electronic-rock-king-around-here.wav", platref);
		break;
	case 5:
		audioptr->LoadMusic("audio/music/upbeat-rock-good-news.wav", platref);
		break;
	}

	audioptr->PlayMusic();
}