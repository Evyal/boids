#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../constants.hpp"
#include "../flock.hpp"
#include "doctest.h"
#include <SFML/Graphics.hpp>
#include <cmath>

// //////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////

// TEST_CASE("TESTING CLASS FLOCK") {

//   //////////////////////////////////////////////////////////////////////////////////////////
//   // GETTERS

//   SUBCASE("TESTING CONSTRUCTORS and GETTERS") {
//     // sf::Vector2f center{375, 375};

//     Boid b1{{0.f, 0.f}, {0.f, 0.f}};
//     Boid b2{{10.f, 10.f}, {0.f, 0.f}};
//     Boid b3{{20.f, 10.f}, {0.f, 15.f}};
//     Boid b4{{10.f, 20.f}, {10.f, 0.f}};
//     Boid b5{{20.f, 20.f}, {0.f, 10.f}};

//     Flock flock1{};

//     CHECK(flock1.getSize() == 0);
//     CHECK(flock1.getFlockColor() == sf::Color::Black);

//     Flock flock2{{b1, b2}};

//     CHECK(flock2.getSize() == 2);
//     CHECK(flock2.getFlockColor() == sf::Color::Black);

//     Flock flock3{{b1, b2, b3, b4, b5}, sf::Color::Red};

//     CHECK(flock3.getBoid(0).getPosition().x == 0.f);
//     CHECK(flock3.getBoid(0).getPosition().y == 0.f);
//     CHECK(flock3.getBoid(1).getPosition().x == 10.f);
//     CHECK(flock3.getBoid(1).getPosition().y == 10.f);
//     CHECK(flock3.getBoid(2).getPosition().x == 20.f);
//     CHECK(flock3.getBoid(2).getPosition().y == 10.f);
//     CHECK(flock3.getBoid(3).getPosition().x == 10.f);
//     CHECK(flock3.getBoid(3).getPosition().y == 20.f);
//     CHECK(flock3.getBoid(4).getPosition().x == 20.f);
//     CHECK(flock3.getBoid(4).getPosition().y == 20.f);

//     CHECK(flock3.getSize() == 5);
//     CHECK(flock3.getFlockColor() == sf::Color::Red);

//     // CHECK(flock3.getMeanPosition().x == 12.f);
//     // CHECK(flock3.getMeanPosition().y == 12.f);
//     // CHECK(flock3.getMeanVelocity().x == 2.f);
//     // CHECK(flock3.getMeanVelocity().y == 5.f);
//     CHECK(flock3.getMeanSpeed() == 7.f);

//     Boid b6{{10.f, 50.f}, {200.f, 150.f}};
//     Boid b7{{20.f, 40.f}, {100.f, 250.f}};
//     Boid b8{{30.f, 60.f}, {50.f, 120.f}};

//     Flock flock4{{b6, b7, b8}};

//     CHECK(flock4.getFlockPositions().at(0).x == 10.f);
//     CHECK(flock4.getFlockPositions().at(0).y == 50.f);
//     CHECK(flock4.getFlockPositions().at(1).x == 20.f);
//     CHECK(flock4.getFlockPositions().at(1).y == 40.f);
//     CHECK(flock4.getFlockPositions().at(2).x == 30.f);
//     CHECK(flock4.getFlockPositions().at(2).y == 60.f);

//     CHECK(flock4.getFlockVelocities().at(0).x == 200.f);
//     CHECK(flock4.getFlockVelocities().at(0).y == 150.f);
//     CHECK(flock4.getFlockVelocities().at(1).x == 100.f);
//     CHECK(flock4.getFlockVelocities().at(1).y == 250.f);
//     CHECK(flock4.getFlockVelocities().at(2).x == 50.f);
//     CHECK(flock4.getFlockVelocities().at(2).y == 120.f);

//     CHECK(flock4.getSpeedVector().at(0) == 250.f);
//     CHECK(flock4.getSpeedVector().at(2) == 130.f);
//   }

//   //////////////////////////////////////////////////////////////////////////////////////////
//   //

//   SUBCASE("TESTING RULES") {
//     Boid b1{{10.f, 50.f}, {20.f, 50.f}};
//     Boid b2{{15.f, 45.f}, {10.f, 20.f}};
//     Boid b3{{20.f, 40.f}, {40.f, 30.f}};
//     Boid b4{{25.f, 30.f}, {70.f, 10.f}};
//     Boid b5{{30.f, 20.f}, {60.f, 40.f}};
//     Boid b6{{100.f, 100.f}, {0.f, 0.f}};

//     Flock flock{{b1, b2, b3, b4, b5, b6}};

//     std::vector<sf::Vector2f> separation{
//         flock.Separation(constants::defaultSeparationStrenght,
//                          constants::defaultSeparationRange)};

//     std::vector<sf::Vector2f> alignemnt{
//         flock.Alignment(constants::defaultAlignmentStrenght,
//                         constants::defaultInteractionRange)};

//     std::vector<sf::Vector2f> cohesion{
//         flock.Cohesion(constants::defaultCohesionStrenght,
//                        constants::defaultInteractionRange)};

//     // DEFAULT SEPARATION STRENGHT = 0.5f
//     // DEFAULT SEPARATION RANGE = 15.f

//     CHECK(distance(b1, b2) < 15.f); //
//     CHECK(distance(b1, b3) < 15.f); //
//     CHECK(distance(b1, b4) > 15.f);
//     CHECK(distance(b1, b5) > 15.f);
//     CHECK(distance(b2, b3) < 15.f); //
//     CHECK(distance(b2, b4) > 15.f);
//     CHECK(distance(b2, b5) > 15.f);
//     CHECK(distance(b3, b4) < 15.f); //
//     CHECK(distance(b3, b5) > 15.f);
//     CHECK(distance(b4, b5) < 15.f); //

//     CHECK(separation[0].x == -(b2.getPosition().x - b1.getPosition().x +
//                                b3.getPosition().x - b1.getPosition().x) *
//                                  constants::defaultSeparationStrenght);
//     CHECK(separation[0].y == -(b2.getPosition().y - b1.getPosition().y +
//                                b3.getPosition().y - b1.getPosition().y) *
//                                  constants::defaultSeparationStrenght);

//     CHECK(separation[1].x == -(b1.getPosition().x - b2.getPosition().x +
//                                b3.getPosition().x - b2.getPosition().x) *
//                                  constants::defaultSeparationStrenght);
//     CHECK(separation[1].y == -(b1.getPosition().y - b2.getPosition().y +
//                                b3.getPosition().y - b2.getPosition().y) *
//                                  constants::defaultSeparationStrenght);

//     CHECK(separation[2].x ==
//           -(b1.getPosition().x - b3.getPosition().x + b2.getPosition().x -
//             b3.getPosition().x + b4.getPosition().x - b3.getPosition().x) *
//               constants::defaultSeparationStrenght);
//     CHECK(separation[2].y ==
//           -(b1.getPosition().y - b3.getPosition().y + b2.getPosition().y -
//             b3.getPosition().y + b4.getPosition().y - b3.getPosition().y) *
//               constants::defaultSeparationStrenght);

//     CHECK(separation[3].x == -(b3.getPosition().x - b4.getPosition().x +
//                                b5.getPosition().x - b4.getPosition().x) *
//                                  constants::defaultSeparationStrenght);
//     CHECK(separation[3].y == -(b3.getPosition().y - b4.getPosition().y +
//                                b5.getPosition().y - b4.getPosition().y) *
//                                  constants::defaultSeparationStrenght);

//     CHECK(separation[4].x == -(b4.getPosition().x - b5.getPosition().x) *
//                                  constants::defaultSeparationStrenght);
//     CHECK(separation[4].y == -(b4.getPosition().y - b5.getPosition().y) *
//                                  constants::defaultSeparationStrenght);

//     CHECK(separation[5].x == 0.f);
//     CHECK(separation[5].y == 0.f);

//     CHECK(distance(b1, b2) < 150.f);
//     CHECK(distance(b1, b3) < 150.f);
//     CHECK(distance(b1, b4) < 150.f);
//     CHECK(distance(b1, b5) < 150.f);
//     CHECK(distance(b2, b3) < 150.f);
//     CHECK(distance(b2, b4) < 150.f);
//     CHECK(distance(b2, b5) < 150.f);
//     CHECK(distance(b3, b4) < 150.f);
//     CHECK(distance(b3, b5) < 150.f);
//     CHECK(distance(b4, b5) < 150.f);

//     CHECK(distance(b1, b6) < 150.f);
//     CHECK(distance(b2, b6) < 150.f);
//     CHECK(distance(b3, b6) < 150.f);
//     CHECK(distance(b4, b6) < 150.f);
//     CHECK(distance(b5, b6) < 150.f);

//     CHECK(alignemnt[0].x ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b2.getVelocity().x - b1.getVelocity().x) +
//                            (b3.getVelocity().x - b1.getVelocity().x) +
//                            (b4.getVelocity().x - b1.getVelocity().x) +
//                            (b5.getVelocity().x - b1.getVelocity().x) +
//                            (b6.getVelocity().x - b1.getVelocity().x)) /
//                           5.f));
//     CHECK(alignemnt[0].y ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b2.getVelocity().y - b1.getVelocity().y) +
//                            (b3.getVelocity().y - b1.getVelocity().y) +
//                            (b4.getVelocity().y - b1.getVelocity().y) +
//                            (b5.getVelocity().y - b1.getVelocity().y) +
//                            (b6.getVelocity().y - b1.getVelocity().y)) /
//                           5.f));

//     CHECK(alignemnt[1].x ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b1.getVelocity().x - b2.getVelocity().x) +
//                            (b3.getVelocity().x - b2.getVelocity().x) +
//                            (b4.getVelocity().x - b2.getVelocity().x) +
//                            (b5.getVelocity().x - b2.getVelocity().x) +
//                            (b6.getVelocity().x - b2.getVelocity().x)) /
//                           5.f));
//     CHECK(alignemnt[1].y ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b1.getVelocity().y - b2.getVelocity().y) +
//                            (b3.getVelocity().y - b2.getVelocity().y) +
//                            (b4.getVelocity().y - b2.getVelocity().y) +
//                            (b5.getVelocity().y - b2.getVelocity().y) +
//                            (b6.getVelocity().y - b2.getVelocity().y)) /
//                           5.f));

//     CHECK(alignemnt[2].x ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b2.getVelocity().x - b3.getVelocity().x) +
//                            (b1.getVelocity().x - b3.getVelocity().x) +
//                            (b4.getVelocity().x - b3.getVelocity().x) +
//                            (b5.getVelocity().x - b3.getVelocity().x) +
//                            (b6.getVelocity().x - b3.getVelocity().x)) /
//                           5.f));
//     CHECK(alignemnt[2].y ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b2.getVelocity().y - b3.getVelocity().y) +
//                            (b1.getVelocity().y - b3.getVelocity().y) +
//                            (b4.getVelocity().y - b3.getVelocity().y) +
//                            (b5.getVelocity().y - b3.getVelocity().y) +
//                            (b6.getVelocity().y - b3.getVelocity().y)) /
//                           5.f));

//     CHECK(alignemnt[3].x ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b2.getVelocity().x - b4.getVelocity().x) +
//                            (b3.getVelocity().x - b4.getVelocity().x) +
//                            (b1.getVelocity().x - b4.getVelocity().x) +
//                            (b5.getVelocity().x - b4.getVelocity().x) +
//                            (b6.getVelocity().x - b4.getVelocity().x)) /
//                           5.f));
//     CHECK(alignemnt[3].y ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b2.getVelocity().y - b4.getVelocity().y) +
//                            (b3.getVelocity().y - b4.getVelocity().y) +
//                            (b1.getVelocity().y - b4.getVelocity().y) +
//                            (b5.getVelocity().y - b4.getVelocity().y) +
//                            (b6.getVelocity().y - b4.getVelocity().y)) /
//                           5.f));

//     CHECK(alignemnt[4].x ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b2.getVelocity().x - b5.getVelocity().x) +
//                            (b3.getVelocity().x - b5.getVelocity().x) +
//                            (b4.getVelocity().x - b5.getVelocity().x) +
//                            (b1.getVelocity().x - b5.getVelocity().x) +
//                            (b6.getVelocity().x - b5.getVelocity().x)) /
//                           5.f));
//     CHECK(alignemnt[4].y ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b2.getVelocity().y - b5.getVelocity().y) +
//                            (b3.getVelocity().y - b5.getVelocity().y) +
//                            (b4.getVelocity().y - b5.getVelocity().y) +
//                            (b1.getVelocity().y - b5.getVelocity().y) +
//                            (b6.getVelocity().y - b5.getVelocity().y)) /
//                           5.f));

//     CHECK(alignemnt[5].x ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b2.getVelocity().x - b6.getVelocity().x) +
//                            (b3.getVelocity().x - b6.getVelocity().x) +
//                            (b4.getVelocity().x - b6.getVelocity().x) +
//                            (b5.getVelocity().x - b6.getVelocity().x) +
//                            (b1.getVelocity().x - b6.getVelocity().x)) /
//                           5.f));
//     CHECK(alignemnt[5].y ==
//           doctest::Approx(constants::defaultAlignmentStrenght *
//                           ((b2.getVelocity().y - b6.getVelocity().y) +
//                            (b3.getVelocity().y - b6.getVelocity().y) +
//                            (b4.getVelocity().y - b6.getVelocity().y) +
//                            (b5.getVelocity().y - b6.getVelocity().y) +
//                            (b1.getVelocity().y - b6.getVelocity().y)) /
//                           5.f));

//     // COHESION

//     sf::Vector2f boid1CenterMass{(b2.getPosition() + b3.getPosition() +
//                                   b4.getPosition() + b5.getPosition() +
//                                   b6.getPosition()) /
//                                  5.f};
//     CHECK(cohesion[0].x ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid1CenterMass.x - b1.getPosition().x)));
//     CHECK(cohesion[0].y ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid1CenterMass.y - b1.getPosition().y)));

//     sf::Vector2f boid2CenterMass{(b1.getPosition() + b3.getPosition() +
//                                   b4.getPosition() + b5.getPosition() +
//                                   b6.getPosition()) /
//                                  5.f};
//     CHECK(cohesion[1].x ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid2CenterMass.x - b2.getPosition().x)));
//     CHECK(cohesion[1].y ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid2CenterMass.y - b2.getPosition().y)));

//     sf::Vector2f boid3CenterMass{(b2.getPosition() + b1.getPosition() +
//                                   b4.getPosition() + b5.getPosition() +
//                                   b6.getPosition()) /
//                                  5.f};
//     CHECK(cohesion[2].x ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid3CenterMass.x - b3.getPosition().x)));
//     CHECK(cohesion[2].y ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid3CenterMass.y - b3.getPosition().y)));

//     sf::Vector2f boid4CenterMass{(b2.getPosition() + b3.getPosition() +
//                                   b1.getPosition() + b5.getPosition() +
//                                   b6.getPosition()) /
//                                  5.f};
//     CHECK(cohesion[3].x ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid4CenterMass.x - b4.getPosition().x)));
//     CHECK(cohesion[3].y ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid4CenterMass.y - b4.getPosition().y)));

//     sf::Vector2f boid5CenterMass{(b2.getPosition() + b3.getPosition() +
//                                   b4.getPosition() + b1.getPosition() +
//                                   b6.getPosition()) /
//                                  5.f};
//     CHECK(cohesion[4].x ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid5CenterMass.x - b5.getPosition().x)));
//     CHECK(cohesion[4].y ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid5CenterMass.y - b5.getPosition().y)));

//     sf::Vector2f boid6CenterMass{(b2.getPosition() + b3.getPosition() +
//                                   b4.getPosition() + b5.getPosition() +
//                                   b1.getPosition()) /
//                                  5.f};
//     CHECK(cohesion[5].x ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid6CenterMass.x - b6.getPosition().x)));
//     CHECK(cohesion[5].y ==
//           doctest::Approx(constants::defaultCohesionStrenght *
//                           (boid6CenterMass.y - b6.getPosition().y)));
//   }

//   ////////////////////////////////////////////////////////////////////////////////
//   ////////////////////////////////////////////////////////////////////////////////

//   SUBCASE("TESTING RULES on SPECIAL CASES") {

//     // REMEMBER TESTS MIGHT NEED TO BE CHANGED IF DEFAULT PARAMETERS OF
//     // INTERACTION ARE CHANGED!

//     Boid b1{{100.f, 500.f}, {200.f, 300.f}};
//     Boid b2{{150.f, 300.f}, {100.f, 200.f}};
//     Boid b3{{250.f, 300.f}, {400.f, 300.f}};

//     //     std::cout << distance(b1, b2) << '\n';
//     //     std::cout << distance(b2, b3) << '\n';
//     //     std::cout << distance(b1, b3) << '\n';

//     Flock flock{{b1, b2, b3}};

//     ////////////////////////////////////////////////////////////////////////////////
//     // CHECKING RULES if some boids are OUT OF THE INTERACTION RANGE

//     std::vector<sf::Vector2f> separation{
//         flock.Separation(constants::defaultSeparationStrenght,
//                          constants::defaultSeparationRange)};

//     std::vector<sf::Vector2f> alignemnt{
//         flock.Alignment(constants::defaultAlignmentStrenght,
//                         constants::defaultInteractionRange)};

//     std::vector<sf::Vector2f> cohesion{
//         flock.Cohesion(constants::defaultCohesionStrenght,
//                        constants::defaultInteractionRange)};

//     CHECK(separation[0].x == 0.f);
//     CHECK(separation[0].y == 0.f);
//     CHECK(separation[1].x == 0.f);
//     CHECK(separation[1].y == 0.f);
//     CHECK(separation[2].x == 0.f);
//     CHECK(separation[2].y == 0.f);

//     ////////////////////////////////////////////////////////////////////////////////

//     CHECK(alignemnt[0].x == 0.f);
//     CHECK(alignemnt[0].y == 0.f);

//     CHECK(alignemnt[1].x == constants::defaultAlignmentStrenght *
//                                 (b3.getVelocity().x - b2.getVelocity().x));
//     CHECK(alignemnt[1].y == constants::defaultAlignmentStrenght *
//                                 (b3.getVelocity().y - b2.getVelocity().y));
//     CHECK(alignemnt[2].x == constants::defaultAlignmentStrenght *
//                                 (b2.getVelocity().x - b3.getVelocity().x));
//     CHECK(alignemnt[2].y == constants::defaultAlignmentStrenght *
//                                 (b2.getVelocity().y - b3.getVelocity().y));

//     CHECK(alignemnt[1].x == +4.5f);
//     CHECK(alignemnt[1].y == +1.5f);
//     CHECK(alignemnt[2].x == -4.5f);
//     CHECK(alignemnt[2].y == -1.5f);

//     ////////////////////////////////////////////////////////////////////////////////

//     CHECK(cohesion[0].x == 0.f);
//     CHECK(cohesion[0].y == 0.f);

//     CHECK(cohesion[1].x == +1.5f);
//     CHECK(cohesion[1].y == 0.f);
//     CHECK(cohesion[2].x == -1.5f);
//     CHECK(cohesion[2].y == 0.f);
//   }

//   ////////////////////////////////////////////////////////////////////////////////
//   ////////////////////////////////////////////////////////////////////////////////

//   SUBCASE("TESTING UPDATE") {
//     Boid b1{{100.f, 500.f}, {200.f, 300.f}};
//     Boid b2{{150.f, 300.f}, {100.f, 200.f}};
//     Boid b3{{250.f, 300.f}, {400.f, 300.f}};

//     //     std::cout << distance(b1, b2) << '\n';
//     //     std::cout << distance(b2, b3) << '\n';
//     //     std::cout << distance(b1, b3) << '\n';

//     Flock flock{{b1, b2, b3}};
//   }

//   ////////////////////////////////////////////////////////////////////////////////
//   ////////////////////////////////////////////////////////////////////////////////

//   SUBCASE("TESTING RULES on TOROIDAL MODE") {

//     toroidal = true;

//     ////////////////////////////////////////////////////////////////////////////////
//     // CHECKING RULES on TOROIDAL MODE

//     Boid b1{{100.f, 500.f}, {200.f, 300.f}};
//     Boid b2{{150.f, 300.f}, {100.f, 200.f}};
//     Boid b3{{250.f, 300.f}, {400.f, 300.f}};

//     //     std::cout << distance(b1, b2) << '\n';
//     //     std::cout << distance(b2, b3) << '\n';
//     //     std::cout << distance(b1, b3) << '\n';

//     Flock flock{{b1, b2, b3}};

//     ////////////////////////////////////////////////////////////////////////////////
//     // SEPARATION RULE is the SAME
//     // ALGINMENT RULE is the SAME

//     ////////////////////////////////////////////////////////////////////////////////
//     // TESTING COHESION in TOROIDAL

    

//     ////////////////////////////////////////////////////////////////////////////////
//     // TESTING UPDATE in TOROIDAL
//   }

//   ////////////////////////////////////////////////////////////////////////////////
//   ////////////////////////////////////////////////////////////////////////////////

//   SUBCASE("TESTING REPEL") {
//     // REPEL
//   }

//   ////////////////////////////////////////////////////////////////////////////////
//   ////////////////////////////////////////////////////////////////////////////////

//   SUBCASE("TESTING CREATE FLOCK") {}
// }
