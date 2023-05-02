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
{
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/player_1.png"));
        sprite.setScale(sf::Vector2f(2.0f, 2.0f));
	}
}

void Player::Update(sf::Time frameTime)
{

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

