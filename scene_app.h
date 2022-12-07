#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <box2d/Box2D.h>
#include <input/keyboard.h>
#include <input/input_manager.h>
#include <input/touch_input_manager.h>
#include "audio/audio_manager.h"
#include "screen_manager.h"

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

class SceneApp : public gef::Application
{
public:
	// Initialize all managers to NULL
	SceneApp(gef::Platform& platform);

	// Initialize Everything Necessary
	void Init();

	// Destroy Everything after game has completed
	void CleanUp();

	// Update Scene Manager and Process Touch, as well as Input Manager
	bool Update(float frame_time);
	void Render();

private:
	void InitFont();
	void CleanUpFont();
	void SetupLights();

	// Updates
	void ProcessTouchInput();

	// Create font
	gef::Font* font_;

	// Create renderers for 2D/3D
	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;

	// Create primitive builder
	PrimitiveBuilder* primitive_builder_;

	// Create the physics world
	b2World* world_;

	// Create input manager
	gef::InputManager* input_manager_;

	// Touch Input Variables
	Int32 active_touch_id_;
	gef::Vector2 touch_position_;
	gef::Vector2 reset;

	// Object Manager
	Manager object_manager;

	// Audio Manager
	gef::AudioManager* audio_manager_;
	float volume = 10.0f;
	bool playing = false;

	// Screen Manager
	Screen_Manager screen_manager;
};

#endif // _SCENE_APP_H
