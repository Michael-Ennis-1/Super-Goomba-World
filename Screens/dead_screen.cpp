#include "dead_screen.h"
void Dead_Screen::Init(char* filename, gef::Platform& platref)
{
	// Creates texture from file, the sets Screen Sprite to the size of platform and positions it in the centre
	screen_texture = CreateTextureFromPNG(filename, platref);
	screen_sprite_.set_texture(screen_texture);
	screen_sprite_.set_height(platref.height());
	screen_sprite_.set_width(platref.width());
	screen_sprite_.set_position(gef::Vector4(platref.width() / 2, platref.height() / 2, 0));
}

void Dead_Screen::RenderDead(gef::SpriteRenderer* renderptr, gef::Font* fontptr)
{
	// Renders Screen Sprite
	renderptr->Begin();
	renderptr->DrawSprite(screen_sprite_);
	renderptr->End();

	// Renders text on screen, without using buffer so it displays over everything else
	renderptr->Begin(false);
	DrawHUD(renderptr, fontptr);
	renderptr->End();
}

void Dead_Screen::DrawHUD(gef::SpriteRenderer* renderptr, gef::Font* fontptr)
{
	if (fontptr)
	{
		// Renders text of Player's collected coins, and how long they took
		fontptr->RenderText(renderptr, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xff00ffff, gef::TJ_LEFT, "Coins: %.0f", coins);
		fontptr->RenderText(renderptr, gef::Vector4(0.0f, 510.0f, -0.9f), 1.0f, 0xff00ff00, gef::TJ_LEFT, "Time Taken in Seconds: %.2f", timer);

		// Calculates Score
		float score = coins * 100 - timer;

		// Renders player Score
		fontptr->RenderText(renderptr, gef::Vector4(425.0f, 510.0f, -0.9f), 1.0f, 0xffffff00, gef::TJ_LEFT, "Score: %.0f", score);
	}
}