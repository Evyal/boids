#ifndef BOID_H
#define BOID_H

#include <SFML/System/Vector2.hpp>
#include <cmath>

class Boid {
 private:
  sf::Vector2f position_{};
  sf::Vector2f velocity_{};

 public:
  //////////////////////////////////////////////////////////////////////////////////////////
  // COSTRUTTORI

  Boid();
  Boid(const sf::Vector2f &position, const sf::Vector2f &velocity);

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

float distance(const sf::Vector2f &a, const sf::Vector2f &b);
float distance(const Boid &boid1, const Boid &boid2);
float distanceX(const Boid &boid1, const Boid &boid2);
float distanceY(const Boid &boid1, const Boid &boid2);

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

Boid createBoid(sf::Vector2f center, float angle);

#endif