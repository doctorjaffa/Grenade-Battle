#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class Thing
{
public:

	Thing();

	virtual void Draw(sf::RenderTarget& target);
	virtual void Update(sf::Time frameTime);

	sf::Vector2f GetPosition();
	virtual void SetPosition(sf::Vector2f newPosition);
	void SetPosition(float newX, float newY);

	bool CheckCollision(Thing other);
	void SetColliding(bool newColliding);

	sf::Vector2f GetCollisionDepth(Thing other);
	virtual void HandleCollision(Thing& other);

	void SetAlive(bool newAlive);

protected:

	sf::Sprite sprite;

	sf::Vector2f hitboxOffset;
	sf::Vector2f hitboxScale;

	bool alive;

private:

	sf::Vector2f GetCollisionCentre();
	sf::FloatRect GetAABB();

	sf::Vector2f position;
	bool colliding;
};

