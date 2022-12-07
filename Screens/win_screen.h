#pragma once
#include "base_screen.h"
#include "graphics/font.h"

class Win_Screen : public Screen
{
public:
	// Initialize screen, using file
	void Init(char* filename, gef::Platform& platref);

	// Renders Screen
	void RenderWin(gef::SpriteRenderer* renderptr, gef::Font* fontptr);

	// Renders player Coins, Time and Score as Text
	void DrawHUD(gef::SpriteRenderer* renderptr, gef::Font* fontptr);

	// Stores player Coins and Timer
	float coins, timer;
};
