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
	// Draw the thing on the screen
	target.draw(sprite);

	// Draws colliders around every object if set to true
	bool drawCollider = false;

	if (drawCollider)
	{
		sf::RectangleShape rectangle;
		sf::FloatRect bounds = GetAABB();
		rectangle.setPosition(bounds.left, bounds.top);
		rectangle.setSize(sf::Vector2f(bounds.width, bounds.height));
		sf::Color collisionColor = sf::Color::Green;
		// turn this red if a collision is occurring
		if (colliding)
			collisionColor = sf::Color::Red;
		collisionColor.a = 100;
		rectangle.setFillColor(collisionColor);

		target.draw(rectangle);
	}
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

void Thing::HandleCollision(Thing& other)
{
}

void Thing::SetAlive(bool newAlive)
{
	alive = newAlive;
}

	/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
	/* ------------------------------------------------------------------------------ Practical Task - Collision Geometry -----------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

bool Thing::CheckCollision(Thing other)
{
	// If the thing collided with is NOT alive, do nothing
	if (!alive || !other.alive)
	{
		return false;
	}

	// Otherwise, find out if it is colliding with another object
	return GetAABB().intersects(other.GetAABB());
}

void Thing::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

sf::Vector2f Thing::GetCollisionDepth(Thing other)
{
	// The bounding boxes on the colliding object, and the object collided with
	sf::FloatRect thisAABB = GetAABB();
	sf::FloatRect otherAABB = other.GetAABB();

	// Get the centres of each object
	sf::Vector2f thisCentre = GetCollisionCentre();
	sf::Vector2f otherCentre = other.GetCollisionCentre();

	// Work out what the minimum distance between these could be to collide
	sf::Vector2f minDistance;
	minDistance.x = thisAABB.width * 0.5f + otherAABB.width * 0.5f;
	minDistance.y = thisAABB.height * 0.5f + otherAABB.height * 0.5f;

	// Figure out the actual distance between them
	sf::Vector2f actualDistance = otherCentre - thisCentre;

	// If they are colliding on the X axis
	if (actualDistance.x < 0)
		// Invert the minimum distance (it is inside the object) 
		minDistance.x = -minDistance.x;
	// If they are colliding on the Y axis
	if (actualDistance.y < 0)
		// Invert the minimum distance (it is inside the object) 
		minDistance.y = -minDistance.y;

	return actualDistance - minDistance;
}

sf::Vector2f Thing::GetCollisionCentre()
{
	// Set the centre to the position of this object
	sf::Vector2f centre = position;

	// Find the bounds of this object
	sf::FloatRect bounds = sprite.getGlobalBounds();

	// Set each point of the centre to equal the actual centre of the object
	centre.x += bounds.width * 0.5f;
	centre.y += bounds.height * 0.5f;

	// Add any hitbox offset to match up properly 
	centre.x += hitboxOffset.x;
	centre.y += hitboxOffset.y;

	return centre;
}

sf::FloatRect Thing::GetAABB()
{
	// Get the bounds of the object and add the hitbox scaling to match up
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width *= hitboxScale.x;
	bounds.height *= hitboxScale.y;

	// Figure out the centre of the object
	sf::Vector2f centre = GetCollisionCentre();

	// Set the bounds 
	bounds.left = centre.x - bounds.width * 0.5f;
	bounds.top = centre.y - bounds.height * 0.5f;

	return bounds;
}
