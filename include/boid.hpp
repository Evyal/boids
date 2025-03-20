#ifndef BOID_H
#define BOID_H

#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "constants.hpp"

namespace ev {

class Boid {
 private:
  sf::Vector2f position_{};
  sf::Vector2f velocity_{};

 public:
  //////////////////////////////////////////////////////////////////////////////////////////
  // CONSTRUCTORS

  Boid(const sf::Vector2f &position = constants::defaultBoidPosition,
       const sf::Vector2f &velocity = constants::defaultBoidVelocity);

  //////////////////////////////////////////////////////////////////////////////////////////
  // GETTERS

  sf::Vector2f getPosition() const;
  sf::Vector2f getVelocity() const;
  float getSpeed() const;

  //////////////////////////////////////////////////////////////////////////////////////////
  // SETTERS

  void setPosition(const sf::Vector2f &position);
  void setVelocity(const sf::Vector2f &velocity);
  void setPositionX(float x);
  void setPositionY(float y);
  void setVelocityX(float v_x);
  void setVelocityY(float v_y);

  //////////////////////////////////////////////////////////////////////////////////////////
  // OPERATORS

  void operator+=(const sf::Vector2f &velocity);
};

//////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS

float distanceX(const Boid &boid1, const Boid &boid2);
float distanceY(const Boid &boid1, const Boid &boid2);
float distance(const Boid &boid1, const Boid &boid2);
float distance(const sf::Vector2f &a, const sf::Vector2f &b);
float toroidalDistance(const sf::Vector2f &a, const sf::Vector2f &b);

//////////////////////////////////////////////////////////////////////////////////////////
// SPEED CONTROL

void checkMinimumSpeed(Boid &boid);
void checkMaximumSpeed(Boid &boid);

//////////////////////////////////////////////////////////////////////////////////////////
// CHECK BORDERS

void toroidalBorders(Boid &boid);
void mirrorBorders(Boid &boid);

//////////////////////////////////////////////////////////////////////////////////////////
// BUILD

Boid createBoid(sf::Vector2f center = {360, 360}, float angle = 0.f);

}  // namespace ev
#endif