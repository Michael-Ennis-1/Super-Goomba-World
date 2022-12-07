#include "enemy_object.h"

void enemy_object::init(int posX, int posY, b2World* worldptr)
{
	// Stores original coords
	original.x = posX;
	original.y = posY;

	// Assign ENEMY type
	object_type_ = GAME_OBJECT_TYPE::ENEMY;

	// Enemy User Data
	b2BodyUserData user_data;
	user_data.pointer = (uintptr_t)this;

	// Assign variables to the object's body, including what type of body it is, it's position and it's user_data (which is the object type)
	b2BodyDef body_def;
	body_def.type = b2_kinematicBody;
	body_def.position = b2Vec2(posX, posY);
	body_def.userData = user_data;

	// Create the enemy in the world, according to the data defined in body_def
	enemy_body_ = worldptr->CreateBody(&body_def);

	// Create a shape for the fixture to use as a collision box
	b2PolygonShape enemy_shape;
	enemy_shape.SetAsBox(0.8f, 0.75f);

	// Assign a fixture to the enemy for other objects to collide with
	b2FixtureDef fixture_def;
	fixture_def.shape = &enemy_shape;
	fixture_def.density = 1.0f;

	// Create the fixture
	enemy_body_->CreateFixture(&fixture_def);

	// Initialize the physics simulation
	UpdateFromSimulation(enemy_body_);
}

void enemy_object::initRange(float targetX, float targetY, int s, bool Axis)
{
	// Stores target information, sets targeting boolean to true, stores speed and which axis it will be moving along
	target.x = targetX; 
	target.y = targetY; 
	targeting = true;
	speed = s;
	Axis_ = Axis;

	// Initializes the axis as positive or negative, based on it's original coordinates and it's target coordinates
	if (target.x > original.x)
	{
		AxisX = 1;
	}
	else if (target.x < original.x)
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

void enemy_object::update()
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

void enemy_object::horizontalUpdate()
{
	// If moving right and target's x is less than or equal to enemy's x position
	if (AxisX == 1 && target.x <= enemy_body_->GetPosition().x)
	{
		// Swaps coordinates with the target, for patrolling
		temp.x = target.x;
		target.x = original.x;
		original.x = temp.x;

		// Swaps whether the enemy is moving positively along the axis, or negatively
		AxisX = (AxisX) * (-1);
	}
	// If moving left and target's x is more than or equal to enemy's x position
	if (AxisX == -1 && target.x >= enemy_body_->GetPosition().x)
	{
		temp.x = target.x;
		target.x = original.x;
		original.x = temp.x;

		AxisX = (AxisX) * (-1);
	}
	else
	{
		// Sets velocity of the enemy
		enemy_body_->SetLinearVelocity(b2Vec2((AxisX * speed), enemy_body_->GetLinearVelocity().y));
	}
}

void enemy_object::verticalUpdate()
{
	// If moving up and target's y is less than or equal to enemy's y position
	if (AxisY == 1 && target.y <= enemy_body_->GetPosition().y)
	{
		// Swaps coordinates with the target, for patrolling
		temp.y = target.y;
		target.y = original.y;
		original.y = temp.y;

		// Swaps whether the enemy is moving positively along the axis, or negatively
		AxisY = (AxisY) * (-1);
	}
	// If moving down and target's y is more than or equal to enemy's y position
	if (AxisY == -1 && target.y >= enemy_body_->GetPosition().y)
	{
		temp.y = target.y;
		target.y = original.y;
		original.y = temp.y;

		AxisY = (AxisY) * (-1);
	}
	else
	{
		// Sets velocity of the enemy
		enemy_body_->SetLinearVelocity(b2Vec2(enemy_body_->GetLinearVelocity().x, (AxisY * speed)));
	}
}

void enemy_object::kill()
{
	// Set dead boolean to true, and targeting to false, so that the render function won't render it anymore and it's update wont be calculate
	dead = true;
	targeting = false;

	// Sets position to very far off screen, so no longer needing to worry about it
	enemy_body_->SetTransform(b2Vec2(-100, -100), 0);
}

bool enemy_object::amIDead()
{
	// Returns dead boolean
	return dead;
}