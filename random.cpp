#include "random.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <random>

namespace limits {
float x_min{340.};
float x_max{380.};
float y_min{340.};
float y_max{380.};
float delta_x{50.};

float v_min{150.};
float v_max{300.};
float delta_v{50.};
float delta_angle{0.002f};
} // namespace limits

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
  std::uniform_real_distribution distX(limits::x_min, limits::x_max);
  std::uniform_real_distribution distY(limits::y_min, limits::y_max);
  return {distX(rng), distY(rng)};
}

sf::Vector2f randomPosition(sf::Vector2f center) {
  std::uniform_real_distribution distX(center.x - limits::delta_x,
                                       center.x + limits::delta_x);
  std::uniform_real_distribution distY(center.y - limits::delta_x,
                                       center.y + limits::delta_x);
  bool a{true};
  float x{};
  float y{};
  while (a) {
    x = distX(rng);
    if (x > 15.f && x < 735.f) {
      a = false;
    }
  }
  a = true;
  while (a) {
    y = distY(rng);
    if (y > 15.f && y < 735.f) {
      a = false;
    }
  }
  return {x, y};
}

// sf::Vector2f randomSpeed() {
//   std::uniform_real_distribution angleCenter(0.f, 2.f * M_PIf);
//   float a{angleCenter(rng)};
//   std::uniform_real_distribution angle(a - limits::delta_angle,
//                                        a + limits::delta_angle);
//   std::uniform_real_distribution norm(limits::v_min, limits::v_max);
//   float v{norm(rng)};
//   return {cosf(angle(rng)) * v, sinf(angle(rng)) * v};
// }

sf::Vector2f randomSpeed(float angleCenter) {
  std::uniform_real_distribution angle(angleCenter - limits::delta_angle,
                                       angleCenter + limits::delta_angle);
  std::uniform_real_distribution norm(limits::v_min, limits::v_max);
  float v{norm(rng)};
  float a{angle(rng)};
  return {cosf(a) * v, sinf(a) * v};
}