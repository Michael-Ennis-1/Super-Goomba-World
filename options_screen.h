#pragma once
#include "game_screen.h"

class Options_Screen : public Screen
{
public:
	// Initialize screen, using file
	void Init(char* filename, gef::Platform& platref);
	// Renders Screen
	void Render(gef::SpriteRenderer* renderptr) override;
};
