#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "boid.hpp"
#include "constants.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>

// DRAW BOID

sf::CircleShape drawCircleBoid(const Boid &boid, sf::Color color);
sf::CircleShape drawTriangleBoid(const Boid &boid, sf::Color color);

sf::RectangleShape drawRectangle(const RectangleParameters &par);

#endif