#ifndef FLOCK_H
#define FLOCK_H

#include "boid.hpp"
#include "structs.hpp"
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
  static FlockPar parameters_;

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
  float getMeanSpeed() const;

  std::vector<sf::Vector2f> getFlockPositions() const;
  std::vector<sf::Vector2f> getFlockVelocities() const;
  std::vector<float> getSpeedVector() const;

  static FlockPar getParameters();

  //////////////////////////////////////////////////////////////////////////////////////////

  static void setParameters(const FlockPar &par);

  static void setSeparationStrength(float value);
  static void setSeparationRange(float value);
  static void setAlignmentStrength(float value);
  static void setCohesionStrength(float value);
  static void setInteractionRange(float value);
  static void setRepelStrength(float value);
  static void setRepelRange(float value);

  //////////////////////////////////////////////////////////////////////////////////////////
  // RULES
  std::vector<sf::Vector2f> Separation() const;
  std::vector<sf::Vector2f> Alignment() const;
  std::vector<sf::Vector2f> Cohesion() const;

  // UPDATE
  void updateFlock(const std::vector<sf::Vector2f> &repelSpeed);

  //////////////////////////////////////////////////////////////////////////////////////////
  // TOROIDAL MODE
  std::vector<sf::Vector2f> toroidalCohesion();
};

//////////////////////////////////////////////////////////////////////////////////////////
// REPEL
std::vector<sf::Vector2f> Repel(const std::vector<Flock> &flockstack, size_t i);

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE FLOCKS
Flock createFlock(size_t n, sf::Vector2f center, sf::Color color);

#endif