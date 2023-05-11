#include "Tile.h"

Tile::Tile(sf::Vector2f newPosition)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/tile.png"));
	hitboxOffset = sf::Vector2f(0, -57.0f);
	hitboxScale = sf::Vector2f(1.0f, 0.25f);
	SetPosition(newPosition);
}
