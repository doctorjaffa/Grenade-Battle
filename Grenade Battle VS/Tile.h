#pragma once
#include "Thing.h"
class Tile :
    public Thing
{

// Public functions/data
public:
    
    // Class constructor which takes in a new position
    Tile(sf::Vector2f newPosition);
};

