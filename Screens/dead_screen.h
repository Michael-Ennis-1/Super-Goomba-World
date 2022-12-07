#pragma once
#include "base_screen.h"
#include "graphics/font.h"

class Dead_Screen : public Screen
{
public:
	// Initialize screen, using file
	void Init(char* filename, gef::Platform& platref);

	// Renders Screen
	void RenderDead(gef::SpriteRenderer* renderptr, gef::Font* fontptr);

	// Renders Text
	void DrawHUD(gef::SpriteRenderer* renderptr, gef::Font* fontptr);

	// Stores player collected Coins and Timer
	float coins, timer;
private:
};
#pragma once
