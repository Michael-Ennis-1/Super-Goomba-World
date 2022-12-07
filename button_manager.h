#pragma once
#include <vector>
#include <graphics/sprite_renderer.h>
#include "game_states.h"
#include "audio/audio_manager.h"
#include "button.h"


class Button_Manager
{
public:
	// Defines a button and pushes it onto the vector stack
	void pushback_button(int sizeX, int sizeY, float posX, float posY, int rN, int t, char* filename, gef::Platform& platref);

	// Checks if a button has been touched, based on it's Render Number, also changes the music based on the screen it swaps to
	void Update(gef::Vector2 tp, int rNum_, gef::AudioManager* audioptr);

	// Renders buttons depending on their Render Number
	void Render(gef::SpriteRenderer* rendererptr, int rN);

	// Returns the size or position of a button
	int ReturnPosition(char axis, int n);
	int ReturnSize(char axis, int n);

	// Turns music off. Also changes volume, or resets it
	void Audio_Change(gef::AudioManager* audioptr, bool volume_music, bool increase_decrease, bool reset_override);

	// Stores all instances of buttons
	std::vector<Button> buttons;

	// Stores the difficulty of the game
	int difficulty = 2;

	// Tells the Game Screen to run certain tasks, Changes
	bool change = false, changeMusicBack = false, musicPlaying = true, changeDifficulty = false;

	// Stores the Game's state, the Previous State and a Temporary state
	GAME_STATES game_state, previous_state, temp_state;

private:
	// Stores Button information
	Button b;

	// Stores volume
	float vol = 3.0f;
};
