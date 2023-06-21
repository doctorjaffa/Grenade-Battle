#include "Player.h"
#include "LevelScreen.h"
#include "VectorHelper.h"

Player::Player(LevelScreen* newLevel, int newPlayerIndex)
	: PhysicsObject()
	, playerIndex(newPlayerIndex)
	, pips()
	, currentLevel(newLevel)
	, grenadeCooldownTime()
	, grenadeCooldownDuration(3)
	, hasFired(false)
	, firingDirection()
	, FIRING_SPEED(750)
{
	{
		std::string playerTexture = "Assets/Graphics/player_" + std::to_string(playerIndex + 1) + ".png";
		sprite.setTexture(AssetManager::RequestTexture(playerTexture));
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

	UpdateFiringDirection();

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
		//firingDirection = true;
        acceleration.x = -ACCEL;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
		//firingDirection = false;
        acceleration.x = ACCEL;
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded)
	{
		acceleration.y = -ACCEL * 200;
		grounded = false;
	}

	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !hasFired)
	{
		firingVelocity.y = acceleration.y;
		

		currentLevel->FireGrenade(0, GetPosition(), firingVelocity);

		hasFired = true;
	}

	if (sf::Joystick::isConnected(playerIndex))
	{
		float axisX = sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::X);

		const float DEADZONE = 15;

		if (abs(axisX) > DEADZONE)
			acceleration.x = axisX * ACCEL / 100.0f;

		if (sf::Joystick::isButtonPressed(playerIndex, 0) && grounded)
		{
			acceleration.y = -ACCEL * 200;
			grounded = false;
		}

		float axisZ = sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::Z);
		if (abs(axisZ) > DEADZONE && !hasFired)
		{
			firingVelocity.y = acceleration.y;


			currentLevel->FireGrenade(playerIndex, GetPosition(), firingVelocity);

			hasFired = true;
		}
	}
}

/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------- PRACTICAL TASK - GRAVITY PREDICTION ------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

sf::Vector2f Player::GetPipPosition(float pipTime)
{
	const float GRAVITY = 1000;
	const float VELOCITY_X = 500;
	const float VELOCITY_Y = -500;

	sf::Vector2f pipPosition;

	pipPosition = sf::Vector2f(0, GRAVITY) * pipTime * pipTime + firingDirection * FIRING_SPEED * pipTime + this->GetPosition();

	return pipPosition;
}

void Player::UpdateFiringDirection()
{
	const float DEADZONE = 15;

	if (sf::Joystick::isConnected(0))
	{
		float axisX = sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::U);
		if (abs(axisX) > DEADZONE)
		{
			firingDirection.x = axisX;
		}
		float axisY = sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::V);
		if (abs(axisY) > DEADZONE)
		{
			firingDirection.y = axisY;
		}

		firingDirection = VectorHelper::Normalise(firingDirection);
	}
}

