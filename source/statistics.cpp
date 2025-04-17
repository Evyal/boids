#include "../include/statistics.hpp"

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <vector>

#include "../include/boid.hpp"
#include "../include/structs.hpp"

namespace ev {

//////////////////////////////////////////////////////////////////////////////////////////

StatsPar distanceStatistics(const std::vector<sf::Vector2f>& positions) {
  const size_t N = positions.size();
  const size_t count = N * (N - 1) / 2;

  if (count == 0) return StatsPar{0.f, 0.f};
  if (count == 1) return StatsPar{distance(positions[0], positions[1]), 0.f};

  float sum = 0.f;
  float sumSquared = 0.f;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = i + 1; j < N; ++j) {
      float d = distance(positions[i], positions[j]);
      sum += d;
      sumSquared += d * d;
    }
  }

  const float countF = static_cast<float>(count);
  const float mean = sum / countF;
  const float stdDev =
      sqrtf((sumSquared - countF * mean * mean) / (countF - 1.f));
  return StatsPar{mean, stdDev};
}

////////////////////////////////////////////////////////////////////////////////

StatsPar toroidalDistanceStatistics(
    const std::vector<sf::Vector2f>& positions) {
  const size_t N = positions.size();
  const size_t count = N * (N - 1) / 2;

  if (count == 0) return StatsPar{0.f, 0.f};
  if (count == 1)
    return StatsPar{toroidalDistance(positions[0], positions[1]), 0.f};

  float sum = 0.f;
  float sumSquared = 0.f;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = i + 1; j < N; ++j) {
      float d = toroidalDistance(positions[i], positions[j]);
      sum += d;
      sumSquared += d * d;
    }
  }

  const float countF = static_cast<float>(count);
  const float mean = sum / countF;
  const float stdDev =
      sqrtf((sumSquared - countF * mean * mean) / (countF - 1.f));
  return StatsPar{mean, stdDev};
}

////////////////////////////////////////////////////////////////////////////////

StatsPar speedStatistics(const std::vector<float>& speeds) {
  const size_t N = speeds.size();
  if (N == 0) return StatsPar{0.f, 0.f};
  if (N == 1) return StatsPar{speeds[0], 0.f};

  float sum = 0.f;
  float sumSquared = 0.f;
  for (float v : speeds) {
    sum += v;
    sumSquared += v * v;
  }

  const float countF = static_cast<float>(N);
  const float mean = sum / countF;
  const float stdDev =
      sqrtf((sumSquared - countF * mean * mean) / (countF - 1.f));
  return StatsPar{mean, stdDev};
}

}  // namespace ev