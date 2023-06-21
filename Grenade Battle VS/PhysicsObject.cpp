#include "PhysicsObject.h"

enum class PhysicsType {
	SYMPLECTIC_EULER,
	VELOCITY_VERLET
};

PhysicsObject::PhysicsObject()
	: Thing()
	, velocity()
	, acceleration()
	, grounded(true)
	, shouldDrag(false)
	, GRAVITY(1000)
{

}

void PhysicsObject::Update(sf::Time frameTime)
{

	Thing::Update(frameTime);

	/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
	/* ------------------------------------------------------------------------------ Practical Task - Physics Alternatives ----------------------------------------------------------------------------------*/
	/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

	// Set a drag multiplier for smooth movement, and set the physics type being used in. 
	const float DRAG_MULT = 5.0f;
	const PhysicsType physics = PhysicsType::SYMPLECTIC_EULER;

	switch (physics)
	{
	case PhysicsType::SYMPLECTIC_EULER:
	{
		// SEMI-IMPLICIT / SYMPLECTIC_EULER

		// Get the previous frames' velocity 
		velocity = velocity + acceleration * frameTime.asSeconds();

		if (shouldDrag)
		{
			// Apply drag 
			velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
		}

		// Set new position based on velocity
		SetPosition(GetPosition() + velocity * frameTime.asSeconds());

		// Update acceleration
		UpdateAcceleration();
	}
	break;

	case PhysicsType::VELOCITY_VERLET:
	{
		// VELOCITY VERLET / LEAP FROG

		// Get half frame velocity using
		// previous frame's acceleration
		sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

		// Get new frame's position using half frame velocity
		SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());

		// Update our current acceleration
		UpdateAcceleration();

		// Get new frame's velocity using half frame velocity and
		// updated acceleration
		velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

		if (shouldDrag)
		{
			// drag
			velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
		}

	}
	break;

	default:
		break;
	}
}

void PhysicsObject::SetGrounded(bool newGrounded)
{
	grounded = newGrounded;
}

void PhysicsObject::UpdateAcceleration()
{
	// Update acceleration
	acceleration.y = GRAVITY;
}

