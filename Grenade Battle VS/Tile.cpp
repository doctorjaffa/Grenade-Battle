#include "Tile.h"

Tile::Tile(sf::Vector2f newPosition)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/tile.png"));

	sprite.setScale(2.5f, 2.5f);

	hitboxOffset = sf::Vector2f(0, 0);
	hitboxScale = sf::Vector2f(1.0f, 1.0f);
	SetPosition(newPosition);
}
