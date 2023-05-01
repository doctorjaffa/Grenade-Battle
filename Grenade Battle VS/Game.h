#pragma once
#include <SFML/Graphics.hpp>

// Forward declaration
class Screen;

class Game
{

// Public functions/data
public:

	// Default constructor
	Game();

	void RunGameLoop();

	void EventHandling();
	void Update();
	void Draw();

	sf::RenderWindow* GetWindow();

// Private functions/data
private:

	sf::RenderWindow window;
	sf::Clock gameClock;

	Screen* currentScreen;

};