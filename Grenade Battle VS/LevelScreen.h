#pragma once
#include "Screen.h"
#include "Player.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Game;
class Platform;

class LevelScreen :
    public Screen
{

public:
    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;


private:

    bool LoadLevel();
    void Restart();

    Player player;
    bool gameRunning;

    std::vector<Tile*> tiles;

    sf::View camera;

};