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
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Panel.png"));
	sprite.setScale(10.0f, 10.0f);

	winningText.setFont(AssetManager::RequestFont("Assets/Fonts/dogica.ttf"));
	winningText.setCharacterSize(70);
	winningText.setString("Player 1 wins!");
	winningText.setFillColor(sf::Color::Black);

	restartText.setFont(AssetManager::RequestFont("Assets/Fonts/dogica.ttf"));
	restartText.setCharacterSize(30);
	restartText.setString("Press R to restart,\nor ESCAPE to quit.");
	restartText.setFillColor(sf::Color::Black);

	ResetPosition();
}

void EndPanel::Update(sf::Time frameTime)
{
	if (animatingOut)
	{
		float xPos = window->getSize().x * 0.5f - winningText.getGlobalBounds().width * 0.5f;
		float yPos = window->getSize().y;
		float finalYPos = window->getSize().y * 0.5f - sprite.getGlobalBounds().height * 0.5f;

		sf::Vector2f begin(xPos, yPos);
		sf::Vector2f change(0, finalYPos - yPos);
		float duration = 1.0f;
		float time = animationClock.getElapsedTime().asSeconds();

		sf::Vector2f newPosition = Easing::EaseOutQuad(begin, change, duration, time);
		SetPosition(newPosition);

		if (time >= duration)
		{
			SetPosition(begin + change);
			animatingOut = false;
		}

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
	target.draw(sprite);
	target.draw(winningText);
	target.draw(restartText);
}

void EndPanel::SetPosition(sf::Vector2f newPosition)
{
	sprite.setPosition(newPosition);

	// center the title on the x direction
	float titleX = sprite.getGlobalBounds().width * 0.5f - winningText.getGlobalBounds().width * 0.5f;
	winningText.setPosition(sf::Vector2f(newPosition.x + titleX, newPosition.y + 50));

	// center the message in the x and y direction
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

