#pragma once
#include "Screen.h"
#include "Player.h"
#include "Tile.h"
#include "Grenade.h"
#include <SFML/Graphics.hpp>

class Game;

class LevelScreen :
    public Screen
{

public:
    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void FireGrenade(int playerNumber, sf::Vector2f position, sf::Vector2f velocity);


private:

    bool LoadLevel();
    void Restart();

    Player player1;
    Player player2;
    bool gameRunning;

    std::vector<Tile*> tiles;
    std::vector<Grenade*> grenades;

    sf::View camera;

};