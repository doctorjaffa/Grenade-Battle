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
	, lives(1)
{
	{
		// Get the player texture from the textures map
		std::string playerTexture = "Assets/Graphics/player_" + std::to_string(playerIndex + 1) + ".png";
		sprite.setTexture(AssetManager::RequestTexture(playerTexture));
		// Update the scale of the player object
        sprite.setScale(sf::Vector2f(2.5f, 2.5f));

		// Change its hitbox data
		hitboxOffset = sf::Vector2f(0, 0);
		hitboxScale = sf::Vector2f(0.9f, 0.9f);

		// Add sprites to pips
		const int NUM_PIPS = 10;
		for (int i = 0; i < NUM_PIPS; ++i)
		{
			pips.push_back(sf::Sprite());
			pips[i].setTexture(AssetManager::RequestTexture("Assets/Graphics/pip.png"));
		}

		// This player should apply drag in the PhysicsObject base class
		shouldDrag = true;

	}
}

void Player::Update(sf::Time frameTime)
{
	// Call the base class update function
	PhysicsObject::Update(frameTime);

	// Update the firing direction
	UpdateFiringDirection();

	// Set the time to start at 0
	float pipTime = 0;
	// Increment of pip time per pip sprite
	float pipTimeStep = 0.1f;
	
	// For each pip in the pips vector
	for (int i = 0; i < pips.size(); ++i)
	{
		// Set its position based on how much time has passed 
		pips[i].setPosition(GetPipPosition(pipTime));
		// Increase the pip time by the pip time increment
		pipTime += pipTimeStep;
	}

	// If a player has already fired
	if (hasFired)
	{
		// Check if enough time has passed to fire again
		if (grenadeCooldownTime.getElapsedTime().asSeconds() >= grenadeCooldownDuration)
		{
			// The player has not fired
			hasFired = false;
			// Restart the cooldown timer
			grenadeCooldownTime.restart();
		}
	}

}

void Player::Draw(sf::RenderTarget& target)
{
	// Call the base class draw function
	Thing::Draw(target);

	// Draw the pips
	for (int i = 0; i < pips.size(); ++i)
	{
		target.draw(pips[i]);
	}
}

void Player::HandleCollision(Thing& other)
{
	// Set a constant jump speed 
	const float JUMPSPEED = 400;
	// Get the collision depth with the object collided with
	sf::Vector2f depth = GetCollisionDepth(other);
	// Get the current position
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

	// Update the position to the new position
	SetPosition(newPos);
}

void Player::UpdateAcceleration()
{
	// Call the base class acceleration update function
	PhysicsObject::UpdateAcceleration();

	// Set the constant acceleration
	const float ACCEL = 1000;

	// Keyboard movements
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
	// End of keyboard movements 

	// If there is a controller connected
	if (sf::Joystick::isConnected(playerIndex))
	{
		// Get the left analogue stick movement 
		float axisX = sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::X);

		// Set a constant deadzone 
		const float DEADZONE = 15;

		// If the analogue stick is pushed further than the deadzone
		if (abs(axisX) > DEADZONE)
			// Update the player's acceleration based on its movement 
			acceleration.x = axisX * ACCEL / 100.0f;

		// If the player presses the A button
		if (sf::Joystick::isButtonPressed(playerIndex, 0) && grounded)
		{
			// Lift the player off the ground
			acceleration.y = -ACCEL * 300;
			// They are no longer grounded
			grounded = false;
		}

		// Get how far the player pushes in one of the triggers
		float axisZ = sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::Z);
		// If it's further than the deadzone, and the player hasn't fired already
		if (abs(axisZ) > DEADZONE && !hasFired)
		{
			// Grenade offset
			sf::Vector2f grenadeOffset(45.0f, -5.0f);
			// Create a new grenade and set its data based on the player 
			currentLevel->FireGrenade(playerIndex, GetPosition() + grenadeOffset, firingDirection * FIRING_SPEED);

			// The player has fired
			hasFired = true;
		}
	}
}

/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------- PRACTICAL TASK - GRAVITY PREDICTION ------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

sf::Vector2f Player::GetPipPosition(float pipTime)
{
	// Empty vector variable
	sf::Vector2f pipPosition;

	// Derivation equation to get this pip's prediction positon 
	pipPosition = sf::Vector2f(0, GRAVITY) * pipTime * pipTime / 2.0f + firingDirection * FIRING_SPEED * pipTime + GetPosition();

	return pipPosition;
}

void Player::UpdateFiringDirection()
{
	// Constant deadzone variable
	const float DEADZONE = 15;

	// If the controller is connected
	if (sf::Joystick::isConnected(playerIndex))
	{
		float axisX = sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::U);
		// If the stick is further than the deadzone
		if (abs(axisX) > DEADZONE)
		{
			// Update the firing direction to match analogue stick movement
			firingDirection.x = axisX;
		}
		float axisY = sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::V);
		// If the stick is further than the deadzone
		if (abs(axisY) > DEADZONE)
		{
			// Update the firing direction to match analogue stick movement
			firingDirection.y = axisY;
		}

		// Normalise the firing direction so we are getting ONLY the direction, not the full arc
		firingDirection = VectorHelper::Normalise(firingDirection);
	}
}

void Player::RemoveLife()
{
	// Remove a life from the player
	lives--;
}

int Player::GetLives()
{
	return lives;
}

void Player::SetLives(int newLives)
{
	lives = newLives;
}

sf::Vector2f Player::GetStartPosition()
{
	return startPosition;
}

void Player::SetStartPosition(sf::Vector2f newStartPos)
{
	startPosition = newStartPos;
}

int Player::GetPlayerIndex()
{
	return playerIndex;
}

