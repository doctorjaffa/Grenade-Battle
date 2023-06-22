#include "Grenade.h"
#include "VectorHelper.h"
#include <SFML/Graphics.hpp>

Grenade::Grenade(int newPlayerNumber, sf::Vector2f newPosition, sf::Vector2f newVelocity)
	: PhysicsObject()
	, playerNumber(newPlayerNumber)
{
	// Get the texture from the textures map
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/grenade.png"));
	// Set the scale of this grenade
	sprite.setScale(sf::Vector2f(2.5f, 2.5f));

	// Set the hitbox data
	hitboxOffset = sf::Vector2f(0, 0);
	hitboxScale = sf::Vector2f(0.5f, 0.5f);
	
	// Update its position to the position handed in constructor, as well as its velocity
	SetPosition(newPosition);
	velocity = newVelocity;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------- PRACTICAL TASK - REFLECTION ------------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

void Grenade::HandleCollision(Thing& other)
{
	// Get the collision depth with the object collided with
	sf::Vector2f depth = GetCollisionDepth(other);
	// Create a new position based on current position
	sf::Vector2f newPos = GetPosition();

	if (abs(depth.x) < abs(depth.y))
	{
		// Move in X direction
		newPos.x += depth.x;

		/*
		sf::Vector2f topLeft = (sf::Rect<float>::left, sf::Rect<float>::top);
		sf::Vector2f bottomLeft = (sf::Rect<float>::left, sf::Rect<float>::top + sf::Rect<float>::height);

		sf::Vector2f collisionLineX = (bottomLeft - topLeft);

		sf::Vector2f newVelocity = VectorHelper::GetReflection(velocity, VectorHelper::GetNormal(collisionLineX));
		velocity.x = newVelocity.x;
		acceleration.x = 0;
		*/
		
	}
	else
	{
		// Move in y direction
		newPos.y += depth.y;

		/*
		sf::Vector2f topLeft = (sf::Rect<float>::left, sf::Rect<float>::top);
		sf::Vector2f topRight = (sf::Rect<float>::left + sf::Rect<float>::width, sf::Rect<float>::top);

		sf::Vector2f collisionLineY = (topRight - topLeft);

		sf::Vector2f newVelocity = VectorHelper::GetReflection(velocity, VectorHelper::GetNormal(collisionLineY));
		velocity.y = newVelocity.y;
		acceleration.y = 0;
		*/
	}

	// Update the position to this new position
	SetPosition(newPos);
}




