#pragma once
#include "base_screen.h"

class Menu_Screen : public Screen
{
public:
	// Initialize screen, using file
	void Init(char* filename, gef::Platform& platref);

	// Overwritten render screen
	void Render(gef::SpriteRenderer* renderptr) override;
};
