#pragma once
#include "load_texture.h"
#include "graphics/texture.h"
#include "graphics/sprite.h"
#include "graphics/sprite_renderer.h"

class Screen
{
public:
	// Base screen that all other screens inherit from
	
	// Overwritable render function that other screens use to show their sprite
	virtual void Render(gef::SpriteRenderer* renderptr);

	// Stores Texture and Sprite information
	gef::Sprite screen_sprite_;
	gef::Texture* screen_texture;
};