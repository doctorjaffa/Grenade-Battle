#pragma once
#include "Thing.h"
#include "PhysicsObject.h"

class LevelScreen;

class Player :
    public PhysicsObject
{

// Public functions/data
public:

    // Constructor which gets the level screen and this player object's index
    Player(LevelScreen* newLevel, int newPlayerIndex);

    void Update(sf::Time frameTime) override;

    void Draw(sf::RenderTarget& target) override;

    // Getters/Setters
    int GetLives();

    // Collision function
    void HandleCollision(Thing& other) override;

    // Take a life off the player 
    void RemoveLife();


// Private functions/data
private:

    // Virtual functions
    // Acceleration function
    void UpdateAcceleration() override;

    // Getters/Setters
    // The position of the pip sprite
    sf::Vector2f GetPipPosition(float pipTime);

    // Update the firing direction
    void UpdateFiringDirection();

    // Vector of pip sprites
    std::vector<sf::Sprite> pips;

    // Pointer to the level screen
    LevelScreen* currentLevel;

    // Firing velocity of the grenade
    //sf::Vector2f firingVelocity;

    // Has the player fired a grenade
    bool hasFired;
    // Cooldown time and duration of the grenade firing 
    sf::Clock grenadeCooldownTime;
    float grenadeCooldownDuration;

    // Firing direction and speed of the grenade
    sf::Vector2f firingDirection;
    float FIRING_SPEED;

    // Player index and lives
    int playerIndex;
    int lives;

};

