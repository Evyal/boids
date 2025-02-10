#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "boid.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>

// DRAW BOID

sf::CircleShape drawCircleBoid(const Boid &boid, sf::Color color);
sf::CircleShape drawTriangleBoid(const Boid &boid, sf::Color color);

#endif