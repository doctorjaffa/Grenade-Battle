#pragma once
#include "Thing.h"
class EndPanel :
	public Thing
{

// Public functions/data
public:

	// Constructor which gets a new window
	EndPanel(sf::RenderWindow* newWindow);

	// Update and draw functions
	void Update(sf::Time frameTime);
	void Draw(sf::RenderTarget& target);

	// Getters/Setters
	// Set each player's win state
	void SetPlayer1Win(bool newHasWon);
	void SetPlayer2Win(bool newHasWon);

	// Set the position of this panel
	void SetPosition(sf::Vector2f newPosition) override;

	// Beginning animation of panel
	void StartAnimation();
	// Reset its position
	void ResetPosition();

// Private functions/data
private:

	// Text objects for the panel
	sf::Text winningText;
	sf::Text restartText;

	// Render window (game window)
	sf::RenderWindow* window;

	// Is it using ease-out
	bool animatingOut;
	// The animation clock
	sf::Clock animationClock;

	// Booleans for which player wins
	bool player1Won;
	bool player2Won;
};

