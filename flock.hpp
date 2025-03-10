#ifndef FLOCK_H
#define FLOCK_H

#include "boid.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <vector>

extern bool toroidal;
class Flock {

private:
  std::vector<Boid> flock_;
  sf::Color color_;

public:
  //////////////////////////////////////////////////////////////////////////////////////////
  // COSTRUTTORI
  Flock();
  Flock(const std::vector<Boid> &flock);
  Flock(const std::vector<Boid> &flock, const sf::Color &color);

  //////////////////////////////////////////////////////////////////////////////////////////
  // GETTERS
  Boid getBoid(size_t i) const;
  size_t getSize() const;
  sf::Color getFlockColor() const;

  // sf::Vector2f getMeanPosition() const;
  // sf::Vector2f getMeanVelocity() const;
  float getMeanSpeed() const;

  std::vector<sf::Vector2f> getFlockPositions() const;
  std::vector<sf::Vector2f> getFlockVelocities() const;
  std::vector<float> getSpeedVector() const;

  //////////////////////////////////////////////////////////////////////////////////////////
  // RULES
  std::vector<sf::Vector2f> Separation(float separation,
                                       float separationRange) const;
  std::vector<sf::Vector2f> Alignment(float alignment, float interaction) const;
  std::vector<sf::Vector2f> Cohesion(float cohesion, float interaction) const;

  //////////////////////////////////////////////////////////////////////////////////////////
  // UPDATE
  void updateFlock(const std::vector<sf::Vector2f> &separationSpeed,
                   const std::vector<sf::Vector2f> &alignmentSpeed,
                   const std::vector<sf::Vector2f> &coesionSpeed,
                   const std::vector<sf::Vector2f> &repelSpeed);

  //////////////////////////////////////////////////////////////////////////////////////////
  // TOROIDAL MODE

  std::vector<sf::Vector2f> toroidalCohesion(float cohesion, float interaction);
  void toroidalUpdate(const std::vector<sf::Vector2f> &separationSpeed,
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