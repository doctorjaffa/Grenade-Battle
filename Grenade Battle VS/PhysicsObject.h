#pragma once
#include "Thing.h"

class PhysicsObject :
    public Thing
{
// Public functions/data
public:

    // Default constructor
    PhysicsObject();

    // Update function
    void Update(sf::Time frameTime) override;

    // Getters/Setters
    void SetGrounded(bool newGrounded);

// Protected variables
protected:

    // Virtual function
    virtual void UpdateAcceleration();

    // Physics movement variables
    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    // Grounded and drag application booleans
    bool grounded;
    bool shouldDrag;

    // Constants 
    const float GRAVITY;
};

