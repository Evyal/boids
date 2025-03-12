#ifndef FLOCK_H
#define FLOCK_H

#include "boid.hpp"
#include "structs.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <vector>

class Flock {

private:
  std::vector<Boid> flock_;
  sf::Color color_;
  static FlockPar parameters_;
  static bool toroidal_;
  static bool repulsiveClick_;

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
  static bool getToroidalMode();
  static bool getRepulsiveClick();

  //////////////////////////////////////////////////////////////////////////////////////////

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
  std::vector<sf::Vector2f> Separation() const;
  std::vector<sf::Vector2f> Alignment() const;
  std::vector<sf::Vector2f> Cohesion() const;
  void RepelOnClick(const sf::Vector2f &pos);

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