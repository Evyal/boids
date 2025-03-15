#include "statistics.hpp"
#include "boid.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <numeric>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////

std::vector<float>
calculateDistances(const std::vector<sf::Vector2f> &positions) {
  std::vector<float> distances;

  // iterate over all the possible pairs
  for (size_t i{0}; i < positions.size(); ++i) {
    for (size_t j{i + 1}; j < positions.size(); ++j) {
      distances.push_back(distance(positions[i], positions[j]));
    }
  }
  return distances;
}

//////////////////////////////////////////////////////////////////////////////////////////

float calculateMean(const std::vector<float> &distances) {
  if (distances.empty()) {
    return 0.0;
  }

  float totalDistance =
      std::accumulate(distances.begin(), distances.end(), 0.0f);
  return totalDistance / static_cast<float>(distances.size());
}

//////////////////////////////////////////////////////////////////////////////////////////

float calculateStandardDeviation(const std::vector<float> &distances,
                                 float mean) {
  if (distances.size() < 2) {
    return 0.0;
  }

  float variance = std::accumulate(distances.begin(), distances.end(), 0.0f,
                                   [mean](float acc, float distance) {
                                     return acc + powf(distance - mean, 2.f);
                                   }) /
                   static_cast<float>(distances.size() - 1);
  return std::sqrt(variance);
}
