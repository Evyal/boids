#ifndef RANDOM_H
#define RANDOM_H

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace ev {

//////////////////////////////////////////////////////////////////////////////////////////
// Random for generating NUMBERS

size_t randomInt(size_t min, size_t max);
float randomFloat(float min, float max);
float randomAngle();

//////////////////////////////////////////////////////////////////////////////////////////
// Random for generating BOIDS

sf::Vector2f randomBoidPosition(sf::Vector2f center);
sf::Vector2f randomBoidSpeed(float angleCenter);

}  // namespace ev

#endif