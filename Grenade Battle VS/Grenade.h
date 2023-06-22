#pragma once
#include "PhysicsObject.h"
class Grenade :
    public PhysicsObject
{

// Public functions/data
public:
    
    // Constructor which gets the player index, the position of this grenade and its velocity 
    Grenade(int newPlayerNumber, sf::Vector2f newPosition, sf::Vector2f newVelocity);

    // Collision code for this grenade
    void HandleCollision(Thing& other) override;

    // Grenade lifetime
    float grenadeLifetime;

    // Grenade timer 
    sf::Clock grenadeTimer;

// Protected functions/data
protected:

    // The player index
    int playerNumber;

// Private functions/data
private:

};

