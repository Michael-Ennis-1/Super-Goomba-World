#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	font_(NULL),
	world_(NULL),
	audio_manager_(NULL),
	active_touch_id_(-1),
	reset(0, 0)
{
}

void SceneApp::Init()
{
	// Create sprite renderer
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// Create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// Initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);

	// Initialise input manager
	input_manager_ = gef::InputManager::Create(platform_);

	// Create Audio Manager
	audio_manager_ = gef::AudioManager::Create();

	// Initialize volume
	audio_manager_->SetMasterVolume(10.0f);

	// Initialise font/lighting
	InitFont();
	SetupLights();

	// initialise the physics world
	b2Vec2 gravity(0.0f, (-9.81f * 3));
	world_ = new b2World(gravity);

	// Initialize Screen Manager
	screen_manager.Init(platform_, sprite_renderer_, primitive_builder_, world_, audio_manager_);

	// Initialize Touch Manager
	if (input_manager_ && input_manager_->touch_manager() && (input_manager_->touch_manager()->max_num_panels() > 0))
		input_manager_->touch_manager()->EnablePanel(0);
}

void SceneApp::CleanUp()
{
	// destroying the physics world also destroys all the objects within it
	delete world_;
	world_ = NULL;

	CleanUpFont();

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete audio_manager_;
	audio_manager_ = NULL;
}

void SceneApp::ProcessTouchInput()
{
	const gef::TouchInputManager* touch_input = input_manager_->touch_manager();
	if (touch_input && (touch_input->max_num_panels() > 0))
	{
		// get the active touches for this panel
		const gef::TouchContainer& panel_touches = touch_input->touches(0);

		// go through the touches
		for (gef::ConstTouchIterator touch = panel_touches.begin(); touch != panel_touches.end(); ++touch)
		{
			// if active touch id is -1, then we are not currently processing a touch
			if (active_touch_id_ == -1)
			{
				// check for the start of a new touch
				if (touch->type == gef::TT_NEW)
				{
					active_touch_id_ = touch->id;

					// Record position of Touch
					touch_position_ = touch->position;

					// Reset touch_position_ to (0, 0)
					touch_position_ = reset;
				}
			}
			else if (active_touch_id_ == touch->id)
			{
				// Processing touch data with a matching id 
				if (touch->type == gef::TT_ACTIVE)
				{
					// Update an active touch here
					touch_position_ = touch->position;
				}
				else if (touch->type == gef::TT_RELEASED)
				{
					// Touch has been Released
					active_touch_id_ = -1;
				}
			}
		}
	}
}

bool SceneApp::Update(float frame_time)
{
	// Process touches on screen
	ProcessTouchInput();

	// Update Input
	input_manager_->Update();

	// Update Scene Manager
	screen_manager.Update(touch_position_, world_, input_manager_, audio_manager_, platform_, frame_time);
	
	// Reset Touch Position
	touch_position_ = reset;

	return true;
}

void SceneApp::Render()
{
	// Renders everything
	screen_manager.Render(sprite_renderer_, renderer_3d_, platform_, font_);
}

void SceneApp::InitFont()
{
	// Initializes Font
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SceneApp::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}

void SceneApp::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}
