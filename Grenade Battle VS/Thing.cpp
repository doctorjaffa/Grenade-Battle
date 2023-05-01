#include "Thing.h"

Thing::Thing()
	: sprite()
	, position(0, 0)
{
}

void Thing::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Thing::Update(sf::Time frameTime)
{
}

sf::Vector2f Thing::GetPosition()
{
	return position;
}

void Thing::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	sprite.setPosition(newPosition);
}
