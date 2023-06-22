#include "VectorHelper.h"

float VectorHelper::SquareMagnitude(sf::Vector2f vec)
{
    // Square each term in the vector and add them together
    return vec.x * vec.x + vec.y * vec.y;;
}

float VectorHelper::Magnitude(sf::Vector2f vec)
{
    // Square root the square magnitude
    return sqrt(SquareMagnitude(vec));
}

sf::Vector2f VectorHelper::Normalise(sf::Vector2f vec)
{
    // Get the magnitude of this vector
    float mag = Magnitude(vec);

    // Divide the vector by its magnitude
    vec.x = vec.x / mag;
    vec.y = vec.y / mag;


    return vec;
}

float VectorHelper::Dot(sf::Vector3f a, sf::Vector3f b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float VectorHelper::Dot(sf::Vector2f a, sf::Vector2f b)
{
    return a.x* b.x + a.y * b.y;
}

sf::Vector3f VectorHelper::Cross(sf::Vector3f a, sf::Vector3f b)
{
    sf::Vector3f c;
    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;

    return c;
}

sf::Vector3f VectorHelper::GetReflection(sf::Vector3f incident, sf::Vector3f normal)
{
    return incident - 2.0f * normal * Dot(incident, normal);
}

sf::Vector2f VectorHelper::GetReflection(sf::Vector2f incident, sf::Vector2f normal)
{
    return incident - 2.0f * normal * Dot(incident, normal);
}

sf::Vector3f VectorHelper::GetNormal(sf::Vector3f line1, sf::Vector3f line2)
{
    return Cross(line1, line2);
}

sf::Vector2f VectorHelper::GetNormal(sf::Vector2f line)
{
    return sf::Vector2f(line.y, -line.x);
}
