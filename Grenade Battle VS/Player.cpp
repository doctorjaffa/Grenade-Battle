#include "Player.h"

enum class PhysicsType {
    SYMPLECTIC_EULER,
    VELOCITY_VERLET
};

Player::Player()
	: Thing()
	, twoFramesOldPos(100, 300)
	, velocity()
	, acceleration()
	, pips()
{
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/player_1.png"));
        sprite.setScale(sf::Vector2f(2.0f, 2.0f));

		// Add sprites to pips
		const int NUM_PIPS = 15;
		for (int i = 0; i < NUM_PIPS; ++i)
		{
			pips.push_back(sf::Sprite());
			pips[i].setTexture(AssetManager::RequestTexture("Assets/Graphics/pip.png"));
		}
	}
}

void Player::Update(sf::Time frameTime)
{
	Thing::Update(frameTime);

	/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
	/* ------------------------------------------------------------------------------ Practical Task - Physics Alternatives ----------------------------------------------------------------------------------*/
	/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

	// Set a drag multiplier for smooth movement, and set the physics type being used in. 
    const float DRAG_MULT = 10.0f;
    const PhysicsType physics = PhysicsType::SYMPLECTIC_EULER;

	switch (physics)
	{
		case PhysicsType::SYMPLECTIC_EULER:
		{
			// SEMI-IMPLICIT / SYMPLECTIC_EULER

			// Get the previous frames' velocity 
			velocity = velocity + acceleration * frameTime.asSeconds();

			// Apply drag 
			velocity = velocity - velocity * DRAG_MULT * frameTime.asSeconds();

			// Set new position based on velocity
			SetPosition(GetPosition() + velocity * frameTime.asSeconds());

			// Update acceleration
			UpdateAcceleration();
		}
		break;

		case PhysicsType::VELOCITY_VERLET:
		{
			// VELOCITY VERLET / LEAP FROG

			// Get half frame velocity using
			// previous frame's acceleration
			sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

			// Get new frame's position using half frame velocity
			SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());

			// Update our current acceleration
			UpdateAcceleration();

			// Get new frame's velocity using half frame velocity and
			// updated acceleration
			velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

			// drag
			velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
		}
		break;

		default:
			break;
	}

	float pipTime = 0;
	float pipTimeStep = 0.1f;
	for (int i = 0; i < pips.size(); ++i)
	{
		pips[i].setPosition(GetPipPosition(pipTime));
		pipTime += pipTimeStep;
	}
}

void Player::Draw(sf::RenderTarget& target)
{
	Thing::Draw(target);

	// Draw the pips
	for (int i = 0; i < pips.size(); ++i)
	{
		target.draw(pips[i]);
	}
}

void Player::HandleCollision(Thing& other)
{
	const float JUMPSPEED = 400;
	sf::Vector2f depth = GetCollisionDepth(other);
	sf::Vector2f newPos = GetPosition();

	if (abs(depth.x) < abs(depth.y))
	{
		// Move in X direction
		newPos.x += depth.x;
		velocity.x = 0;
		acceleration.x = 0;
	}
	else
	{
		// Move in y direction
		newPos.y += depth.y;
		velocity.y = 0;
		acceleration.y = 0;

		// If we collided from above
		if (depth.y < 0)
		{
			velocity.y = -JUMPSPEED;
		}
	}

	SetPosition(newPos);
}

void Player::UpdateAcceleration()
{
    const float ACCEL = 1000;

    // Update acceleration
    acceleration.x = 0;
    acceleration.y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        acceleration.x = -ACCEL;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        acceleration.x = ACCEL;
    }
}

sf::Vector2f Player::GetPipPosition(float pipTime)
{
	const float GRAVITY = 1000;
	const float VELOCITY_X = 500;
	const float VELOCITY_Y = -500;

	sf::Vector2f pipPosition;

	//pipPosition = sf::Vector2f(0, 1000) * pipTime * pipTime + sf::Vector2f(500, -1000) * pipTime + sf::Vector2f(500, 500);

	pipPosition = sf::Vector2f(0, 1000) * pipTime * pipTime + sf::Vector2f(500, -500) * pipTime + sf::Vector2f(300, 300);

	//pipPosition = sf::Vector2f(0, GRAVITY) * pipTime * pipTime + sf::Vector2f(VELOCITY_X, VELOCITY_Y) + this->GetPosition();

	return pipPosition;
}

