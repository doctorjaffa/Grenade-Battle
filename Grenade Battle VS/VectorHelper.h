#pragma once
#include <SFML/System.hpp>

namespace VectorHelper
{
	// Magnitude functions
	float SquareMagnitude(sf::Vector2f vec);
	float Magnitude(sf::Vector2f vec);

	// Normalise a vector
	sf::Vector2f Normalise(sf::Vector2f vec);

	// Dot products for 3D and 2D
	float Dot(sf::Vector3f a, sf::Vector3f b);
	float Dot(sf::Vector2f a, sf::Vector2f b);

	// Cross product
	sf::Vector3f Cross(sf::Vector3f a, sf::Vector3f b);

	// Reflection equations for 3D and 2D
	sf::Vector3f GetReflection(sf::Vector3f incident, sf::Vector3f normal);
	sf::Vector2f GetReflection(sf::Vector2f incident, sf::Vector2f normal);

	// Get normal (direction of collision line) equations for 3D and 2D 
	sf::Vector3f GetNormal(sf::Vector3f line1, sf::Vector3f line2);
	sf::Vector2f GetNormal(sf::Vector2f line);
};

