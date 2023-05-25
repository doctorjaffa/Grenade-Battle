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




