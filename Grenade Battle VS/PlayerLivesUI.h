#pragma once
#include <SFML/Graphics.hpp>

class Player;

class PlayerLivesUI
{
public:

    PlayerLivesUI(Player* player1, Player* player2);

    void Update(sf::Time frameTime);
    void Draw(sf::RenderTarget& target);


private:

    sf::View camera;

    sf::Text player1LivesText;
    sf::Text player2LivesText;

    sf::Font gameFont;

    Player* player1;
    Player* player2;
};

