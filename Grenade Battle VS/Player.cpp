#include "Player.h"
#include "LevelScreen.h"

/*
enum class PhysicsType {
    SYMPLECTIC_EULER,
    VELOCITY_VERLET
};
*/

Player::Player(LevelScreen* newLevel)
	: PhysicsObject()
	, pips()
	, currentLevel(newLevel)
	, firingDirection(false)
	, grenadeCooldownTime()
	, grenadeCooldownDuration(3)
	, hasFired(false)
{
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/player_1.png"));
        sprite.setScale(sf::Vector2f(2.5f, 2.5f));

		hitboxOffset = sf::Vector2f(0, 0);
		hitboxScale = sf::Vector2f(0.9f, 0.9f);

		// Add sprites to pips
		const int NUM_PIPS = 10;
		for (int i = 0; i < NUM_PIPS; ++i)
		{
			pips.push_back(sf::Sprite());
			pips[i].setTexture(AssetManager::RequestTexture("Assets/Graphics/pip.png"));
		}
	}
}

void Player::Update(sf::Time frameTime)
{
	PhysicsObject::Update(frameTime);

	float pipTime = 0;
	float pipTimeStep = 0.1f;
	for (int i = 0; i < pips.size(); ++i)
	{
		pips[i].setPosition(GetPipPosition(pipTime));
		pipTime += pipTimeStep;
	}

	if (hasFired)
	{
		if (grenadeCooldownTime.getElapsedTime().asSeconds() >= grenadeCooldownDuration)
		{
			hasFired = false;
			grenadeCooldownTime.restart();
		}
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
	}

	SetPosition(newPos);
}

void Player::UpdateAcceleration()
{
    const float ACCEL = 1000;
	const float GRAVITY = 1000;

    // Update acceleration
    acceleration.x = 0;
    acceleration.y = GRAVITY;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
		firingDirection = true;
        acceleration.x = -ACCEL;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
		firingDirection = false;
        acceleration.x = ACCEL;
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded)
	{
		acceleration.y = -ACCEL * 200;
		grounded = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !hasFired)
	{
		// If player is facing left
		if (firingDirection)
		{
			firingVelocity.x =  -ACCEL;
		}
		else 
		{
			firingVelocity.x =  ACCEL;
		}
		firingVelocity.y = acceleration.y;

		currentLevel->FireGrenade(0, GetPosition(), firingVelocity);

		hasFired = true;
	}

	if (sf::Joystick::isConnected(0))
	{
		float axisX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

		float deadzone = 15;

		if (abs(axisX) > deadzone)
			acceleration.x = axisX * ACCEL / 100.0f;

		if (sf::Joystick::isButtonPressed(0, 0) && grounded)
		{
			acceleration.y = -ACCEL * 200;
			grounded = false;
		}
	}
}



sf::Vector2f Player::GetPipPosition(float pipTime)
{
	const float GRAVITY = 1000;
	const float VELOCITY_X = 500;
	const float VELOCITY_Y = -500;

	sf::Vector2f pipPosition;

	pipPosition = sf::Vector2f(0, GRAVITY) * pipTime * pipTime + sf::Vector2f(VELOCITY_X, VELOCITY_Y) * pipTime + this->GetPosition();

	return pipPosition;
}

