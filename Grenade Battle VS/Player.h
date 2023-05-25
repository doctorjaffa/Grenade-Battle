#pragma once
#include "Thing.h"
#include "PhysicsObject.h"

class LevelScreen;

class Player :
    public PhysicsObject
{
public:

    Player(LevelScreen* newLevel);

    void Update(sf::Time frameTime) override;

    void Draw(sf::RenderTarget& target) override;

    void HandleCollision(Thing& other) override;


private:

    void UpdateAcceleration() override;

    sf::Vector2f GetPipPosition(float pipTime);

    std::vector<sf::Sprite> pips;

    LevelScreen* currentLevel;

    sf::Vector2f firingVelocity;

};

