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
	// Reset the level
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	// If the game is running
	if (gameRunning)
	{
		// Update the lives UI and each player
		livesUI.Update(frameTime);
		player1.Update(frameTime);
		player2.Update(frameTime);

		// Set the colliding of the players
		player1.SetColliding(false);
		player2.SetColliding(false);

		// For each grenade in the grenades vector
		for (int i = 0; i < grenades.size(); ++i)
		{
			// Update the grenade
			grenades[i]->Update(frameTime);
			// Set its collding
			grenades[i]->SetColliding(false);

			// Check if the grenade is colliding with any tiles in the tile vector
			for (int j = 0; j < tiles.size(); ++j)
			{
				// If it is colliding with a tile
				if (grenades[i]->CheckCollision(*tiles[j]))
				{
					// Handle this collision
					grenades[i]->SetColliding(true);
					grenades[i]->HandleCollision(*tiles[j]);
				}
			}

			
			// If the grenade is colliding with player 1
			if (grenades[i]->CheckCollision(player1))
			{
				player1.SetColliding(true);
				grenades[i]->SetColliding(true);

				// Take away a life from the player 1
				player1.RemoveLife();

				// If the player 1 is out of lives
				if (player1.GetLives() == 0)
				{
					// Roll the end panel
					endPanel.SetPlayer1Win(true);
				}
				//Restart();
			}

			// If the grenade is colliding with player 2
			if (grenades[i]->CheckCollision(player2))
			{
				player2.SetColliding(true);
				grenades[i]->SetColliding(true);

				// Take away a life from the player 2
				player2.RemoveLife();

				// If the player 2 is out of lives
				if (player2.GetLives() == 0)
				{
					// Roll the end panel
					endPanel.SetPlayer2Win(true);
				}
				//Restart();
			} 

			// If the grenade exceeds its lifetime, delete it
			if (grenades[i]->grenadeTimer.getElapsedTime().asSeconds() >= grenades[i]->grenadeLifetime)
			{
				delete grenades[i];
				grenades[i] = nullptr;
			}

		}

		for (int i = 0; i < tiles.size(); ++i)
		{
			tiles[i]->SetColliding(false);
		}

		// For each tile in the tiles vector
		for (int i = 0; i < tiles.size(); ++i)
		{
			// If the tile is colliding with player 1
			if (tiles[i]->CheckCollision(player1))
			{
				// The player is grounded and handle this collision
				player1.SetColliding(true);
				player1.SetGrounded(true);
				tiles[i]->SetColliding(true);
				player1.HandleCollision(*tiles[i]);
			}
			// If the tile is colliding with player 2
			if (tiles[i]->CheckCollision(player2))
			{
				// The player is grounded and handle this collision
				player2.SetColliding(true);
				player2.SetGrounded(true);
				tiles[i]->SetColliding(true);
				player2.HandleCollision(*tiles[i]);
			}
		}
	}
	// If the game is over
	else
	{
		// Start rolling the end panel update
		endPanel.Update(frameTime);

	}

	// If player presses R, restart the level
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

	// Draw the players
	player1.Draw(target);
	player2.Draw(target);

	// Draw all of the grenades
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
	// The game is over
	gameRunning = false;
	// Start the end panel animation
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
	// Delete all of the grenades in the grenades vector
	for (int i = 0; i < grenades.size(); ++i)
	{
		delete grenades[i];
		grenades[i] = nullptr;
	}
	grenades.clear();

	// Reload the level
	LoadLevel();
}

// Create a new grenade based on the current player position and velocity
void LevelScreen::FireGrenade(int playerNumber, sf::Vector2f position, sf::Vector2f velocity)
{
	grenades.push_back(new Grenade(playerNumber, position, velocity));

}
