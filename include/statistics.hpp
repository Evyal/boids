#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <vector>

namespace ev {

std::vector<float> calculateDistances(
    const std::vector<sf::Vector2f> &positions);

float calculateMean(const std::vector<float> &distances);
float calculateStandardDeviation(const std::vector<float> &distances,
                                 float mean);

}  // namespace ev

#endif