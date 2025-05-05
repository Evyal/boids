#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <SFML/Graphics.hpp>
#include <cmath>

#include "doctest.h"
#include "boid.hpp"
#include "constants.hpp"
#include "flock.hpp"

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING CLASS FLOCK") {
  SUBCASE("TESTING CONSTRUCTORS and GETTERS") {
    // sf::Vector2f center{375, 375};

    ev::Boid b1{{0.f, 0.f}, {0.f, 0.f}};
    ev::Boid b2{{10.f, 10.f}, {0.f, 0.f}};
    ev::Boid b3{{20.f, 10.f}, {0.f, 15.f}};
    ev::Boid b4{{10.f, 20.f}, {10.f, 0.f}};
    ev::Boid b5{{20.f, 20.f}, {0.f, 10.f}};

    // Flocks must have at least 2 elements

    ev::Flock flock2{{b1, b2}};

    CHECK(flock2.getSize() == 2);
    CHECK(flock2.getFlockColor() == sf::Color::Black);

    ev::Flock flock3{{b1, b2, b3, b4, b5}, sf::Color::Red};

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

    ev::Boid b6{{10.f, 50.f}, {200.f, 150.f}};
    ev::Boid b7{{20.f, 40.f}, {100.f, 250.f}};
    ev::Boid b8{{30.f, 60.f}, {50.f, 120.f}};

    ev::Flock flock4{{b6, b7, b8}};

    CHECK(flock4.getFlockPositions().at(0).x == 10.f);
    CHECK(flock4.getFlockPositions().at(0).y == 50.f);
    CHECK(flock4.getFlockPositions().at(1).x == 20.f);
    CHECK(flock4.getFlockPositions().at(1).y == 40.f);
    CHECK(flock4.getFlockPositions().at(2).x == 30.f);
    CHECK(flock4.getFlockPositions().at(2).y == 60.f);

    CHECK(flock4.getFlockVelocities().at(0).x == 200.f);
    CHECK(flock4.getFlockVelocities().at(0).y == 150.f);
    CHECK(flock4.getFlockVelocities().at(1).x == 100.f);
    CHECK(flock4.getFlockVelocities().at(1).y == 250.f);
    CHECK(flock4.getFlockVelocities().at(2).x == 50.f);
    CHECK(flock4.getFlockVelocities().at(2).y == 120.f);

    CHECK(flock4.getFlockSpeeds().at(0) == 250.f);
    CHECK(flock4.getFlockSpeeds().at(2) == 130.f);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING RULES") {
  ev::Boid b1{{10.f, 50.f}, {20.f, 50.f}};
  ev::Boid b2{{15.f, 45.f}, {10.f, 20.f}};
  ev::Boid b3{{20.f, 40.f}, {40.f, 30.f}};
  ev::Boid b4{{25.f, 30.f}, {70.f, 10.f}};
  ev::Boid b5{{30.f, 20.f}, {60.f, 40.f}};
  ev::Boid b6{{100.f, 100.f}, {0.f, 0.f}};

  ev::Flock flock{{b1, b2, b3, b4, b5, b6}};

  auto separation = flock.separation();
  auto alignment = flock.alignment();
  auto cohesion = flock.cohesion();

  const float s = ev::constants::defaultSeparationStrength;  // 0.5f
  const float a = ev::constants::defaultAlignmentStrength;   // 0.03f
  const float c = ev::constants::defaultCohesionStrength;    // 0.015f
  const float sr = ev::constants::defaultSeparationRange;    // 15.f
  const float i = ev::constants::defaultInteractionRange;    // 150.f

  //////////////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING SEPARATION") {
    // Separation Distance Checks
    CHECK(distance(b1, b2) < sr);
    CHECK(distance(b1, b3) < sr);
    CHECK(distance(b1, b4) > sr);
    CHECK(distance(b1, b5) > sr);
    CHECK(distance(b2, b3) < sr);
    CHECK(distance(b2, b4) > sr);
    CHECK(distance(b2, b5) > sr);
    CHECK(distance(b3, b4) < sr);
    CHECK(distance(b3, b5) > sr);
    CHECK(distance(b4, b5) < sr);

    {
      // boid 1: b2 and b3 contribute.
      const float expX = -((b2.getPosition().x - b1.getPosition().x) +
                           (b3.getPosition().x - b1.getPosition().x)) *
                         s;
      const float expY = -((b2.getPosition().y - b1.getPosition().y) +
                           (b3.getPosition().y - b1.getPosition().y)) *
                         s;
      CHECK(separation[0].x == doctest::Approx(expX));
      CHECK(separation[0].y == doctest::Approx(expY));
    }

    {
      // boid 2: b1 and b3 contribute.
      const float expX = -((b1.getPosition().x - b2.getPosition().x) +
                           (b3.getPosition().x - b2.getPosition().x)) *
                         s;
      const float expY = -((b1.getPosition().y - b2.getPosition().y) +
                           (b3.getPosition().y - b2.getPosition().y)) *
                         s;
      CHECK(separation[1].x == doctest::Approx(expX));
      CHECK(separation[1].y == doctest::Approx(expY));
    }

    {
      // boid 3: b1, b2, and b4 contribute.
      const float expX = -((b1.getPosition().x - b3.getPosition().x) +
                           (b2.getPosition().x - b3.getPosition().x) +
                           (b4.getPosition().x - b3.getPosition().x)) *
                         s;
      const float expY = -((b1.getPosition().y - b3.getPosition().y) +
                           (b2.getPosition().y - b3.getPosition().y) +
                           (b4.getPosition().y - b3.getPosition().y)) *
                         s;
      CHECK(separation[2].x == doctest::Approx(expX));
      CHECK(separation[2].y == doctest::Approx(expY));
    }

    {
      // boid 4: b3 and b5 contribute.
      const float expX = -((b3.getPosition().x - b4.getPosition().x) +
                           (b5.getPosition().x - b4.getPosition().x)) *
                         s;
      const float expY = -((b3.getPosition().y - b4.getPosition().y) +
                           (b5.getPosition().y - b4.getPosition().y)) *
                         s;
      CHECK(separation[3].x == doctest::Approx(expX));
      CHECK(separation[3].y == doctest::Approx(expY));
    }

    {
      // boid 5: Only b4 contributes.
      const float expX = -(b4.getPosition().x - b5.getPosition().x) * s;
      const float expY = -(b4.getPosition().y - b5.getPosition().y) * s;
      CHECK(separation[4].x == doctest::Approx(expX));
      CHECK(separation[4].y == doctest::Approx(expY));
    }

    {
      // boid 6: No boids within separation range contribute.
      CHECK(separation[5].x == doctest::Approx(0.f));
      CHECK(separation[5].y == doctest::Approx(0.f));
    }

    //////////////////////////////////////////////////////////////////////////////////////////

    SUBCASE("TESTING ALIGNMENT") {
      // Interaction Distance Checks
      CHECK(distance(b1, b2) < i);
      CHECK(distance(b1, b3) < i);
      CHECK(distance(b1, b4) < i);
      CHECK(distance(b1, b5) < i);
      CHECK(distance(b2, b3) < i);
      CHECK(distance(b2, b4) < i);
      CHECK(distance(b2, b5) < i);
      CHECK(distance(b3, b4) < i);
      CHECK(distance(b3, b5) < i);
      CHECK(distance(b4, b5) < i);

      CHECK(distance(b1, b6) < i);
      CHECK(distance(b2, b6) < i);
      CHECK(distance(b3, b6) < i);
      CHECK(distance(b4, b6) < i);
      CHECK(distance(b5, b6) < i);

      // Alignment Vector Checks
      {
        // boid 1:
        const float sumX = (b2.getVelocity().x - b1.getVelocity().x) +
                           (b3.getVelocity().x - b1.getVelocity().x) +
                           (b4.getVelocity().x - b1.getVelocity().x) +
                           (b5.getVelocity().x - b1.getVelocity().x) +
                           (b6.getVelocity().x - b1.getVelocity().x);
        const float sumY = (b2.getVelocity().y - b1.getVelocity().y) +
                           (b3.getVelocity().y - b1.getVelocity().y) +
                           (b4.getVelocity().y - b1.getVelocity().y) +
                           (b5.getVelocity().y - b1.getVelocity().y) +
                           (b6.getVelocity().y - b1.getVelocity().y);
        const float expX = a * (sumX / 5.f);
        const float expY = a * (sumY / 5.f);
        CHECK(alignment[0].x == doctest::Approx(expX));
        CHECK(alignment[0].y == doctest::Approx(expY));
      }

      {
        // boid 2:
        const float sumX = (b1.getVelocity().x - b2.getVelocity().x) +
                           (b3.getVelocity().x - b2.getVelocity().x) +
                           (b4.getVelocity().x - b2.getVelocity().x) +
                           (b5.getVelocity().x - b2.getVelocity().x) +
                           (b6.getVelocity().x - b2.getVelocity().x);
        const float sumY = (b1.getVelocity().y - b2.getVelocity().y) +
                           (b3.getVelocity().y - b2.getVelocity().y) +
                           (b4.getVelocity().y - b2.getVelocity().y) +
                           (b5.getVelocity().y - b2.getVelocity().y) +
                           (b6.getVelocity().y - b2.getVelocity().y);
        const float expX = a * (sumX / 5.f);
        const float expY = a * (sumY / 5.f);
        CHECK(alignment[1].x == doctest::Approx(expX));
        CHECK(alignment[1].y == doctest::Approx(expY));
      }

      {
        // boid 3:
        const float sumX = (b2.getVelocity().x - b3.getVelocity().x) +
                           (b1.getVelocity().x - b3.getVelocity().x) +
                           (b4.getVelocity().x - b3.getVelocity().x) +
                           (b5.getVelocity().x - b3.getVelocity().x) +
                           (b6.getVelocity().x - b3.getVelocity().x);
        const float sumY = (b2.getVelocity().y - b3.getVelocity().y) +
                           (b1.getVelocity().y - b3.getVelocity().y) +
                           (b4.getVelocity().y - b3.getVelocity().y) +
                           (b5.getVelocity().y - b3.getVelocity().y) +
                           (b6.getVelocity().y - b3.getVelocity().y);
        const float expX = a * (sumX / 5.f);
        const float expY = a * (sumY / 5.f);
        CHECK(alignment[2].x == doctest::Approx(expX));
        CHECK(alignment[2].y == doctest::Approx(expY));
      }

      {
        // boid 4:
        const float sumX = (b2.getVelocity().x - b4.getVelocity().x) +
                           (b3.getVelocity().x - b4.getVelocity().x) +
                           (b1.getVelocity().x - b4.getVelocity().x) +
                           (b5.getVelocity().x - b4.getVelocity().x) +
                           (b6.getVelocity().x - b4.getVelocity().x);
        const float sumY = (b2.getVelocity().y - b4.getVelocity().y) +
                           (b3.getVelocity().y - b4.getVelocity().y) +
                           (b1.getVelocity().y - b4.getVelocity().y) +
                           (b5.getVelocity().y - b4.getVelocity().y) +
                           (b6.getVelocity().y - b4.getVelocity().y);
        const float expX = a * (sumX / 5.f);
        const float expY = a * (sumY / 5.f);
        CHECK(alignment[3].x == doctest::Approx(expX));
        CHECK(alignment[3].y == doctest::Approx(expY));
      }

      {
        // boid 5:
        const float sumX = (b2.getVelocity().x - b5.getVelocity().x) +
                           (b3.getVelocity().x - b5.getVelocity().x) +
                           (b4.getVelocity().x - b5.getVelocity().x) +
                           (b1.getVelocity().x - b5.getVelocity().x) +
                           (b6.getVelocity().x - b5.getVelocity().x);
        const float sumY = (b2.getVelocity().y - b5.getVelocity().y) +
                           (b3.getVelocity().y - b5.getVelocity().y) +
                           (b4.getVelocity().y - b5.getVelocity().y) +
                           (b1.getVelocity().y - b5.getVelocity().y) +
                           (b6.getVelocity().y - b5.getVelocity().y);
        const float expX = a * (sumX / 5.f);
        const float expY = a * (sumY / 5.f);
        CHECK(alignment[4].x == doctest::Approx(expX));
        CHECK(alignment[4].y == doctest::Approx(expY));
      }

      {
        // boid 6:
        const float sumX = (b2.getVelocity().x - b6.getVelocity().x) +
                           (b3.getVelocity().x - b6.getVelocity().x) +
                           (b4.getVelocity().x - b6.getVelocity().x) +
                           (b5.getVelocity().x - b6.getVelocity().x) +
                           (b1.getVelocity().x - b6.getVelocity().x);
        const float sumY = (b2.getVelocity().y - b6.getVelocity().y) +
                           (b3.getVelocity().y - b6.getVelocity().y) +
                           (b4.getVelocity().y - b6.getVelocity().y) +
                           (b5.getVelocity().y - b6.getVelocity().y) +
                           (b1.getVelocity().y - b6.getVelocity().y);
        const float expX = a * (sumX / 5.f);
        const float expY = a * (sumY / 5.f);
        CHECK(alignment[5].x == doctest::Approx(expX));
        CHECK(alignment[5].y == doctest::Approx(expY));
      }
    }

    //////////////////////////////////////////////////////////////////////////////////////////

    SUBCASE("TESTING COHESION") {
      {
        // boid 1, compute center of mass for boids 2,3,4,5,6.
        sf::Vector2f center =
            (b2.getPosition() + b3.getPosition() + b4.getPosition() +
             b5.getPosition() + b6.getPosition()) /
            5.f;
        CHECK(cohesion[0].x ==
              doctest::Approx(c * (center.x - b1.getPosition().x)));
        CHECK(cohesion[0].y ==
              doctest::Approx(c * (center.y - b1.getPosition().y)));
      }
      {
        // boid 2, center of mass for boids 1,3,4,5,6.
        sf::Vector2f center =
            (b1.getPosition() + b3.getPosition() + b4.getPosition() +
             b5.getPosition() + b6.getPosition()) /
            5.f;
        CHECK(cohesion[1].x ==
              doctest::Approx(c * (center.x - b2.getPosition().x)));
        CHECK(cohesion[1].y ==
              doctest::Approx(c * (center.y - b2.getPosition().y)));
      }
      {
        // boid 3, center of mass for boids 1,2,4,5,6.
        sf::Vector2f center =
            (b1.getPosition() + b2.getPosition() + b4.getPosition() +
             b5.getPosition() + b6.getPosition()) /
            5.f;
        CHECK(cohesion[2].x ==
              doctest::Approx(c * (center.x - b3.getPosition().x)));
        CHECK(cohesion[2].y ==
              doctest::Approx(c * (center.y - b3.getPosition().y)));
      }
      {
        // boid 4, center of mass for boids 1,2,3,5,6.
        sf::Vector2f center =
            (b1.getPosition() + b2.getPosition() + b3.getPosition() +
             b5.getPosition() + b6.getPosition()) /
            5.f;
        CHECK(cohesion[3].x ==
              doctest::Approx(c * (center.x - b4.getPosition().x)));
        CHECK(cohesion[3].y ==
              doctest::Approx(c * (center.y - b4.getPosition().y)));
      }
      {
        // boid 5, center of mass for boids 1,2,3,4,6.
        sf::Vector2f center =
            (b1.getPosition() + b2.getPosition() + b3.getPosition() +
             b4.getPosition() + b6.getPosition()) /
            5.f;
        CHECK(cohesion[4].x ==
              doctest::Approx(c * (center.x - b5.getPosition().x)));
        CHECK(cohesion[4].y ==
              doctest::Approx(c * (center.y - b5.getPosition().y)));
      }
      {
        // boid 6, center of mass for boids 1,2,3,4,5.
        sf::Vector2f center =
            (b1.getPosition() + b2.getPosition() + b3.getPosition() +
             b4.getPosition() + b5.getPosition()) /
            5.f;
        CHECK(cohesion[5].x ==
              doctest::Approx(c * (center.x - b6.getPosition().x)));
        CHECK(cohesion[5].y ==
              doctest::Approx(c * (center.y - b6.getPosition().y)));
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING PARAMETERS") {
  SUBCASE("TESTING INTERACTION PARAMETERS") {
    ev::Boid b1{};
    ev::Boid b2{};
    ev::Flock flock{{b1, b2}, {}};

    CHECK(ev::Flock::getParameters().separationStrength ==
          ev::constants::defaultSeparationStrength);
    CHECK(ev::Flock::getParameters().separationRange ==
          ev::constants::defaultSeparationRange);
    CHECK(ev::Flock::getParameters().alignmentStrength ==
          ev::constants::defaultAlignmentStrength);
    CHECK(ev::Flock::getParameters().cohesionStrength ==
          ev::constants::defaultCohesionStrength);
    CHECK(ev::Flock::getParameters().interactionRange ==
          ev::constants::defaultInteractionRange);
    CHECK(ev::Flock::getParameters().repelStrength ==
          ev::constants::defaultRepelStrength);
    CHECK(ev::Flock::getParameters().repelRange ==
          ev::constants::defaultRepelRange);
    CHECK(ev::Flock::getParameters().clickStrength ==
          ev::constants::defaultClickStrenght);

          ev::Flock::setParameters({1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f});

    CHECK(ev::Flock::getParameters().separationStrength == 1.f);
    CHECK(ev::Flock::getParameters().separationRange == 2.f);
    CHECK(ev::Flock::getParameters().alignmentStrength == 3.f);
    CHECK(ev::Flock::getParameters().cohesionStrength == 4.f);
    CHECK(ev::Flock::getParameters().interactionRange == 5.f);
    CHECK(ev::Flock::getParameters().repelStrength == 6.f);
    CHECK(ev::Flock::getParameters().repelRange == 7.f);
    CHECK(ev::Flock::getParameters().clickStrength == 8.f);

    ev::Flock::setSeparationStrength(15.f);
    ev::Flock::setSeparationRange(15.f);
    ev::Flock::setAlignmentStrength(15.f);
    ev::Flock::setCohesionStrength(15.f);
    ev::Flock::setInteractionRange(15.f);
    ev::Flock::setRepelStrength(15.f);
    ev::Flock::setRepelRange(15.f);
    ev::Flock::setClickStrength(15.f);

    CHECK(ev::Flock::getParameters().separationStrength == 15.f);
    CHECK(ev::Flock::getParameters().separationRange == 15.f);
    CHECK(ev::Flock::getParameters().alignmentStrength == 15.f);
    CHECK(ev::Flock::getParameters().cohesionStrength == 15.f);
    CHECK(ev::Flock::getParameters().interactionRange == 15.f);
    CHECK(ev::Flock::getParameters().repelStrength == 15.f);
    CHECK(ev::Flock::getParameters().repelRange == 15.f);
    CHECK(ev::Flock::getParameters().clickStrength == 15.f);
  }

  SUBCASE("TESTING MODES") {
    CHECK(ev::Flock::getToroidalMode() == false);
    CHECK(ev::Flock::getRepulsiveClick() == false);

    ev::Flock::setToroidalMode(true);
    ev::Flock::setRepulsiveClick(true);

    CHECK(ev::Flock::getToroidalMode() == true);
    CHECK(ev::Flock::getRepulsiveClick() == true);
  }

  // resetting flock parameters to default values since they are static.

  ev::Flock::setParameters(ev::constants::defaultFlockParameters);
  ev::Flock::setToroidalMode(false);
  ev::Flock::setRepulsiveClick(false);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING RULES on SPECIAL CASES") {
  // REMEMBER TESTS MIGHT NEED TO BE CHANGED IF DEFAULT PARAMETERS OF
  // INTERACTION ARE CHANGED!

  ev::Boid b1{{100.f, 500.f}, {200.f, 200.f}};
  ev::Boid b2{{150.f, 300.f}, {210.f, 150.f}};
  ev::Boid b3{{250.f, 300.f}, {190.f, 180.f}};
  ev::Flock flock{{b1, b2, b3}};

  std::vector<sf::Vector2f> separation{flock.separation()};
  std::vector<sf::Vector2f> alignment{flock.alignment()};
  std::vector<sf::Vector2f> cohesion{flock.cohesion()};

  // const float &s{ev::constants::defaultSeparationStrength};
  const float &a{ev::constants::defaultAlignmentStrength};
  // const float &c{ev::constants::defaultCohesionStrength};

  ////////////////////////////////////////////////////////////////////////////////
  // Checking rules if some boids are out of the interaction range

  SUBCASE("SEPARATION") {
    // std::cout << distance(b1, b2) << '\n';
    // std::cout << distance(b2, b3) << '\n';
    // std::cout << distance(b1, b3) << '\n';

    CHECK(separation[0].x == 0.f);
    CHECK(separation[0].y == 0.f);
    CHECK(separation[1].x == 0.f);
    CHECK(separation[1].y == 0.f);
    CHECK(separation[2].x == 0.f);
    CHECK(separation[2].y == 0.f);
  }

  ////////////////////////////////////////////////////////////////////////////////

  SUBCASE("ALIGNMENT") {
    CHECK(alignment[0].x == 0.f);
    CHECK(alignment[0].y == 0.f);

    CHECK(alignment[1].x == a * (b3.getVelocity().x - b2.getVelocity().x));
    CHECK(alignment[1].y == a * (b3.getVelocity().y - b2.getVelocity().y));
    CHECK(alignment[2].x == a * (b2.getVelocity().x - b3.getVelocity().x));
    CHECK(alignment[2].y == a * (b2.getVelocity().y - b3.getVelocity().y));

    CHECK(alignment[1].x == doctest::Approx(-0.6f));
    CHECK(alignment[1].y == doctest::Approx(+0.9f));
    CHECK(alignment[2].x == doctest::Approx(+0.6f));
    CHECK(alignment[2].y == doctest::Approx(-0.9f));
  }

  ////////////////////////////////////////////////////////////////////////////////

  SUBCASE("COHESION") {
    CHECK(cohesion[0].x == 0.f);
    CHECK(cohesion[0].y == 0.f);

    CHECK(cohesion[1].x == +1.5f);
    CHECK(cohesion[1].y == 0.f);
    CHECK(cohesion[2].x == -1.5f);
    CHECK(cohesion[2].y == 0.f);
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING UPDATE FUNCTION") {
  ev::Boid b1{{100.f, 500.f}, {200.f, 200.f}};
  ev::Boid b2{{150.f, 300.f}, {210.f, 150.f}};
  ev::Boid b3{{250.f, 300.f}, {190.f, 180.f}};
  ev::Flock flock{{b1, b2, b3}};

  SUBCASE("TESTING UPDATE") {
    ////////////////////////////////////////////////////////////////////////////////
    // Same flock as before to make it simpler

    flock.updateFlock();

    CHECK(flock.getBoid(0).getPosition().x ==
          doctest::Approx(100.f + b1.getVelocity().x / ev::constants::speedScale));
    CHECK(flock.getBoid(0).getPosition().y ==
          doctest::Approx(500.f + b1.getVelocity().y / ev::constants::speedScale));
    CHECK(flock.getBoid(0).getVelocity().x == doctest::Approx(200.f));
    CHECK(flock.getBoid(0).getVelocity().y == doctest::Approx(200.f));

    CHECK(flock.getBoid(1).getPosition().x ==
          doctest::Approx(150.f + b2.getVelocity().x / ev::constants::speedScale));
    CHECK(flock.getBoid(1).getPosition().y ==
          doctest::Approx(300.f + b2.getVelocity().y / ev::constants::speedScale));
    CHECK(flock.getBoid(1).getVelocity().x == doctest::Approx(210.9f));
    CHECK(flock.getBoid(1).getVelocity().y == doctest::Approx(150.9f));

    CHECK(flock.getBoid(2).getPosition().x ==
          doctest::Approx(250.f + b3.getVelocity().x / ev::constants::speedScale));
    CHECK(flock.getBoid(2).getPosition().y ==
          doctest::Approx(300.f + b3.getVelocity().y / ev::constants::speedScale));
    CHECK(flock.getBoid(2).getVelocity().x == doctest::Approx(189.1f));
    CHECK(flock.getBoid(2).getVelocity().y == doctest::Approx(179.1f));

    std::cout << ev::distance({200, 200}, {150, 300}) << " "
              << ev::distance({200, 200}, {250, 300}) << '\n';
  }

  ////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING REPEL CLICK in ATTRACTIVE MODE") {
    ev::Flock::setRepulsiveClick(false);
    flock.repelOnClick({200, 200});

    CHECK(flock.getBoid(0).getVelocity().x == doctest::Approx(200.f));
    CHECK(flock.getBoid(0).getVelocity().y == doctest::Approx(200.f));
    CHECK(flock.getBoid(1).getVelocity().x ==
          doctest::Approx(210.f + 50 * ev::constants::defaultClickStrenght));
    CHECK(flock.getBoid(1).getVelocity().y ==
          doctest::Approx(150.f + (-100) * ev::constants::defaultClickStrenght));
    CHECK(flock.getBoid(2).getVelocity().x ==
          doctest::Approx(190.f + (-50) * ev::constants::defaultClickStrenght));
    CHECK(flock.getBoid(2).getVelocity().y ==
          doctest::Approx(180.f + (-100) * ev::constants::defaultClickStrenght));
  }

  ////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING REPEL CLICK in REPULSIVE MODE") {
    ev::Flock::setRepulsiveClick(true);
    flock.repelOnClick({200, 200});

    CHECK(flock.getBoid(0).getVelocity().x == doctest::Approx(200.f));
    CHECK(flock.getBoid(0).getVelocity().y == doctest::Approx(200.f));
    CHECK(flock.getBoid(1).getVelocity().x ==
          doctest::Approx(210.f + (-50) * ev::constants::defaultClickStrenght));
    CHECK(flock.getBoid(1).getVelocity().y ==
          doctest::Approx(150.f + (100) * ev::constants::defaultClickStrenght));
    CHECK(flock.getBoid(2).getVelocity().x ==
          doctest::Approx(190.f + (50) * ev::constants::defaultClickStrenght));
    CHECK(flock.getBoid(2).getVelocity().y ==
          doctest::Approx(180.f + (100) * ev::constants::defaultClickStrenght));

          ev::Flock::setRepulsiveClick(false);
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING RULES on TOROIDAL MODE") {
  // Create 3 boids: 1 near the right edge, 2 near the left edge, 3 centered

  ev::Boid b1{{700.f, 360.f}, {150.f, 0.f}};
  ev::Boid b2{{20.f, 360.f}, {150.f, 0.f}};
  ev::Boid b3{{360.f, 360.f}, {150.f, 0.f}};
  ev::Flock flock{{b1, b2, b3}};

  ev::Flock::setToroidalMode(true);

  ////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING TOROIDAL COHESION") {
    // Calculate toroidal cohesion vectors.
    auto cohesionVecs = flock.toroidalCohesion();

    // Boid 1: Only Boid 2 is within the interaction range (after
    // adjustment).
    CHECK(cohesionVecs[0].x == doctest::Approx(0.6f));
    CHECK(cohesionVecs[0].y == doctest::Approx(0.f));

    // Boid 2: Only Boid 1 contributes.
    CHECK(cohesionVecs[1].x == doctest::Approx(-0.6f));
    CHECK(cohesionVecs[1].y == doctest::Approx(0.f));

    // Boid 3: Neither neighbor is close enough after adjustments.
    CHECK(cohesionVecs[2].x == doctest::Approx(0.f));
    CHECK(cohesionVecs[2].y == doctest::Approx(0.f));
  }

  ////////////////////////////////////////////////////////////////////////////////

  SUBCASE("TESTING UPDATE in TOROIDAL MODE") {
    flock.updateFlock();

    const ev::Boid &boid0 = flock.getBoid(0);
    const ev::Boid &boid1 = flock.getBoid(1);
    const ev::Boid &boid2 = flock.getBoid(2);

    // boid 1:
    //   Position: (700,360) + (150/150, 0) = (701,360)
    //   Velocity: (150,0) + cohesion (0.6,0) = (150.6,0)
    CHECK(boid0.getPosition().x == doctest::Approx(701.f));
    CHECK(boid0.getPosition().y == doctest::Approx(360.f));
    CHECK(boid0.getVelocity().x == doctest::Approx(150.6f));
    CHECK(boid0.getVelocity().y == doctest::Approx(0.f));

    // boid 2:
    //   Position: (20,360) + (150/150, 0) = (21,360)
    //   Velocity: (150,0) + (-0.6,0) = (149.4,0),
    //             checkMinimumSpeed leaves it to (150,0)
    CHECK(boid1.getPosition().x == doctest::Approx(21.f));
    CHECK(boid1.getPosition().y == doctest::Approx(360.f));
    CHECK(boid1.getVelocity().x ==
          doctest::Approx(150.f));  // adjusted from 149.4f to 150.f
    CHECK(boid1.getVelocity().y == doctest::Approx(0.f));

    // boid 3:
    //   Position: (360,360) + (150/150, 0) = (361,360)
    //   Velocity: (150,0) + (0,0) = (150,0)
    CHECK(boid2.getPosition().x == doctest::Approx(361.f));
    CHECK(boid2.getPosition().y == doctest::Approx(360.f));
    CHECK(boid2.getVelocity().x == doctest::Approx(150.f));
    CHECK(boid2.getVelocity().y == doctest::Approx(0.f));
  }

  ev::Flock::setToroidalMode(false);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING REPEL") {
  // Flock 0: Three boids
  // a1: Positioned near b1, so should be repelled.
  // a2: Positioned near b2, so should be repelled.
  // a3: Placed far from any boid in Flock 1, so no repel force.
  ev::Boid a1{{100.f, 100.f}, {0.f, 0.f}};
  ev::Boid a2{{150.f, 150.f}, {0.f, 0.f}};
  ev::Boid a3{{300.f, 300.f}, {0.f, 0.f}};
  ev::Flock flock0{{a1, a2, a3}};

  // Flock 1: Three boids
  // b1 is close to a1, b2 is close to a2, b3 is far away.
  ev::Boid b1{{105.f, 105.f}, {0.f, 0.f}};
  ev::Boid b2{{140.f, 140.f}, {0.f, 0.f}};
  ev::Boid b3{{400.f, 400.f}, {0.f, 0.f}};
  ev::Flock flock1{{b1, b2, b3}};
  std::vector<ev::Flock> flockstack{flock0, flock1};

  auto repelSpeeds = repel(flockstack, 0);

  // Expected calculations:
  // a1: Only b1 is within range (distance = 7.07 < 20).
  //   (b1 - a1) = (105 - 100, 105 - 100) = (5, 5),
  //   repel contribution = (5, 5) * (-0.3) = (-1.5, -1.5).
  //
  // a2: Only b2 is within range (distance = 14.14 < 20).
  //   (b2 - a2) = (140 - 150, 140 - 150) = (-10, -10),
  //   repel contribution = (-10, -10) * (-0.3) = (3, 3).
  //
  // For a3: No boid in flock1 is close (distance > 20), so repel force is
  // (0, 0).

  const float repelStrength{ev::Flock::getParameters().repelStrength};
  sf::Vector2f a1expected =
      ((sf::Vector2f{105.f, 105.f} - sf::Vector2f{100.f, 100.f})) *
      (-repelStrength);
  sf::Vector2f a2expected =
      ((sf::Vector2f{140.f, 140.f} - sf::Vector2f{150.f, 150.f})) *
      (-repelStrength);
  sf::Vector2f a3expected{0.f, 0.f};

  // Check there is a repel force for each boid in flock0.
  CHECK(repelSpeeds.size() == 3);

  CHECK(repelSpeeds[0].x == doctest::Approx(a1expected.x));
  CHECK(repelSpeeds[0].y == doctest::Approx(a1expected.y));
  CHECK(repelSpeeds[1].x == doctest::Approx(a2expected.x));
  CHECK(repelSpeeds[1].y == doctest::Approx(a2expected.y));
  CHECK(repelSpeeds[2].x == doctest::Approx(a3expected.x));
  CHECK(repelSpeeds[2].y == doctest::Approx(a3expected.y));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("TESTING CREATE FLOCK") {
  sf::Vector2f center{20, 20};

  ev::Flock flock{ev::createFlock(10, center, sf::Color::Green)};

  CHECK(flock.getFlockColor() == sf::Color::Green);
  CHECK(flock.getSize() == 10);

  for (size_t i{0}; i < flock.getSize(); i++) {
    CHECK(ev::distance(flock.getFlockPositions()[i], center) <
          ev::constants::randomPositionRange);

    CHECK(flock.getFlockPositions()[i].x >= 0.f);
    CHECK(flock.getFlockPositions()[i].x <= ev::constants::fieldSide);
    CHECK(flock.getFlockPositions()[i].y >= 0.f);
    CHECK(flock.getFlockPositions()[i].y <= ev::constants::fieldSide);
  }
}
