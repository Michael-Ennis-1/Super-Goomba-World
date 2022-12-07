#pragma once
#include "graphics/sprite.h"
#include "load_texture.h"

class Button
{
public:
	// Initialize button at a certain size, certain position, when to render, where it leads to, a file name and on a platform
	void Init(int sizeX, int sizeY, float posX, float posY, int renderNum, int t, char* file, gef::Platform& platref);

	// Returns button position X and Y
	int getX();
	int getY();

	// Returns button size X and Y
	int getSizeX();
	int getSizeY();

	// Button Sprite variable
	gef::Sprite button;

	// Variables to store Render Numberand  it's Type (Where it leads to)
	int rNum, type;
};
