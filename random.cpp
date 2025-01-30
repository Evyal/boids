#include "random.hpp"
#include "constants.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <random>
#include <chrono>

std::default_random_engine rng(static_cast<size_t>(
    std::chrono::steady_clock::now().time_since_epoch().count()));

//////////////////////////////////////////////////////////////////////////////////////////
// Generate a RANDOM INTEGER (SIZE_T) in the RANGE [min, max], inclusive

size_t randomInt(size_t min, size_t max) {

  std::uniform_int_distribution dist(min, max);
  return dist(rng);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Generate a random FLOAT in the range (min, max]

float randomFloat(float min, float max) {
  std::uniform_real_distribution dist(min, max);
  return dist(rng);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Generates a random position for a boid, all the boids spawn around the same
// center point

sf::Vector2f randomPosition(sf::Vector2f center) {
  std::uniform_real_distribution distX(
      center.x - constants::randomPositionRange,
      center.x + constants::randomPositionRange);
  std::uniform_real_distribution distY(
      center.y - constants::randomPositionRange,
      center.y + constants::randomPositionRange);

  // Generate randomly until the boid spawns inside the margins
  bool a{true};
  float x{};
  float y{};
  while (a) {
    x = distX(rng);
    if (x > constants::randomMinimumX && x < constants::randomMaximumX) {
      a = false;
    }
  }
  a = true;
  while (a) {
    y = distY(rng);
    if (y > constants::randomMinimumY && y < constants::randomMaximumY) {
      a = false;
    }
  }
  return {x, y};
}

//////////////////////////////////////////////////////////////////////////////////////////
// Boids of the same flock are generated with their direction varying just a
// little between each other

sf::Vector2f randomSpeed(float angleCenter) {
  std::uniform_real_distribution angle(
      angleCenter - constants::randomAngleRange,
      angleCenter + constants::randomAngleRange);
  std::uniform_real_distribution norm(constants::randomMinimumSpeed,
                                      constants::randomMaximumSpeed);
  float v{norm(rng)};
  float a{angle(rng)};
  return {cosf(a) * v, sinf(a) * v};
}