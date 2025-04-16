#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <cmath>
#include <random>
#include <type_traits>

#include "../include/constants.hpp"

namespace randomGen {

//////////////////////////////////////////////////////////////////////////////////////////
// Seed
inline std::random_device rd{};

// Global random engine (Mersenne Twister).
inline std::mt19937 engine{rd()};

//////////////////////////////////////////////////////////////////////////////////////////
// Function to generate a random integer within the closed interval [a, b].
inline int randomInt(int a, int b) {
  assert(a <= b && "For randomInt, a must be less than or equal to b.");
  std::uniform_int_distribution<int> dist(a, b);
  return dist(engine);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Overload for other integral types using a template.
template <typename I>
typename std::enable_if<std::is_integral<I>::value, I>::type randomInt(I a,
                                                                       I b) {
  assert(a <= b && "For randomInt, a must be less than or equal to b.");
  std::uniform_int_distribution<I> dist(a, b);
  return dist(engine);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Template function to generate a random real numbers in the range [a,b).
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type randomReal(
    T a, T b) {
  assert(a < b && "For randomReal, a must be less than b.");
  std::uniform_real_distribution<T> dist(a, b);
  return dist(engine);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Function to generate a random boolean value.
inline bool randomBool() {
  std::bernoulli_distribution dist(0.5);
  return dist(engine);
}

//////////////////////////////////////////////////////////////////////////////////////////

}  // namespace randomGen

namespace ev {

//////////////////////////////////////////////////////////////////////////////////////////
// Generates a random angle in range [0,2Pi)

inline float randomAngle() { return randomGen::randomReal(0.f, 2.f * M_PIf); }

inline sf::Vector2f randomVec2f(float min, float max) {
  assert(min < max && "a must be less than b.");
  return {randomGen::randomReal(min, max), randomGen::randomReal(min, max)};
}

//////////////////////////////////////////////////////////////////////////////////////////
// Generates a random position for a boid, all the boids spawn around the same
// center point

inline sf::Vector2f randomBoidPosition(sf::Vector2f center) {
  // Generate randomly until the boid spawns inside the margins
  bool b{true};
  sf::Vector2f position{};
  while (b) {
    position = center;

    float angle{randomAngle()};
    float step{randomGen::randomReal(0.f, constants::randomPositionRange)};

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

inline sf::Vector2f randomBoidSpeed(float angleCenter) {
  std::uniform_real_distribution angle(
      angleCenter - constants::randomAngleRange,
      angleCenter + constants::randomAngleRange);
  std::uniform_real_distribution norm(constants::randomMinimumSpeed,
                                      constants::randomMaximumSpeed);
  float v{randomGen::randomReal(constants::randomMinimumSpeed,
                                constants::randomMaximumSpeed)};
  float a{randomGen::randomReal(angleCenter - constants::randomAngleRange,
                                angleCenter + constants::randomAngleRange)};
  return {cosf(a) * v, sinf(a) * v};
}

//////////////////////////////////////////////////////////////////////////////////////////

}  // namespace ev

#endif