// Project includes
#include "LevelScreen.h"
#include "AssetManager.h"
#include "Game.h"

#include <iostream>
#include <fstream>


LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player1(this, 0)
	, player2(this, 1)
	, gameRunning(true)
	, tiles()
	, camera()
	, endPanel(newGamePointer->GetWindow())
	, livesUI(&player1, &player2)
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		livesUI.Update(frameTime);
		player1.Update(frameTime);
		player2.Update(frameTime);

		player1.SetColliding(false);
		player2.SetColliding(false);

		for (int i = 0; i < grenades.size(); ++i)
		{
			grenades[i]->Update(frameTime);
			grenades[i]->SetColliding(false);

			for (int j = 0; j < tiles.size(); ++j)
			{
				if (grenades[i]->CheckCollision(*tiles[j]))
				{
					grenades[i]->SetColliding(true);
					grenades[i]->HandleCollision(*tiles[j]);
				}
			}

			if (grenades[i]->CheckCollision(player1))
			{
				player1.SetColliding(true);
				grenades[i]->SetColliding(true);

				player1.RemoveLife();

				if (player1.GetLives() == 0)
				{
					endPanel.SetPlayer1Win(true);
				}
			}

			if (grenades[i]->CheckCollision(player2))
			{
				player2.SetColliding(true);
				grenades[i]->SetColliding(true);

				player2.RemoveLife();

				if (player2.GetLives() == 0)
				{
					endPanel.SetPlayer2Win(true);
				}

			}

		}

		for (int i = 0; i < tiles.size(); ++i)
		{
			tiles[i]->SetColliding(false);
		}

		for (int i = 0; i < tiles.size(); ++i)
		{
			if (tiles[i]->CheckCollision(player1))
			{
				player1.SetColliding(true);
				player1.SetGrounded(true);
				tiles[i]->SetColliding(true);
				player1.HandleCollision(*tiles[i]);
			}
			if (tiles[i]->CheckCollision(player2))
			{
				player2.SetColliding(true);
				player2.SetGrounded(true);
				tiles[i]->SetColliding(true);
				player2.HandleCollision(*tiles[i]);
			}
		}
	}
	else
	{
		endPanel.Update(frameTime);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		Restart();
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	// Update the camera based on the render target size and player position.
	camera = target.getDefaultView();
	sf::Vector2f cameraCenter = camera.getCenter();
	cameraCenter.y = player1.GetPosition().y;
	camera.setCenter(cameraCenter);

	// Update the render target to use the camera 
	target.setView(camera);

	// Draw "world" objects (ones that should use the camera)
	for (int i = 0; i < tiles.size(); ++i)
	{
		tiles[i]->Draw(target);
	}

	player1.Draw(target);
	player2.Draw(target);

	for (int i = 0; i < grenades.size(); ++i)
	{
		grenades[i]->Draw(target);
	}

	target.setView(target.getDefaultView());

	// Draw UI objects (use the base view)
	if (!gameRunning)
	{
		endPanel.Draw(target);
	}
}

void LevelScreen::TriggerEndState(bool _win)
{
	// TODO
	gameRunning = false;
	endPanel.StartAnimation();
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
			player1.SetPosition(x, y);
			std::cout << player1.GetPosition().x;
			std::cout << player1.GetPosition().y;
		}
		else if (ch == 'O')
		{
			player2.SetPosition(x, y);
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

	player1.SetAlive(true);
	player2.SetAlive(true);
	gameRunning = true;

	// Return true if file was successfully loaded
	return true;
}

void LevelScreen::Restart()
{
	for (int i = 0; i < grenades.size(); ++i)
	{
		delete grenades[i];
		grenades[i] = nullptr;
	}
	grenades.clear();

	LoadLevel();
}

void LevelScreen::FireGrenade(int playerNumber, sf::Vector2f position, sf::Vector2f velocity)
{
	grenades.push_back(new Grenade(playerNumber, position, velocity));

}
