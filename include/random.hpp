#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <cmath>
#include <random>

#include "constants.hpp"

namespace randomGen {

//////////////////////////////////////////////////////////////////////////////////////////
// Function to generate size_t integral types.
inline std::size_t randomSizeType(std::size_t min, std::size_t max,
                                  std::mt19937& engine) {
  assert(min <= max && "For randomInt, min must be less than or equal to max.");
  std::uniform_int_distribution<std::size_t> dist(min, max);
  return dist(engine);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Function to generate a random real numbers in the range [a,b).
inline float randomFloat(float min, float max, std::mt19937& engine) {
  assert(min < max && "For randomFloat, min must be less than max.");
  std::uniform_real_distribution<float> dist(min, max);
  return dist(engine);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Function to generate a random boolean value.
inline bool randomBool(std::mt19937& engine) {
  std::bernoulli_distribution dist(0.5);
  return dist(engine);
}

//////////////////////////////////////////////////////////////////////////////////////////

}  // namespace randomGen

namespace ev {

//////////////////////////////////////////////////////////////////////////////////////////
// Generates a random angle in range [0,2Pi)

inline float randomAngle(std::mt19937& engine) {
  return randomGen::randomFloat(0.f, 2.f * M_PIf, engine);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Generates a random sf::Vector2f in range [min, max)

inline sf::Vector2f randomVec2f(float min, float max, std::mt19937& engine) {
  assert(min < max && "a must be less than b.");
  return {randomGen::randomFloat(min, max, engine),
          randomGen::randomFloat(min, max, engine)};
}

//////////////////////////////////////////////////////////////////////////////////////////
// Generates a random position for a boid, all the boids spawn around the same
// center point

inline sf::Vector2f randomBoidPosition(sf::Vector2f center,
                                       std::mt19937& engine) {
  // Generate randomly until the boid spawns inside the margins
  bool b{true};
  sf::Vector2f position{};
  while (b) {
    position = center;

    float angle{randomAngle(engine)};
    float step{
        randomGen::randomFloat(0.f, constants::randomPositionRange, engine)};

    position += {step * cosf(angle), step * sinf(angle)};
    if (position.x > constants::randomMinimumX &&
        position.x < constants::randomMaximumX &&
        position.y > constants::randomMinimumY &&
        position.y < constants::randomMaximumY) {
      b = false;
    }
  }

  assert(position.x >= 0.f);
  assert(position.x <= constants::fieldSide);
  assert(position.y >= 0.f);
  assert(position.y <= constants::fieldSide);

  return position;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Boids of the same flock are generated with their direction varying just a
// little between each other

inline sf::Vector2f randomBoidVelocity(float angleCenter, std::mt19937& engine) {
  float v{randomGen::randomFloat(constants::randomMinimumSpeed,
                                 constants::randomMaximumSpeed, engine)};
  float a{randomGen::randomFloat(angleCenter - constants::randomAngleRange,
                                 angleCenter + constants::randomAngleRange,
                                 engine)};
  return {cosf(a) * v, sinf(a) * v};
}

//////////////////////////////////////////////////////////////////////////////////////////

}  // namespace ev

#endif