#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <vector>

#include "structs.hpp"

namespace ev {

StatsPar distanceStatistics(const std::vector<sf::Vector2f> &positions);
StatsPar toroidalDistanceStatistics(const std::vector<sf::Vector2f> &positions);

StatsPar speedStatistics(const std::vector<float> &speeds);

}  // namespace ev

#endif