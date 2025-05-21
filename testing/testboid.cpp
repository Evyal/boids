#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <random>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <SFML/Graphics.hpp>

#include "boid.hpp"
#include "constants.hpp"
#include "doctest.h"

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

std::random_device rd{};
std::mt19937 engine{rd()};

TEST_CASE("TESTING BOID FUNCTION") {
  SUBCASE("TESTING DISTANCE BETWEEN SFML 2D VECTORS") {
    sf::Vector2f pos1{0, 0};
    sf::Vector2f pos2{-3, 4};
    sf::Vector2f pos3{-3, 0};
    sf::Vector2f pos4{1, 1};

    CHECK(ev::distance(pos1, pos2) == 5.f);
    CHECK(ev::distance(pos1, pos3) == 3.f);
    CHECK(ev::distance(pos2, pos3) == 4.f);
    CHECK(ev::distance(pos1, pos4) == doctest::Approx(sqrtf(2.f)));
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING DISTANCE BETWEEN BOIDS") {
    ev::Boid b1{{0, 0}, {0, 0}};
    ev::Boid b2{{0, 0}, {0, 0}};

    CHECK(distance(b1, b2) == 0.f);

    b1.position = {0, 0};
    b2.position = {3, 4};

    CHECK(distance(b1, b2) == 5.f);
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING TOROIDAL DISTANCE BETWEEN BOIDS") {
    ev::Boid b1{{360, 100}};
    ev::Boid b2{{360, 700}};

    CHECK(ev::toroidalDistance(b1.position, b2.position) ==
          doctest::Approx(120.f));

    ev::Boid b3{{20, 20}};
    ev::Boid b4{{-20, -10}};
    ev::Boid b5{{0, 0}};
    CHECK(ev::toroidalDistance(b3.position, b4.position) ==
          doctest::Approx(50.f));
    CHECK(ev::toroidalDistance(b3.position, b5.position) ==
          doctest::Approx(sqrtf(800.f)));
    CHECK(ev::toroidalDistance(b4.position, b5.position) ==
          doctest::Approx(sqrtf(500.f)));
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING SPEED CONTROL") {
    ev::Boid b1{{0, 0}, {0, 0}};
    ev::Boid b2{{1, 2}, {3, 4}};

    b1.velocity = {400, 0};
    b2.velocity = {1, 0};

    maximumSpeedControl(b1);
    minimumSpeedControl(b2);

    CHECK(b1.velocity.x == ev::constants::maxBoidSpeed);
    CHECK(b1.velocity.y == 0.f);

    CHECK(b2.velocity.x == ev::constants::minBoidSpeed);
    CHECK(b2.velocity.y == 0.f);

    b1.velocity = {300, 400};
    b2.velocity = {30, 40};

    maximumSpeedControl(b1);
    minimumSpeedControl(b2);

    CHECK(b1.velocity.x ==
          doctest::Approx(300 * ev::constants::maxBoidSpeed / 500));
    CHECK(b1.velocity.y ==
          doctest::Approx(400 * ev::constants::maxBoidSpeed / 500));
    CHECK(getSpeed(b1) == ev::constants::maxBoidSpeed);

    CHECK(b2.velocity.x == 30 * ev::constants::minBoidSpeed / 50);
    CHECK(b2.velocity.y == 40 * ev::constants::minBoidSpeed / 50);
    CHECK(getSpeed(b2) == ev::constants::minBoidSpeed);

    // Nel caso in cui la velocità di un boid sia esattamente {0,0}, la
    // funzione checkMinimumSpeed non modificherà la sua velocità. Altrimenti
    // si sarebbe dovuta assegnare una direzione in modo casuale.

    b2.velocity = {0.f, 0.f};

    std::cout << b2.velocity.x << '\n';
    minimumSpeedControl(b2);

    CHECK(b2.velocity.x == doctest::Approx(0.f));
    CHECK(b2.velocity.y == doctest::Approx(0.f));
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING CHECK BORDERS") {
    ev::Boid b1{};
    ev::Boid b2{};
    ev::Boid b3{};
    ev::Boid b4{};

    // TOROIDAL

    b1.position = {-10, -10};
    b2.position = {375, 375};
    b3.position = {750, 375};
    b4.position = {375, 750};

    toroidalBorders(b1);
    toroidalBorders(b2);
    toroidalBorders(b3);
    toroidalBorders(b4);

    CHECK(b1.position.x == 710.f);
    CHECK(b1.position.y == 710.f);

    CHECK(b2.position.x == 375.f);
    CHECK(b2.position.y == 375.f);

    CHECK(b3.position.x == 30.f);
    CHECK(b3.position.y == 375.f);

    CHECK(b4.position.x == 375.f);
    CHECK(b4.position.y == 30.f);

    // MIRROR

    b1.position = {-15, -15};
    b2.position = {375, 375};
    b3.position = {750, 375};
    b4.position = {375, 750};

    b1.velocity = {100, 150};
    b2.velocity = {100, 150};
    b3.velocity = {100, 150};
    b4.velocity = {-100, -150};

    mirrorBorders(b1);
    mirrorBorders(b2);
    mirrorBorders(b3);
    mirrorBorders(b4);

    // ATTENZIONE: La velocità non si inverte sempre, il boid semplicemente
    // ottiene una componente diretta verso l'interno tutte le volte che
    // supera i margini

    CHECK(b1.velocity.x == +100 + ev::constants::speedBoostMirror);
    CHECK(b1.velocity.y == +150 + ev::constants::speedBoostMirror);

    CHECK(b2.velocity.x == 100.f);
    CHECK(b2.velocity.y == 150.f);

    CHECK(b3.velocity.x == -100 - ev::constants::speedBoostMirror);
    CHECK(b3.velocity.y == 150.f);

    CHECK(b4.velocity.x == -100.f);
    CHECK(b4.velocity.y == -150 - ev::constants::speedBoostMirror);

    CHECK(b1.position.x == 0.f);
    CHECK(b1.position.y == 0.f);

    CHECK(b2.position.x == 375.f);
    CHECK(b2.position.y == 375.f);

    CHECK(b3.position.x == 720.f);
    CHECK(b3.position.y == 375.f);

    CHECK(b4.position.x == 375.f);
    CHECK(b4.position.y == 720.f);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING BUILD BOID") {
  sf::Vector2f center{400., 200.};
  float rand{ev::constants::randomPositionRange};

  for (size_t i{0}; i < 100; i++) {
    ev::Boid b5{ev::randomBoid(engine, center, 0)};

    CHECK(b5.position.x <= center.x + rand);
    CHECK(b5.position.x >= center.x - rand);
    CHECK(b5.position.y <= center.y + rand);
    CHECK(b5.position.y >= center.y - rand);

    CHECK(getSpeed(b5) >= ev::constants::randomMinimumSpeed);
    CHECK(getSpeed(b5) <= ev::constants::randomMaximumSpeed);
  }

  sf::Vector2f center1{700., 360.};

  for (size_t i{0}; i < 100; i++) {
    ev::Boid b{ev::randomBoid(engine, center1, 0)};
    CHECK(b.position.x <= center1.x + rand);
    CHECK(b.position.x >= center1.x - rand);
    CHECK(b.position.y <= center1.y + rand);
    CHECK(b.position.y >= center1.y - rand);

    CHECK(getSpeed(b) >= ev::constants::randomMinimumSpeed);
    CHECK(getSpeed(b) <= ev::constants::randomMaximumSpeed);

    CHECK(b.position.x <= 720.f);
    CHECK(b.position.x >= 0.f);
    CHECK(b.position.y <= 720.f);
    CHECK(b.position.y >= 0.f);
  }
}