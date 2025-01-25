#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "flock.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <vector>

float calculateDistance(const sf::Vector2f &p1, const sf::Vector2f &p2);
std::vector<float> calculateDistances(const std::vector<sf::Vector2f> &points);
float calculateMean(const std::vector<float> &distances);
float calculateStandardDeviation(const std::vector<float> &distances,
                                 float mean);

#endif