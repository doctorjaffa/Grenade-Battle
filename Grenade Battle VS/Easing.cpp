#include "Easing.h"

sf::Vector2f Easing::EaseOutQuad(sf::Vector2f begin, sf::Vector2f change, float duration, float time)
{
    //return (change / (duration * duration)) * time * (2 - time) + begin;

    return -((change * time * time) / duration * duration) + (2.0f * ((change * time) / duration)) + begin;
}
