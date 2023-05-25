#include "Thing.h"

Thing::Thing()
	: sprite()
	, position(0, 0)
	, colliding(false)
	, hitboxOffset(0, 0)
	, hitboxScale(1, 1)
	, alive(true)
{
}

void Thing::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Thing::Update(sf::Time frameTime)
{
}

sf::Vector2f Thing::GetPosition()
{
	return position;
}

void Thing::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	sprite.setPosition(newPosition);
}

void Thing::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

bool Thing::CheckCollision(Thing other)
{
	if (!alive || !other.alive)
	{ 
		return false;
	}
	
	return GetAABB().intersects(other.GetAABB());
}

void Thing::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

sf::Vector2f Thing::GetCollisionDepth(Thing other)
{
	sf::FloatRect thisAABB = GetAABB();
	sf::FloatRect otherAABB = other.GetAABB();

	sf::Vector2f thisCentre = GetCollisionCentre();
	sf::Vector2f otherCentre = other.GetCollisionCentre();

	sf::Vector2f minDistance;
	minDistance.x = thisAABB.width * 0.5f + otherAABB.width * 0.5f;
	minDistance.y = thisAABB.height * 0.5f + otherAABB.height * 0.5f;

	sf::Vector2f actualDistance = otherCentre - thisCentre;

	if (actualDistance.x < 0)
		minDistance.x = -minDistance.x;
	if (actualDistance.y < 0)
		minDistance.y = -minDistance.y;

	return actualDistance - minDistance;
}

void Thing::HandleCollision(Thing& other)
{
	// Do nothing, handle in child class.
}

void Thing::SetAlive(bool newAlive)
{
	alive = newAlive;
}

sf::Vector2f Thing::GetCollisionCentre()
{
	sf::Vector2f centre = position;

	sf::FloatRect bounds = sprite.getGlobalBounds();
	centre.x += bounds.width * 0.5f;
	centre.y += bounds.height * 0.5f;

	centre.x += hitboxOffset.x;
	centre.y += hitboxOffset.y;

	return centre;
}

sf::FloatRect Thing::GetAABB()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width *= hitboxScale.x;
	bounds.height *= hitboxScale.y;

	sf::Vector2f centre = GetCollisionCentre();

	bounds.left = centre.x - bounds.width * 0.5f;
	bounds.top = centre.y - bounds.height * 0.5f;

	return bounds;
}
