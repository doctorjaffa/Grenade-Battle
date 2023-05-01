#include "Player.h"

Player::Player()
	: Thing()
	, position(100, 300)
	, velocity()
	, acceleration()
{
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/player_1.png"));
		sprite.setPosition(position);
	}
}

void Player::Update(sf::Time frameTime)
{
    const float DRAG_MULT = 10.0f;

    SetPosition(GetPosition() + velocity * frameTime.asSeconds());
    velocity = velocity + acceleration * frameTime.asSeconds();

    // drag
    velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

    // Update acceleration
    UpdateAcceleration();

}

void Player::UpdateAcceleration()
{
    const float ACCEL = 1000;

    // Update acceleration
    acceleration.x = 0;
    acceleration.y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        acceleration.x = -ACCEL;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        acceleration.x = ACCEL;
    }
}

