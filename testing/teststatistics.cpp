#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <SFML/Graphics.hpp>
#include <cmath>

#include "doctest.h"
#include "statistics.hpp"

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Test distance calculations with 5 points on a line") {
  std::vector<sf::Vector2f> points = {
      {0.f, 0.f}, {1.f, 0.f}, {2.f, 0.f}, {3.f, 0.f}, {4.f, 0.f}};

  float mean = ev::distanceStatistics(points).mean;
  float sigma = ev::distanceStatistics(points).sigma;

  CHECK(mean == doctest::Approx(2.f));
  CHECK(sigma == doctest::Approx(sqrtf(10.f / 9.f)));
}

//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Test calculateMean with empty vector") {
  std::vector<sf::Vector2f> positions;
  CHECK(ev::distanceStatistics(positions).sigma == 0.f);
}

//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Test calculateStandardDeviation with one element") {
  std::vector<float> speeds = {1.f};

  CHECK(ev::speedStatistics(speeds).mean == doctest::Approx(1.f));

  // Only one distance, standard deviation should be 0.
  CHECK(ev::speedStatistics(speeds).sigma == 0.f);
}

//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Test toroidal distances") {
  //////////////////////////////////////////////////////////////////////////////////////////
  // Case 1: two points

  std::vector<sf::Vector2f> positions1{{360, 100}, {360, 700}};
  auto stats1 = ev::toroidalDistanceStatistics(positions1);

  // expected toroidal distance: 120, sigma = 0.
  CHECK(stats1.mean == doctest::Approx(120.0f));
  CHECK(stats1.sigma == doctest::Approx(0.0f));

  //////////////////////////////////////////////////////////////////////////////////////////
  // Case 2: three points

  std::vector<sf::Vector2f> positions2{{20, 20}, {-20, -10}, {0, 0}};
  auto stats2 = ev::toroidalDistanceStatistics(positions2);

  // expected mean
  const float d1 = 50.0f;
  const float d2 = std::sqrt(800.0f);
  const float d3 = std::sqrt(500.0f);
  const float expectedMean = (d1 + d2 + d3) / 3.0f;
  CHECK(stats2.mean == doctest::Approx(expectedMean));

  // standard deviation
  const float var = ((d1 - expectedMean) * (d1 - expectedMean) +
                     (d2 - expectedMean) * (d2 - expectedMean) +
                     (d3 - expectedMean) * (d3 - expectedMean)) /
                    2.0f;  // N-1
  const float expectedSigma = std::sqrt(var);
  CHECK(stats2.sigma == doctest::Approx(expectedSigma));
}