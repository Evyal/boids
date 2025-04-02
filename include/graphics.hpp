#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "../include/structs.hpp"
#include "../include/boid.hpp"

namespace ev {

// DRAW BOID

sf::CircleShape getTriangleBoid(const Boid &boid,
                                const sf::Color &color = sf::Color::Black);

// function to create a rectangle from parameters

sf::RectangleShape getRectangle(const RectanglePar &par,
                                const sf::Color &color = sf::Color::Black);

}  // namespace ev

#endif