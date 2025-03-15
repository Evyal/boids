#include <SFML/System/Vector2.hpp>
#include <cstddef>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../boid.hpp"
#include "../constants.hpp"
#include "doctest.h"
#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING CLASS BOID") {

  SUBCASE("TESTING GETTERS") {
    Boid b1{{0, 0}, {0, 0}};
    Boid b2{{1, 2}, {3, 4}};

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

    Boid b1{{0, 0}, {0, 0}};
    Boid b2{{1, 2}, {3, 4}};

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

    CHECK(distance(pos1, pos2) == 5.f);
    CHECK(distance(pos1, pos3) == 3.f);
    CHECK(distance(pos2, pos3) == 4.f);
    CHECK(distance(pos1, pos4) == doctest::Approx(sqrtf(2.f)));
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING DISTANCE BETWEEN BOIDS") {

    Boid b1{{0, 0}, {0, 0}};
    Boid b2{{0, 0}, {0, 0}};

    CHECK(distance(b1, b2) == 0.f);

    b1.setPosition({0, 0});
    b2.setPosition({3, 4});

    CHECK(distance(b1, b2) == 5.f);
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING SPEED CONTROL") {

    Boid b1{{0, 0}, {0, 0}};
    Boid b2{{1, 2}, {3, 4}};

    b1.setVelocity({400, 0});
    b2.setVelocity({1, 0});

    checkMaximumSpeed(b1);
    checkMinimumSpeed(b2);

    CHECK(b1.getVelocity().x == constants::maxBoidSpeed);
    CHECK(b1.getVelocity().y == 0.f);

    CHECK(b2.getVelocity().x == constants::minBoidSpeed);
    CHECK(b2.getVelocity().y == 0.f);

    b1.setVelocity({300, 400});
    b2.setVelocity({30, 40});

    checkMaximumSpeed(b1);
    checkMinimumSpeed(b2);

    CHECK(b1.getVelocity().x == 300 * constants::maxBoidSpeed / 500);
    CHECK(b1.getVelocity().y == 400 * constants::maxBoidSpeed / 500);
    CHECK(b1.getSpeed() == constants::maxBoidSpeed);

    CHECK(b2.getVelocity().x == 30 * constants::minBoidSpeed / 50);
    CHECK(b2.getVelocity().y == 40 * constants::minBoidSpeed / 50);
    CHECK(b2.getSpeed() == constants::minBoidSpeed);

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

    Boid b1{};
    Boid b2{};
    Boid b3{};
    Boid b4{};

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

    CHECK(b1.getVelocity().x == +100 + constants::speedBoostMirror);
    CHECK(b1.getVelocity().y == +150 + constants::speedBoostMirror);

    CHECK(b2.getVelocity().x == 100.f);
    CHECK(b2.getVelocity().y == 150.f);

    CHECK(b3.getVelocity().x == -100 - constants::speedBoostMirror);
    CHECK(b3.getVelocity().y == 150.f);

    CHECK(b4.getVelocity().x == -100.f);
    CHECK(b4.getVelocity().y == -150 - constants::speedBoostMirror);

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

  for (size_t i{0}; i < 100; i++) {
    Boid b5{createBoid(center, 0)};

    CHECK(b5.getPosition().x <= center.x + constants::randomPositionRange);
    CHECK(b5.getPosition().x >= center.x - constants::randomPositionRange);
    CHECK(b5.getPosition().y <= center.y + constants::randomPositionRange);
    CHECK(b5.getPosition().y >= center.y - constants::randomPositionRange);

    CHECK(b5.getSpeed() >= constants::randomMinimumSpeed);
    CHECK(b5.getSpeed() <= constants::randomMaximumSpeed);
  }

  sf::Vector2f center1{700., 360.};

  for (size_t i{0}; i < 100; i++) {
    Boid b{createBoid(center1, 0)};
    CHECK(b.getPosition().x <= center1.x + constants::randomPositionRange);
    CHECK(b.getPosition().x >= center1.x - constants::randomPositionRange);
    CHECK(b.getPosition().y <= center1.y + constants::randomPositionRange);
    CHECK(b.getPosition().y >= center1.y - constants::randomPositionRange);

    CHECK(b.getSpeed() >= constants::randomMinimumSpeed);
    CHECK(b.getSpeed() <= constants::randomMaximumSpeed);

    CHECK(b.getPosition().x <= 720.f);
    CHECK(b.getPosition().x >= 0.f);
    CHECK(b.getPosition().y <= 720.f);
    CHECK(b.getPosition().y >= 0.f);
  }
}