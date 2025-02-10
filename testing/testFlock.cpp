#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../flock.hpp"
#include "doctest.h"
#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING CLASS FLOCK") {

  //////////////////////////////////////////////////////////////////////////////////////////
  // GETTERS

  SUBCASE("TESTING GETTERS") {
    sf::Vector2f center{375, 375};
    Boid b1{{0, 0}, {0, 0}};
    Boid b2{{10, 10}, {0, 0}};
    Boid b3{{20, 10}, {0, 0}};
    Boid b4{{10, 20}, {0, 0}};
    Boid b5{{20, 20}, {0, 0}};

    Flock flock{{b1, b2, b3, b4, b5}, sf::Color::Black};

    CHECK(flock.getBoid(0).getPosition().x == 0);
    CHECK(flock.getBoid(0).getPosition().y == 0);
    CHECK(flock.getBoid(1).getPosition().x == 10);
    CHECK(flock.getBoid(1).getPosition().y == 10);
    CHECK(flock.getBoid(2).getPosition().x == 20);
    CHECK(flock.getBoid(2).getPosition().y == 10);
    CHECK(flock.getBoid(3).getPosition().x == 10);
    CHECK(flock.getBoid(3).getPosition().y == 20);
    CHECK(flock.getBoid(4).getPosition().x == 20);
    CHECK(flock.getBoid(4).getPosition().y == 20);
  }

  //////////////////////////////////////////////////////////////////////////////////////////
  //

  SUBCASE("TESTING GETTERS") {}
}