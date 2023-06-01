// Project includes
#include "LevelScreen.h"
#include "AssetManager.h"
#include "Game.h"

#include <iostream>
#include <fstream>


LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player(this)
	, gameRunning(true)
	, tiles()
	, camera()
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{

		player.Update(frameTime);

		player.SetColliding(false);

		for (int i = 0; i < grenades.size(); ++i)
		{
			grenades[i]->Update(frameTime);
			grenades[i]->SetColliding(false);

			if (grenades[i]->CheckCollision(*tiles[i]))
			{
				grenades[i]->SetColliding(true);
				grenades[i]->HandleCollision(*tiles[i]);
			}

		}

		for (int i = 0; i < tiles.size(); ++i)
		{
			tiles[i]->SetColliding(false);
		}

		for (int i = 0; i < tiles.size(); ++i)
		{
			if (tiles[i]->CheckCollision(player))
			{
				player.SetColliding(true);
				player.SetGrounded(true);
				tiles[i]->SetColliding(true);
				player.HandleCollision(*tiles[i]);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			Restart();
		}
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	// Update the camera based on the render target size and player position.
	camera = target.getDefaultView();
	sf::Vector2f cameraCenter = camera.getCenter();
	cameraCenter.y = player.GetPosition().y;
	camera.setCenter(cameraCenter);

	// Update the render target to use the camera 
	target.setView(camera);

	// Draw "world" objects (ones that should use the camera)
	for (int i = 0; i < tiles.size(); ++i)
	{
		tiles[i]->Draw(target);
	}

	player.Draw(target);

	for (int i = 0; i < grenades.size(); ++i)
	{
		grenades[i]->Draw(target);
	}

	target.setView(target.getDefaultView());
}

bool LevelScreen::LoadLevel()
{
	// Open the level file
	std::ifstream inFile;
	std::string filePath = "Assets/Levels/Level 1.txt";
	inFile.open(filePath);

	// Make sure the file was actually opened 
	if (!inFile)
	{
		// File was not opened
		return false;
	}

	// Clear out our tiles before making new ones
	// Make sure to delete BEFORE clearing!
	for (int i = 0; i < tiles.size(); ++i)
	{
		delete tiles[i];
		tiles[i] = nullptr;
	}
	tiles.clear();

	// Set the starting x and y coordinates used to position our level objects
	float x = 0.0f;
	float y = 0.0f;

	// Define the spacing we will use for our grid
	const float X_SPACE = 45.0f;
	const float Y_SPACE = 45.0f;

	// Read each character one by one from the file...
	char ch;
	// Each time, try to read the next character
	// If successful, execute the body of the loop
	// The "noskipws" means our input from the file will include the white space (spaces and new lines)
	while (inFile >> std::noskipws >> ch)
	{
		// Perform actions based on what character was read in

		if (ch == ' ')
		{
			x += X_SPACE;
		}
		else if (ch == '\n')
		{
			y += Y_SPACE;
			x = 0;
		}
		else if (ch == 'P')
		{
			player.SetPosition(x, y);
			std::cout << player.GetPosition().x;
			std::cout << player.GetPosition().y;
		}
		else if (ch == 'T')
		{
			tiles.push_back(new Tile(sf::Vector2f(x, y)));
		}
		else if (ch == '-')
		{
			// Do nothing - empty space 
		}
		else
		{
			std::cerr << "Unrecognised character in level file: " << ch;
		}

	}

	// Close the file now that we are done with it 
	inFile.close();

	player.SetAlive(true);
	gameRunning = true;

	// Return true if file was successfully loaded
	return true;
}

void LevelScreen::Restart()
{
	LoadLevel();
}

void LevelScreen::FireGrenade(int playerNumber, sf::Vector2f position, sf::Vector2f velocity)
{
	grenades.push_back(new Grenade(playerNumber, position, velocity));

}
