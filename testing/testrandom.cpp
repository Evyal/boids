#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../boid.hpp"
#include "../constants.hpp"
#include "../random.hpp"
#include "doctest.h"
#include <SFML/Graphics.hpp>
#include <cmath>

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING RANDOM NUMBER GENERATION") {
  size_t n{1000};

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING RANDOM INT and RANDOM FLOAT") {

    size_t sumInt{};
    for (size_t i{0}; i < n; i++) {
      size_t a{randomInt(0, 100)};
      CHECK(a >= 0);
      CHECK(a <= 100);
      sumInt += a;
    }

    std::cout << sumInt / n << '\n';

    float sumFloat{};
    for (size_t i{0}; i < n; i++) {
      float a{randomFloat(0, 100)};
      CHECK(a >= 0.f);
      CHECK(a <= 100.f);
      sumFloat += a;
    }

    std::cout << sumFloat / static_cast<float>(n) << '\n';
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING RANDOM BOID GENERATION") {

    sf::Vector2f center{100, 100};
    for (size_t i{0}; i < n; i++) {
      sf::Vector2f pos{randomBoidPosition(center)};
      CHECK(distance(center, pos) <= 50.f);
      CHECK(pos.x >= 0.f);
      CHECK(pos.x <= 720.f);
      CHECK(pos.y >= 0.f);
      CHECK(pos.y <= 720.f);
    }

    float angle{0.5f};
    for (size_t i{0}; i < n; i++) {
      sf::Vector2f vel{randomBoidSpeed(angle)};
      CHECK(distance(vel, {0, 0}) >= constants::minBoidSpeed);
      CHECK(distance(vel, {0, 0}) <= constants::maxBoidSpeed);

      CHECK(atan2(vel.y, vel.x) <= angle + constants::randomAngleRange);
      CHECK(atan2(vel.y, vel.x) >= angle - constants::randomAngleRange);
    }
  }
}
