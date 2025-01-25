#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SFML/Graphics.hpp"
#include "flock.hpp"
#include <cmath>
#include <vector>

// DRAW INTERFACE
void drawGrid(sf::RenderWindow &window);
void drawScreen(sf::RenderWindow &window);
void drawInterface(sf::RenderWindow &window);
void drawRectangles(sf::RenderWindow &window,
                    const std::vector<Flock> &flockstack);

// DRAW FLOCK
sf::CircleShape boidBody(const Flock &flock, size_t i);
sf::CircleShape boidTriangle(const Flock &flock, size_t i);

void updateBodyStack(sf::RenderWindow &window,
                     const std::vector<Flock> &flockStack,
                     std::vector<std::vector<sf::CircleShape>> &bodyStack);

// PRINT FLOCK
// void printFlock(sf::RenderWindow &window, const Flock& flock,
//                 float center);

#endif