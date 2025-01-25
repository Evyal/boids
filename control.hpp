#ifndef CONTROL_H
#define CONTROL_H

#include "SFML/Graphics.hpp"
#include "flock.hpp"
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <vector>

void addRandomFlock(std::vector<Flock> &flockStack);
void addFlock(std::vector<Flock> &flockStack, size_t nBoids,
              sf::Vector2f center, sf::Color color);

void assignFlock(const Flock &flock, std::vector<sf::CircleShape> &flockBody);
void drawFlock(sf::RenderWindow &window,
               const std::vector<sf::CircleShape> &flockBody);

void updateFlockStack(std::vector<Flock> &flockStack);

#endif