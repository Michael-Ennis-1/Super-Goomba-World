#include "pause_screen.h"

void Pause_Screen::Init(char *filename, gef::Platform& platref)
{
	// Creates texture from file, the sets Screen Sprite to the size of platform and positions it in the centre
	screen_texture = CreateTextureFromPNG(filename, platref);
	screen_sprite_.set_texture(screen_texture);
	screen_sprite_.set_height(platref.height());
	screen_sprite_.set_width(platref.width());
	screen_sprite_.set_position(gef::Vector4(platref.width() / 2, platref.height() / 2, 0));
}

void Pause_Screen::Render(gef::SpriteRenderer* renderptr)
{
	// Renders Screen Sprite
	renderptr->Begin();
	renderptr->DrawSprite(screen_sprite_);
	renderptr->End();
}