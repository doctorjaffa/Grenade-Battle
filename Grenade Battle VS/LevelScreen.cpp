// Project includes
#include "LevelScreen.h"
#include "AssetManager.h"
#include "Game.h"


LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, gameRunning(true)
{
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{

		player.Update(frameTime);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	player.Draw(target);
}