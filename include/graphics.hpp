#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>

#include "boid.hpp"
#include "structs.hpp"

// DRAW BOID

sf::CircleShape getTriangleBoid(const Boid &boid,
                                const sf::Color &color = sf::Color::Black);

// function to create a rectangle from parameters

sf::RectangleShape getRectangle(const RectanglePar &parconst,
                                const sf::Color &color = sf::Color::Black);

#endif