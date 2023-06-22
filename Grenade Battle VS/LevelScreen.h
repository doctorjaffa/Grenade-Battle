#pragma once
#include "Screen.h"
#include "Player.h"
#include "Tile.h"
#include "Grenade.h"
#include "EndPanel.h"
#include "PlayerLivesUI.h"
#include <SFML/Graphics.hpp>

class Game;

class LevelScreen :
    public Screen
{

// Public functions/data
public:
    
    // Constructor which gets a pointer to the game
    LevelScreen(Game* newGamePointer);

    // Update and draw functions
    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    // Fire the grenade based on the position and velocity 
    void FireGrenade(int playerNumber, sf::Vector2f position, sf::Vector2f velocity);

    // Set off the win state
    void TriggerEndState(bool _win);

// Private functions/data
private:

    // Load and restart the level
    bool LoadLevel();
    void Restart();

    void ResetPositions();

    // The two players
    Player player1;
    Player player2;

    // The end-game panel UI and player lives UI
    EndPanel endPanel;
    PlayerLivesUI livesUI;

    // Is the game running
    bool gameRunning;

    // Vector of tile pointers 
    std::vector<Tile*> tiles;
    // Vector of grenade pointers
    std::vector<Grenade*> grenades;

    // The camera
    sf::View camera;

};