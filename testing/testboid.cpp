#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <SFML/Graphics.hpp>

#include "../assets/doctest.h"
#include "../include/boid.hpp"
#include "../include/constants.hpp"

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING CLASS BOID") {
  SUBCASE("TESTING GETTERS") {
    ev::Boid b1{{0, 0}, {0, 0}};
    ev::Boid b2{{1, 2}, {3, 4}};

    CHECK(b1.getPosition().x == 0.f);
    CHECK(b1.getPosition().y == 0.f);

    CHECK(b2.getPosition().x == 1.f);
    CHECK(b2.getPosition().y == 2.f);

    CHECK(b1.getVelocity().x == 0.f);
    CHECK(b1.getVelocity().y == 0.f);

    CHECK(b1.getVelocity().x == 0.f);
    CHECK(b1.getVelocity().y == 0.f);
    CHECK(b1.getSpeed() == 0.f);

    CHECK(b2.getVelocity().x == 3.f);
    CHECK(b2.getVelocity().y == 4.f);
    CHECK(b2.getSpeed() == 5.f);
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING SETTERS") {
    ev::Boid b1{{0, 0}, {0, 0}};
    ev::Boid b2{{1, 2}, {3, 4}};

    b1.setPosition({3, 3});
    b2.setPosition({3, 3});

    CHECK(b1.getPosition().x == 3.f);
    CHECK(b1.getPosition().y == 3.f);

    CHECK(b2.getPosition().x == 3.f);
    CHECK(b2.getPosition().y == 3.f);

    b1.setVelocity({3, 4});
    b2.setVelocity({0, 0});

    CHECK(b1.getVelocity().x == 3.f);
    CHECK(b1.getVelocity().y == 4.f);
    CHECK(b1.getSpeed() == 5.f);

    CHECK(b2.getVelocity().x == 0.f);
    CHECK(b2.getVelocity().y == 0.f);
    CHECK(b2.getSpeed() == 0.f);

    b1 += {2., 8};
    b2 += {3., 4};

    CHECK(b1.getVelocity().x == 5.f);
    CHECK(b1.getVelocity().y == 12.f);
    CHECK(b1.getSpeed() == 13.f);

    CHECK(b2.getVelocity().x == 3.f);
    CHECK(b2.getVelocity().y == 4.f);
    CHECK(b2.getSpeed() == 5.f);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING FUNCTIONS") {
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

    b1.setPosition({0, 0});
    b2.setPosition({3, 4});

    CHECK(distance(b1, b2) == 5.f);
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING TOROIDAL DISTANCE BETWEEN BOIDS") {
    ev::Boid b1{{360, 100}};
    ev::Boid b2{{360, 700}};

    CHECK(ev::toroidalDistance(b1.getPosition(), b2.getPosition()) ==
          doctest::Approx(120.f));

    ev::Boid b3{{20, 20}};
    ev::Boid b4{{-20, -10}};
    ev::Boid b5{{0, 0}};
    CHECK(ev::toroidalDistance(b3.getPosition(), b4.getPosition()) ==
          doctest::Approx(50.f));
    CHECK(ev::toroidalDistance(b3.getPosition(), b5.getPosition()) ==
          doctest::Approx(sqrtf(800.f)));
    CHECK(ev::toroidalDistance(b4.getPosition(), b5.getPosition()) ==
          doctest::Approx(sqrtf(500.f)));
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING SPEED CONTROL") {
    ev::Boid b1{{0, 0}, {0, 0}};
    ev::Boid b2{{1, 2}, {3, 4}};

    b1.setVelocity({400, 0});
    b2.setVelocity({1, 0});

    checkMaximumSpeed(b1);
    checkMinimumSpeed(b2);

    CHECK(b1.getVelocity().x == ev::constants::maxBoidSpeed);
    CHECK(b1.getVelocity().y == 0.f);

    CHECK(b2.getVelocity().x == ev::constants::minBoidSpeed);
    CHECK(b2.getVelocity().y == 0.f);

    b1.setVelocity({300, 400});
    b2.setVelocity({30, 40});

    checkMaximumSpeed(b1);
    checkMinimumSpeed(b2);

    CHECK(b1.getVelocity().x == 300 * ev::constants::maxBoidSpeed / 500);
    CHECK(b1.getVelocity().y == 400 * ev::constants::maxBoidSpeed / 500);
    CHECK(b1.getSpeed() == ev::constants::maxBoidSpeed);

    CHECK(b2.getVelocity().x == 30 * ev::constants::minBoidSpeed / 50);
    CHECK(b2.getVelocity().y == 40 * ev::constants::minBoidSpeed / 50);
    CHECK(b2.getSpeed() == ev::constants::minBoidSpeed);

    // Nel caso in cui la velocità di un boid sia esattamente {0,0}, la
    // funzione checkMinimumSpeed non modificherà la sua velocità. Altrimenti
    // si sarebbe dovuta assegnare una direzione in modo casuale.

    b2.setVelocity({0, 0});

    checkMinimumSpeed(b2);

    CHECK(b2.getVelocity().x == 0.f);
    CHECK(b2.getVelocity().y == 0.f);
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING CHECK BORDERS") {
    ev::Boid b1{};
    ev::Boid b2{};
    ev::Boid b3{};
    ev::Boid b4{};

    // TOROIDAL

    b1.setPosition({-10, -10});
    b2.setPosition({375, 375});
    b3.setPosition({750, 375});
    b4.setPosition({375, 750});

    toroidalBorders(b1);
    toroidalBorders(b2);
    toroidalBorders(b3);
    toroidalBorders(b4);

    CHECK(b1.getPosition().x == 710.f);
    CHECK(b1.getPosition().y == 710.f);

    CHECK(b2.getPosition().x == 375.f);
    CHECK(b2.getPosition().y == 375.f);

    CHECK(b3.getPosition().x == 30.f);
    CHECK(b3.getPosition().y == 375.f);

    CHECK(b4.getPosition().x == 375.f);
    CHECK(b4.getPosition().y == 30.f);

    // MIRROR

    b1.setPosition({-15, -15});
    b2.setPosition({375, 375});
    b3.setPosition({750, 375});
    b4.setPosition({375, 750});

    b1.setVelocity({100, 150});
    b2.setVelocity({100, 150});
    b3.setVelocity({100, 150});
    b4.setVelocity({-100, -150});

    mirrorBorders(b1);
    mirrorBorders(b2);
    mirrorBorders(b3);
    mirrorBorders(b4);

    // ATTENZIONE: La velocità non si inverte sempre, il boid semplicemente
    // ottiene una componente diretta verso l'interno tutte le volte che
    // supera i margini

    CHECK(b1.getVelocity().x == +100 + ev::constants::speedBoostMirror);
    CHECK(b1.getVelocity().y == +150 + ev::constants::speedBoostMirror);

    CHECK(b2.getVelocity().x == 100.f);
    CHECK(b2.getVelocity().y == 150.f);

    CHECK(b3.getVelocity().x == -100 - ev::constants::speedBoostMirror);
    CHECK(b3.getVelocity().y == 150.f);

    CHECK(b4.getVelocity().x == -100.f);
    CHECK(b4.getVelocity().y == -150 - ev::constants::speedBoostMirror);

    CHECK(b1.getPosition().x == 0.f);
    CHECK(b1.getPosition().y == 0.f);

    CHECK(b2.getPosition().x == 375.f);
    CHECK(b2.getPosition().y == 375.f);

    CHECK(b3.getPosition().x == 720.f);
    CHECK(b3.getPosition().y == 375.f);

    CHECK(b4.getPosition().x == 375.f);
    CHECK(b4.getPosition().y == 720.f);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING BUILD BOID") {
  sf::Vector2f center{400., 200.};
  float rand{ev::constants::randomPositionRange};

  for (size_t i{0}; i < 100; i++) {
    ev::Boid b5{ev::createBoid(center, 0)};

    CHECK(b5.getPosition().x <= center.x + rand);
    CHECK(b5.getPosition().x >= center.x - rand);
    CHECK(b5.getPosition().y <= center.y + rand);
    CHECK(b5.getPosition().y >= center.y - rand);

    CHECK(b5.getSpeed() >= ev::constants::randomMinimumSpeed);
    CHECK(b5.getSpeed() <= ev::constants::randomMaximumSpeed);
  }

  sf::Vector2f center1{700., 360.};

  for (size_t i{0}; i < 100; i++) {
    ev::Boid b{ev::createBoid(center1, 0)};
    CHECK(b.getPosition().x <= center1.x + rand);
    CHECK(b.getPosition().x >= center1.x - rand);
    CHECK(b.getPosition().y <= center1.y + rand);
    CHECK(b.getPosition().y >= center1.y - rand);

    CHECK(b.getSpeed() >= ev::constants::randomMinimumSpeed);
    CHECK(b.getSpeed() <= ev::constants::randomMaximumSpeed);

    CHECK(b.getPosition().x <= 720.f);
    CHECK(b.getPosition().x >= 0.f);
    CHECK(b.getPosition().y <= 720.f);
    CHECK(b.getPosition().y >= 0.f);
  }
}