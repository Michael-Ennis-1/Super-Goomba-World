#pragma once
#include "game_screen.h"

class Splash_Screen : public Screen
{
public:
	// Initialize screen, using file
	void Init(char* filename, gef::Platform& platref);

	// Updates timer, based on frame_time
	void Update(float frame_time);

	// Renders Screen
	void Render(gef::SpriteRenderer* renderptr) override;

	// Stores Signal
	bool change = false;
private:
	// Stores Splash Screen Timer
	float timer_ = 3;
};
