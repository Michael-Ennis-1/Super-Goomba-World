#include "moving_floor.h"

void Moving_Floor::init(float sX, float sY, float sZ, PrimitiveBuilder* pb, int posX, int posY, b2World* worldptr)
{
	// Stores original coords
	original.x = posX;
	original.y = posY;

	// Dimensions
	ground_half_dimensions = gef::Vector4(sX, sY, sZ);

	// Setup the mesh for the Moving Floor based on it's half dimensions, and assign PLATFORM type
	ground_mesh_ = pb->CreateBoxMesh(ground_half_dimensions);
	set_mesh(ground_mesh_);
	object_type_ = GAME_OBJECT_TYPE::PLATFORM;

	// Setup Moving Floor user data
	ground_data.pointer = (uintptr_t)this;

	// Assign variables to the object's body, including what type of body it is, it's position and it's user_data (which is the object type)
	body_def.type = b2_kinematicBody;
	body_def.position = b2Vec2(posX, posY);
	body_def.userData = ground_data;

	// Create the Moving Platform in the world, according to the data defined in body_def
	ground_body_ = worldptr->CreateBody(&body_def);

	// Create a shape for the fixture to use as a collision box, based on dimensions of the object
	shape.SetAsBox(ground_half_dimensions.x(), ground_half_dimensions.y());

	// Assign a fixture to the Moving Floor for other objects to collide with
	fixture_def.shape = &shape;
	fixture_def.density = 1.0f;

	// Create the fixture
	ground_body_->CreateFixture(&fixture_def);

	// Initialize the physics simulation
	UpdateFromSimulation(ground_body_);
}

void Moving_Floor::initRange(float targetX, float targetY, int s, bool Axis)
{
	// Stores target information, stores speed and which axis it will be moving along
	target.x = targetX;
	target.y = targetY;
	speed = s;
	Axis_ = Axis;

	// Initializes the axis as positive or negative, based on it's original coordinates and it's target coordinates
	if (target.x > original.x)
	{
		AxisX = 1;
	}
	if (target.x < original.x)
	{
		AxisX = -1;
	}

	if (target.y > original.y)
	{
		AxisY = 1;
	}
	if (target.y < original.y)
	{
		AxisY = -1;
	}
}

void Moving_Floor::update()
{
	// Chooses which update to use, based on the axis the enemy will be moving along
	if (Axis_ == true)
	{
		horizontalUpdate();
	}
	else
	{
		verticalUpdate();
	}
}

void Moving_Floor::horizontalUpdate()
{
	// If moving right and target's x is less than or equal to enemy's x position
	if (AxisX == 1 && target.x <= ground_body_->GetPosition().x)
	{
		// Swaps coordinates with the target, for patrolling
		temp.x = target.x;
		target.x = original.x;
		original.x = temp.x;

		// Swaps whether the enemy is moving positively along the axis, or negatively
		AxisX = (AxisX) * (-1);
	}   // If moving left and target's x is more than or equal to enemy's x position
	if (AxisX == -1 && target.x >= ground_body_->GetPosition().x)
	{
		temp.x = target.x;
		target.x = original.x;
		original.x = temp.x;

		AxisX = (AxisX) * (-1);
	}
	else
	{
		// Sets velocity of the Moving Floor
		ground_body_->SetLinearVelocity(b2Vec2((AxisX * speed), ground_body_->GetLinearVelocity().y));
	}
}

void Moving_Floor::verticalUpdate()
{
	// If moving up and target's y is less than or equal to enemy's y position
	if (AxisY == 1 && target.y <= ground_body_->GetPosition().y)
	{
		// Swaps coordinates with the target, for patrolling
		temp.y = target.y;
		target.y = original.y;
		original.y = temp.y;

		AxisY = (AxisY) * (-1);
	}   // If moving down and target's y is more than or equal to enemy's y position
	if (AxisY == -1 && target.y >= ground_body_->GetPosition().y)
	{
		temp.y = target.y;
		target.y = original.y;
		original.y = temp.y;

		AxisY = (AxisY) * (-1);
	}
	else
	{
		// Sets velocity of the Moving Floor
		ground_body_->SetLinearVelocity(b2Vec2(ground_body_->GetLinearVelocity().x, (AxisY * speed)));
	}
}