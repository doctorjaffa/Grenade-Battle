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

protected:

	sf::Sprite sprite;

	sf::Vector2f hitboxOffset;
	sf::Vector2f hitboxScale;

private:

	sf::Vector2f position;
};

