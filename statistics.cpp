#include "statistics.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <numeric>
#include <execution>
#include <vector>

// Function to calculate Euclidean distance between two points
float calculateDistance(const sf::Vector2f &p1, const sf::Vector2f &p2) {
  sf::Vector2f diff = p1 - p2;
  return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

// Function to calculate all pairwise distances
std::vector<float> calculateDistances(const std::vector<sf::Vector2f> &points) {
  std::vector<float> distances;
  size_t n = points.size();
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      distances.push_back(calculateDistance(points[i], points[j]));
    }
  }
  return distances;
}

// Function to calculate the mean of distances
float calculateMean(const std::vector<float> &distances) {
  if (distances.empty()) {
    return 0.0; // No distances, return 0
  }
  float totalDistance =
      std::accumulate(distances.begin(), distances.end(), 0.0f);
  return totalDistance / static_cast<float>(distances.size());
}

// Function to calculate the standard deviation of distances
float calculateStandardDeviation(const std::vector<float> &distances,
                                 float mean) {
  if (distances.empty()) {
    return 0.0; // No distances, return 0
  }
  float variance =
      std::reduce(std::execution::par, distances.begin(), distances.end(), 0.0f,
                      [mean](float acc, float distance) {
                        return acc + (distance - mean) * (distance - mean);
                      }) /
      static_cast<float>(distances.size());
  return std::sqrt(variance);
}
  