#ifndef BOID_H
#define BOID_H

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <random>

#include "constants.hpp"

namespace ev {

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// CLASS BOID
struct Boid {
  sf::Vector2f position = constants::defaultBoidPosition;
  sf::Vector2f velocity = constants::defaultBoidVelocity;
};

//////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS

//////////////////////////////////////////////////////////////////////////////////////////
// DISTANCE for BOIDS

float deltaX(const Boid &boid1, const Boid &boid2);
float deltaY(const Boid &boid1, const Boid &boid2);
float distance(const Boid &boid1, const Boid &boid2);

// DISTANCE for sf::Vector2f
float distance(const sf::Vector2f &a, const sf::Vector2f &b);
float toroidalDistance(const sf::Vector2f &a, const sf::Vector2f &b);

//////////////////////////////////////////////////////////////////////////////////////////
// SPEED CONTROL

float getSpeed(const Boid &boid);

void minimumSpeedControl(Boid &boid);
void maximumSpeedControl(Boid &boid);

//////////////////////////////////////////////////////////////////////////////////////////
// CHECK BORDERS

void toroidalBorders(Boid &boid);
void mirrorBorders(Boid &boid);

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE BOIDS

Boid randomBoid(std::mt19937 &engine, sf::Vector2f center = {360, 360},
                float angle = 0.f);

}  // namespace ev
#endif