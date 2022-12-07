#include "button.h"

void Button::Init(int sizeX, int sizeY, float posX, float posY, int renderNum, int t, char* file, gef::Platform& platref)
{
	// Creates button's texture, height, width and sets its position, render number and type, based on user input
	button.set_texture(CreateTextureFromPNG(file, platref));
	button.set_height(sizeY);
	button.set_width(sizeX);
	button.set_position(gef::Vector4(posX, posY, 0));
	rNum = renderNum;
	type = t;
}

int Button::getX()
{
	// Returns button position x
	return button.position().x();
}

int Button::getY()
{
	// Returns button position y
	return button.position().y();
}

int Button::getSizeX()
{
	// Returns button width
	return button.width();
}

int Button::getSizeY()
{
	// Returns button height
	return button.height();
}
