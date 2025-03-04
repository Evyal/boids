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

  SUBCASE("TESTING CONSTRUCTORS and GETTERS") {
    // sf::Vector2f center{375, 375};

    Boid b1{{0.f, 0.f}, {0.f, 0.f}};
    Boid b2{{10.f, 10.f}, {0.f, 0.f}};
    Boid b3{{20.f, 10.f}, {0.f, 15.f}};
    Boid b4{{10.f, 20.f}, {10.f, 0.f}};
    Boid b5{{20.f, 20.f}, {0.f, 10.f}};

    Flock flock1{};

    CHECK(flock1.getSize() == 0);
    CHECK(flock1.getFlockColor() == sf::Color::Black);

    Flock flock2{{b1, b2}};

    CHECK(flock2.getSize() == 2);
    CHECK(flock2.getFlockColor() == sf::Color::Black);

    Flock flock3{{b1, b2, b3, b4, b5}, sf::Color::Red};

    CHECK(flock3.getBoid(0).getPosition().x == 0.f);
    CHECK(flock3.getBoid(0).getPosition().y == 0.f);
    CHECK(flock3.getBoid(1).getPosition().x == 10.f);
    CHECK(flock3.getBoid(1).getPosition().y == 10.f);
    CHECK(flock3.getBoid(2).getPosition().x == 20.f);
    CHECK(flock3.getBoid(2).getPosition().y == 10.f);
    CHECK(flock3.getBoid(3).getPosition().x == 10.f);
    CHECK(flock3.getBoid(3).getPosition().y == 20.f);
    CHECK(flock3.getBoid(4).getPosition().x == 20.f);
    CHECK(flock3.getBoid(4).getPosition().y == 20.f);

    CHECK(flock3.getSize() == 5);
    CHECK(flock3.getFlockColor() == sf::Color::Red);

    // CHECK(flock3.getMeanPosition().x == 12.f);
    // CHECK(flock3.getMeanPosition().y == 12.f);
    // CHECK(flock3.getMeanVelocity().x == 2.f);
    // CHECK(flock3.getMeanVelocity().y == 5.f);
    CHECK(flock3.getMeanSpeed() == 7.f);
  }

  //////////////////////////////////////////////////////////////////////////////////////////
  //

  SUBCASE("TESTING GETTERS") {}
}