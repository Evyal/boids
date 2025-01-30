#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "flock.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>

// DRAW BOID

sf::CircleShape boidCircle(const Flock &flock, size_t i);
sf::CircleShape boidTriangle(const Flock &flock, size_t i);

#endif