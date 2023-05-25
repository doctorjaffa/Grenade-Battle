#pragma once
#include "Thing.h"

class PhysicsObject :
    public Thing
{
    
public:

    PhysicsObject();

    void Update(sf::Time frameTime) override;

    void SetGrounded(bool newGrounded);

protected:

    virtual void UpdateAcceleration();

    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    bool grounded;
};

