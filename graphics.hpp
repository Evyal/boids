#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "boid.hpp"
#include "constants.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>

// DRAW BOID

sf::CircleShape getCircleBoid(const Boid &boid, const sf::Color &color = sf::Color::Black);
sf::CircleShape getTriangleBoid(const Boid &boid, const sf::Color &color = sf::Color::Black);

sf::RectangleShape getRectangle(const RectanglePar &parconst, const sf::Color &color = sf::Color::Black);

#endif