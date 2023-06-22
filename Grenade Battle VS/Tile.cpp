#include "Tile.h"

Tile::Tile(sf::Vector2f newPosition)
{
	// Get the tile texture from the textures map
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/tile.png"));

	// Set its scale 
	sprite.setScale(2.5f, 2.5f);

	// Add hitbox data
	hitboxOffset = sf::Vector2f(0, 0);
	hitboxScale = sf::Vector2f(1.0f, 1.0f);

	// Set its position to the position handed in its constructor
	SetPosition(newPosition);
}
