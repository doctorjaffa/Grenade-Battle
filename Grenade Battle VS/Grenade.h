#pragma once
#include "PhysicsObject.h"
class Grenade :
    public PhysicsObject
{
public:
    
    Grenade(int newPlayerNumber, sf::Vector2f newPosition, sf::Vector2f newVelocity);

    //void Update(sf::Time frameTime) override;

    //sf::Vector2f GetPosition(float grenadeTime);

protected:

    int playerNumber;

};

