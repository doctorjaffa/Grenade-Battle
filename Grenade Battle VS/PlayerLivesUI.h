#pragma once
#include <SFML/Graphics.hpp>

class Player;

class PlayerLivesUI
{

// Public functions/data
public:

    // Class constructor which takes in two player pointers
    PlayerLivesUI(Player* player1, Player* player2);

    void Update(sf::Time frameTime);
    void Draw(sf::RenderTarget& target);

// Private functions/data
private:

    // The game camera
    sf::View camera;

    // The two player lives counters (placeholder - empty texts)
    sf::Text player1LivesText;
    sf::Text player2LivesText;

    // The game font
    sf::Font gameFont;

    // The two pointers to the players to be set in constructor
    Player* player1;
    Player* player2;
};

