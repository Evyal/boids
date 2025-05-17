#ifndef FLOCK_H
#define FLOCK_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <vector>

#include "boid.hpp"
#include "structs.hpp"

namespace ev {
class Flock {
 private:
  std::vector<Boid> boids_{};
  sf::Color color_{sf::Color::Black};

  //////////////////////////////////////////////////////////////////////////////////////////
  // STATIC VARIABLES

  static FlockPar parameters_;
  static bool toroidal_;
  static bool repulsiveClick_;

 public:
  //////////////////////////////////////////////////////////////////////////////////////////
  // CONSTRUCTORS

  Flock() = delete;
  Flock(const std::vector<Boid> &boids);
  Flock(const std::vector<Boid> &boids, const sf::Color &color);

  //////////////////////////////////////////////////////////////////////////////////////////
  // GETTERS

  Boid getBoid(size_t i) const;
  size_t getSize() const;
  sf::Color getFlockColor() const;
  float getMeanSpeed() const;

  std::vector<sf::Vector2f> getFlockPositions() const;
  std::vector<sf::Vector2f> getFlockVelocities() const;
  std::vector<float> getFlockSpeeds() const;

  //////////////////////////////////////////////////////////////////////////////////////////
  // GETTERS for STATIC VARIABLES

  static FlockPar getParameters();
  static bool getToroidalMode();
  static bool getRepulsiveClick();

  //////////////////////////////////////////////////////////////////////////////////////////
  // SETTERS for STATIC VARIABLES

  static void setParameters(const FlockPar &par);

  static void setSeparationStrength(float p);
  static void setSeparationRange(float p);
  static void setAlignmentStrength(float p);
  static void setCohesionStrength(float p);
  static void setInteractionRange(float p);
  static void setRepelStrength(float p);
  static void setRepelRange(float p);
  static void setClickStrength(float p);

  static void setToroidalMode(bool p);
  static void setRepulsiveClick(bool p);

  //////////////////////////////////////////////////////////////////////////////////////////
  // RULES

  std::vector<sf::Vector2f> separation() const;
  std::vector<sf::Vector2f> alignment() const;
  std::vector<sf::Vector2f> cohesion() const;

  // UPDATE

  void updateFlock();
  void updateFlock(const std::vector<sf::Vector2f> &repelSpeed);
  void repelOnClick(const sf::Vector2f &pos);

  //////////////////////////////////////////////////////////////////////////////////////////
  // TOROIDAL MODE

  std::vector<sf::Vector2f> toroidalCohesion();
};

//////////////////////////////////////////////////////////////////////////////////////////
// REPEL between different flocks

std::vector<sf::Vector2f> repel(const std::vector<Flock> &flockstack, size_t i);

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE FLOCKS

Flock createFlock(size_t n, sf::Vector2f center, sf::Color color);

}  // namespace ev

#endif