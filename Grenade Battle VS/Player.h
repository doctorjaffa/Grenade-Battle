#pragma once
#include "Thing.h"
class Player :
    public Thing
{
public:

    Player();

    void Update(sf::Time frameTime) override;

private:

    void UpdateAcceleration();

    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};

