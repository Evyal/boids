#ifndef RANDOM_H
#define RANDOM_H

#include <SFML/System/Vector2.hpp>
#include <cmath>

//////////////////////////////////////////////////////////////////////////////////////////
// Random for generating NUMBERS

size_t randomInt(size_t min, size_t max);
float randomFloat(float min, float max);

//////////////////////////////////////////////////////////////////////////////////////////
// Random for generating BOIDS

sf::Vector2f randomPosition();
sf::Vector2f randomPosition(sf::Vector2f center);
sf::Vector2f randomSpeed();
sf::Vector2f randomSpeed(float angleCenter);

#endif