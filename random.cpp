#include "random.hpp"
#include "constants.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <random>

extern std::default_random_engine rng;

size_t randomInt(size_t min, size_t max) {

  std::uniform_int_distribution dist(min, max);
  return dist(rng);
}

float randomFloat(float min, float max) {
  std::uniform_real_distribution dist(min, max);
  return dist(rng);
}

sf::Vector2f randomPosition() {
  std::uniform_real_distribution distX(constants::randomMinimumX,
                                       constants::randomMinimumX);
  std::uniform_real_distribution distY(constants::randomMinimumY,
                                       constants::randomMaximumY);
  return {distX(rng), distY(rng)};
}

sf::Vector2f randomPosition(sf::Vector2f center) {
  std::uniform_real_distribution distX(
      center.x - constants::randomPositionRange,
      center.x + constants::randomPositionRange);
  std::uniform_real_distribution distY(
      center.y - constants::randomPositionRange,
      center.y + constants::randomPositionRange);
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