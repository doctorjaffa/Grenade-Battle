#include "Grenade.h"

Grenade::Grenade(int newPlayerNumber, sf::Vector2f newPosition, sf::Vector2f newVelocity)
	: PhysicsObject()
	, playerNumber(newPlayerNumber)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/grenade.png"));
	sprite.setScale(sf::Vector2f(2.5f, 2.5f));

	hitboxOffset = sf::Vector2f(0, 0);
	hitboxScale = sf::Vector2f(0.5f, 0.5f);
	
	SetPosition(newPosition);
	velocity = newVelocity;
}

void Grenade::HandleCollision(Thing& other)
{
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




