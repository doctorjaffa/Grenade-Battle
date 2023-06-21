#include "PlayerLivesUI.h"
#include "AssetManager.h"
#include "Player.h"

PlayerLivesUI::PlayerLivesUI(Player* player1, Player* player2)
	: player1(player1)
	, player2(player2)
{
	player1LivesText.setFont(AssetManager::RequestFont("Assets/Fonts/dogica.ttf"));
	player1LivesText.setCharacterSize(70);
	player1LivesText.setString("3");
	player1LivesText.setFillColor(sf::Color::White);
	player1LivesText.setPosition(50, 50);

	player2LivesText.setFont(AssetManager::RequestFont("Assets/Fonts/dogica.ttf"));
	player2LivesText.setCharacterSize(70);
	player2LivesText.setString("3");
	player2LivesText.setFillColor(sf::Color::White);
	player2LivesText.setPosition(300, 300);
}

void PlayerLivesUI::Update(sf::Time frameTime)
{
	std::string player1LivesStr = " ";
	player1LivesStr += player1->GetLives();
	player1LivesText.setString(player1LivesStr);

	std::string player2LivesStr = " ";
	player2LivesStr += player2->GetLives();
	player2LivesText.setString(player2LivesStr);
}

void PlayerLivesUI::Draw(sf::RenderTarget& target)
{
	target.draw(player1LivesText);
	target.draw(player2LivesText);
}

