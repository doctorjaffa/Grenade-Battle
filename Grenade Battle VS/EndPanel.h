#pragma once
#include "Thing.h"
class EndPanel :
	public Thing
{
public:

	EndPanel(sf::RenderWindow* newWindow);

	void Update(sf::Time frameTime);
	void Draw(sf::RenderTarget& target);

	void SetPlayer1Win(bool newHasWon);
	void SetPlayer2Win(bool newHasWon);

	void StartAnimation();
	void ResetPosition();

	void SetPosition(sf::Vector2f newPosition) override;

private:

	sf::Text winningText;
	sf::Text restartText;
	sf::RenderWindow* window;

	bool animatingOut;
	sf::Clock animationClock;

	bool player1Won;
	bool player2Won;
};

