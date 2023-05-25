#pragma once
#include "Thing.h"
class Player :
    public Thing
{
public:

    Player();

    void Update(sf::Time frameTime) override;

    void Draw(sf::RenderTarget& target) override;

    void HandleCollision(Thing& other) override;

    void SetGrounded(bool newGrounded);

private:

    void UpdateAcceleration();

    sf::Vector2f GetPipPosition(float pipTime);

    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    std::vector<sf::Sprite> pips;

    bool grounded;
};

