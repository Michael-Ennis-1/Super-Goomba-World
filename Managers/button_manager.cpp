#include "button_manager.h"

void Button_Manager::pushback_button(int sizeX, int sizeY, float posX, float posY, int rN, int t, char* filename, gef::Platform& platref)
{
	// Creates an instance of button, and pushes it into the vector stack
	b.Init(sizeX, sizeY, posX, posY, rN, t, filename, platref);
	buttons.push_back(b);
}

void Button_Manager::Update(gef::Vector2 tp, int rNum_, gef::AudioManager* audioptr)
{
	// Checks all buttons from the vector stack
	for (int i = 0; i < buttons.size(); i++)
	{
		// As a button's position is the centre, we have to test all edges to make sure the touch is at the correct position. If it is, then it checks the type
		// and if it is the correct type, then it checks if the screen is in the correct one. If it is, it changes it's temp state, and informs the game screen
		// to change screens based on it's temp
		if (tp.x > buttons[i].getX() - (buttons[i].getSizeX() / 2) && tp.x < buttons[i].getX() + (buttons[i].getSizeX() / 2) && buttons[i].rNum == rNum_)
		{
			if (tp.y > buttons[i].getY() - (buttons[i].getSizeY() / 2) && tp.y < buttons[i].getY() + (buttons[i].getSizeY() / 2))
			{
				if (buttons[i].type == 1)
				{
					// Menu Button 1 (Play)
					if (game_state == GAME_STATES::MENU)
					{
						temp_state = GAME_STATES::SPLASH;
						change = true;
					}
					// Pause Button 1 (Back)
					if (game_state == GAME_STATES::PAUSE)
					{
						temp_state = GAME_STATES::GAME;
						change = true;
						changeMusicBack = true;
					}
					// Controls Button 1 (Back)
					if (game_state == GAME_STATES::CONTROLS)
					{
						temp_state = previous_state;
						change = true;
					}
					// Options Button 1 (Back)
					if (game_state == GAME_STATES::OPTIONS)
					{
						temp_state = previous_state;
						change = true;
					}
				}
				if (buttons[i].type == 2)
				{
					// Menu Button 2 (Controls)
					if (game_state == GAME_STATES::MENU)
					{
						temp_state = GAME_STATES::CONTROLS;
						previous_state = GAME_STATES::MENU;
						change = true;
					}
					// Pause Button 2 (Controls)
					if (game_state == GAME_STATES::PAUSE)
					{
						temp_state = GAME_STATES::CONTROLS;
						previous_state = GAME_STATES::PAUSE;
						change = true;
					}
					// Options Button 2 (Mute)
					if (game_state == GAME_STATES::OPTIONS)
					{
						if (musicPlaying == true)
						{
							Audio_Change(audioptr, false, false, false);
							musicPlaying = false;
						}
					}
				}
				if (buttons[i].type == 3)
				{
					// Pause Button 3 (Options)
					if (game_state == GAME_STATES::PAUSE)
					{
						temp_state = GAME_STATES::OPTIONS;
						previous_state = GAME_STATES::PAUSE;
						change = true;
					}
					// Options Button 3 (Unmute)
					if (game_state == GAME_STATES::OPTIONS)
					{
						musicPlaying = true;
						Audio_Change(audioptr, false, true, false);
					}
				}
				if (buttons[i].type == 4)
				{
					// Options Button 4 (High Volume)
					Audio_Change(audioptr, true, true, false);
				}
				if (buttons[i].type == 5)
				{
					// Options Button 5 (Reset Volume)
					Audio_Change(audioptr, true, true, true);
				}
				if (buttons[i].type == 6)
				{
					// Options Button 6 (Low Volume)
					Audio_Change(audioptr, true, false, false);
				}
				if (buttons[i].type == 7)
				{
					// Options Button 7 (Low Difficulty)
					difficulty = 1;
					changeDifficulty = true;
				}
				if (buttons[i].type == 8)
				{
					// Options Button 8 (High Difficulty)
					difficulty = 5;
					changeDifficulty = true;
				}
				if (buttons[i].type == 9)
				{
					// Options Button 9 (Reset Difficulty)
					difficulty = 2;
					changeDifficulty = true;
				}
			}
		}
	}
}

void Button_Manager::Render(gef::SpriteRenderer* rendererptr, int rN)
{
	// Renders all the buttons, depending on their Render Number
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i].rNum == rN)
		{
			rendererptr->DrawSprite(buttons[i].button);
		}
	}
}

int Button_Manager::ReturnPosition(char axis, int n)
{
	// Returns the position of a specific button, depending on it's axis
	if (axis == 'y')
	{
		return buttons[n].getY();
	}
	if (axis == 'x')
	{
		return buttons[n].getX();
	}
}

int Button_Manager::ReturnSize(char axis, int n)
{
	// Returns the size of a specific button, depending on it's axis
	if (axis == 'y')
	{
		return buttons[n].getSizeY();
	}
	if (axis == 'x')
	{
		return buttons[n].getSizeX();
	}
}

void Button_Manager::Audio_Change(gef::AudioManager* audioptr, bool volume_music, bool increase_decrease, bool reset_override)
{
	// Increases or Decreases the volume, and turns on/off music 
	if (volume_music == true && reset_override == false)
	{
		if (increase_decrease == true)
		{
			vol = 20.0f;
		}
		else
		{
			vol = 1.0f;
		}
	}
	else if (volume_music == false)
	{
		if (increase_decrease == true)
		{
			audioptr->PlayMusic();
		}
		else
		{
			audioptr->StopMusic();
		}
	}
	else
	{
		vol = 10.0f;
	}

	// Sets the volume
	audioptr->SetMasterVolume(vol);
}