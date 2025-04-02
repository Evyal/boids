#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <SFML/Graphics.hpp>
#include <cmath>

#include "../include/doctest.h"
#include "../include/statistics.hpp"

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Test distance calculations with 5 points on a line") {
  std::vector<sf::Vector2f> points = {
      {0.f, 0.f}, {1.f, 0.f}, {2.f, 0.f}, {3.f, 0.f}, {4.f, 0.f}};

  std::vector<float> distances = ev::calculateDistances(points);

  // function calculateDistances calculates like this:
  // [0] -> others,
  // [1] -> others
  // [2] -> others
  // [3] -> [4]

  // so for example the first 4 elements are distances [0][1], [0][2], [0][3],
  // [0][4].

  // CHECK there are N*(N-1)/2, 5*4/2 = 10 pairs
  CHECK(distances.size() == 10);

  CHECK(distances[0] == 1.f);
  CHECK(distances[1] == 2.f);
  CHECK(distances[2] == 3.f);
  CHECK(distances[3] == 4.f);
  CHECK(distances[4] == 1.f);
  CHECK(distances[5] == 2.f);
  CHECK(distances[6] == 3.f);
  CHECK(distances[7] == 1.f);
  CHECK(distances[8] == 2.f);
  CHECK(distances[9] == 1.f);

  //////////////////////////////////////////////////////////////////////////////////////////
  // Test calculateMean

  float mean = ev::calculateMean(distances);

  CHECK(mean == doctest::Approx(2.f));

  //////////////////////////////////////////////////////////////////////////////////////////
  // Test calculateStandardDeviation.
  // Variance is calculated with N - 1 = 9
  // deviation is sqrt(10/9) = 1.05409...
  float stddev = ev::calculateStandardDeviation(distances, mean);
  CHECK(stddev == doctest::Approx(sqrtf(10.f / 9.f)));
}

//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Test calculateMean with empty vector") {
  std::vector<float> distances;
  CHECK(ev::calculateMean(distances) == 0.f);
}

//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Test calculateStandardDeviation with one element") {
  std::vector<float> distances = {1.f};

  CHECK(ev::calculateMean(distances) == doctest::Approx(1.f));

  // With only one distance, standard deviation should be 0.
  CHECK(ev::calculateStandardDeviation(distances, 1.f) == 0.f);
}

//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Test toroidal distances") {
  std::vector<sf::Vector2f> positions{{360, 100}, {360, 700}};
  CHECK(ev::calculateToroidalDistances(positions)[0] == doctest::Approx(120.f));

  std::vector<sf::Vector2f> positions2{{20, 20}, {-20, -10}, {0, 0}};
  CHECK(ev::calculateToroidalDistances(positions2)[0] == doctest::Approx(50.f));
  CHECK(ev::calculateToroidalDistances(positions2)[1] ==
        doctest::Approx(sqrtf(800.f)));
  CHECK(ev::calculateToroidalDistances(positions2)[2] ==
        doctest::Approx(sqrtf(500)));
}