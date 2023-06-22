#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class Thing
{
// Public functions/data
public:

	// Default constructor
	Thing();

	// Virtual classes
	virtual void Draw(sf::RenderTarget& target);
	virtual void Update(sf::Time frameTime);

	virtual void SetPosition(sf::Vector2f newPosition);
	virtual void HandleCollision(Thing& other);

	// Getters/Setters
	// Position functions
	sf::Vector2f GetPosition();
	void SetPosition(float newX, float newY);

	// Collision functions
	void SetColliding(bool newColliding);
	sf::Vector2f GetCollisionDepth(Thing other);

	// Object Alive
	void SetAlive(bool newAlive);

	// Public functions

	// Collision Function
	bool CheckCollision(Thing other);

// Protected functions/data
protected:

	// Sprite object
	sf::Sprite sprite;

	// Hitbox data
	sf::Vector2f hitboxOffset;
	sf::Vector2f hitboxScale;

	// Alive boolean
	bool alive;

// Private functions/data
private:

	// Collision functions
	sf::Vector2f GetCollisionCentre();
	sf::FloatRect GetAABB();

	// Object position
	sf::Vector2f position;

	// Is it colliding
	bool colliding;
};

