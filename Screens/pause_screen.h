#pragma once
#include "base_screen.h"

class Pause_Screen : public Screen
{
public:
	// Initialize screen, using file
	void Init(char* filename, gef::Platform& platref);

	// Renders Screen
	void Render(gef::SpriteRenderer* renderptr) override;
};
