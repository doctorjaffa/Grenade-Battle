#include "EndPanel.h"
#include "Easing.h"

EndPanel::EndPanel(sf::RenderWindow* newWindow)
	: Thing()
	, winningText()
	, restartText()
	, window(newWindow)
	, animatingOut(true)
	, animationClock()
	, player1Won(false)
{
	// Get the panel texture from the textures map
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Panel.png"));
	// Set its scale to 10x the default size
	sprite.setScale(10.0f, 10.0f);

	// Set the winning text data ("Player X wins") 
	winningText.setFont(AssetManager::RequestFont("Assets/Fonts/dogica.ttf"));
	winningText.setCharacterSize(70);
	winningText.setString("Player 1 wins!");
	winningText.setFillColor(sf::Color::Black);

	// Set the restart game text data (Restart/Quit)
	restartText.setFont(AssetManager::RequestFont("Assets/Fonts/dogica.ttf"));
	restartText.setCharacterSize(30);
	restartText.setString("Press Y to restart,\n\nor B to quit.");
	restartText.setFillColor(sf::Color::Black);

	// Reset the position of this panel
	ResetPosition();
}

void EndPanel::Update(sf::Time frameTime)
{
	if (animatingOut)
	{
		// Get the starting position of the panel
		float xPos = window->getSize().x * 0.5f - winningText.getGlobalBounds().width * 0.5f;
		float yPos = window->getSize().y;
		// Get the final position of the panel
		float finalYPos = window->getSize().y * 0.5f - sprite.getGlobalBounds().height * 0.5f;

		// Create the start and finish positions
		sf::Vector2f begin(xPos, yPos);
		sf::Vector2f change(0, finalYPos - yPos);

		// Set the duration of this animation
		float duration = 1.0f;
		float time = animationClock.getElapsedTime().asSeconds();

		// Get a new position based on the equation of its current position, the finish, the length of this animation and the time
		sf::Vector2f newPosition = Easing::EaseOutQuad(begin, change, duration, time);
		// Set the current position to the updated position
		SetPosition(newPosition);

		// If enough time has passed
		if (time >= duration)
		{
			// Update the position to finish
			SetPosition(begin + change);
			animatingOut = false;
		}

		// State which player won, accordingly
		if (player1Won)
		{
			winningText.setString("Player 1 Wins!");
		}
		else if (player2Won)
		{
			winningText.setString("Player 2 Wins!");
		}
	}
}

void EndPanel::Draw(sf::RenderTarget& target)
{
	// Draw the panel and text objects on the screen
	target.draw(sprite);
	target.draw(winningText);
	target.draw(restartText);
}

void EndPanel::SetPosition(sf::Vector2f newPosition)
{
	// Set the panel position to the new position
	sprite.setPosition(newPosition);

	// Center the title on the x direction
	float titleX = sprite.getGlobalBounds().width * 0.5f - winningText.getGlobalBounds().width * 0.5f;
	winningText.setPosition(sf::Vector2f(newPosition.x + titleX, newPosition.y + 50));

	// Center the message in the x and y direction
	float messageX = sprite.getGlobalBounds().width * 0.5f - restartText.getGlobalBounds().width * 0.5f;
	float messageY = sprite.getGlobalBounds().height * 0.5f - restartText.getGlobalBounds().height * 0.5f;
	restartText.setPosition(sf::Vector2f(newPosition.x + messageX, newPosition.y + messageY));
}

void EndPanel::SetPlayer1Win(bool newHasWon)
{
	if (newHasWon == true)
	{
		player1Won = true;
	}
}

void EndPanel::SetPlayer2Win(bool newHasWon)
{
	if (newHasWon == true)
	{
		player2Won = true;
	}
}

void EndPanel::StartAnimation()
{
	animatingOut = true;
	animationClock.restart();
}

void EndPanel::ResetPosition()
{
	float xPos = window->getSize().x * 0.5f - sprite.getGlobalBounds().width * 0.5f;
	float yPos = window->getSize().y;
	SetPosition(sf::Vector2f(xPos, yPos));
}

