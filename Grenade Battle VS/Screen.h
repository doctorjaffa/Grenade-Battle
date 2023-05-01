#pragma once
#include <SFML/Graphics.hpp>

// Forward declaration allowed because levelsceen is not used in THIS file and because it is only a pointer
class Game;

class Screen
{

// Public functions/data
public:

	// Constructor with a game pointer
	Screen(Game* newGamePointer);

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

// Protected functions/data
protected:

	Game* gamePointer;

};
