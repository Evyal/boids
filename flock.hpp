#ifndef FLOCK_H
#define FLOCK_H

#include "boid.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <vector>

class Flock {

private:
  std::vector<Boid> flock_;
  sf::Color color_;

public:
  //////////////////////////////////////////////////////////////////////////////////////////
  // COSTRUTTORI
  Flock(const std::vector<Boid> &flock, const sf::Color &color);
  Flock(const std::vector<Boid> &flock);
  Flock();

  //////////////////////////////////////////////////////////////////////////////////////////
  // GETTERS
  Boid getBoid(size_t i) const;
  std::vector<Boid> getBoids() const;
  size_t getSize() const;
  sf::Color getFlockColor() const;

  sf::Vector2f getMassCenter() const;
  sf::Vector2f getMeanVelocity() const;
  float getMeanSpeed() const;

  std::vector<sf::Vector2f> getFlockPositions() const;
  std::vector<sf::Vector2f> getFlockVelocities() const;
  std::vector<float> getSpeedVector() const;

  //////////////////////////////////////////////////////////////////////////////////////////
  // RULES
  // SEPARATION
  std::vector<sf::Vector2f> Separation(float separation,
                                       float separationRange) const;
  // ALIGNMENT
  std::vector<sf::Vector2f> Alignment(float alignment, float interaction) const;
  // COESION
  std::vector<sf::Vector2f> Cohesion(float cohesion, float interaction) const;

  //////////////////////////////////////////////////////////////////////////////////////////
  // UPDATE
  void updateFlock(const std::vector<sf::Vector2f> &separationSpeed,
                   const std::vector<sf::Vector2f> &alignmentSpeed,
                   const std::vector<sf::Vector2f> &coesionSpeed,
                   const std::vector<sf::Vector2f> &repelSpeed);
};

//////////////////////////////////////////////////////////////////////////////////////////
// REPEL
std::vector<sf::Vector2f> Repel(const std::vector<Flock> &flockstack, size_t i,
                                float repel, float repelRange);

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE FLOCKS
Flock createFlock(size_t n, sf::Vector2f center, sf::Color color);

#endif