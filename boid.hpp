#ifndef BOID_H
#define BOID_H

#include <SFML/System/Vector2.hpp>
#include <cmath>

class Boid {
private:
  sf::Vector2f position_{};
  sf::Vector2f speed_{};

public:
  // COSTRUTTORI di DEFAULT

  Boid(sf::Vector2f position, sf::Vector2f speed);
  Boid();

  // GETTERS

  sf::Vector2f getPosition() const;
  sf::Vector2f getVelocity() const;
  float getPositionX() const;
  float getPositionY() const;
  float getVelocityX() const;
  float getVelocityY() const;
  float getSpeed() const;

  // SETTERS

  void setPosition(sf::Vector2f position);
  void setVelocity(sf::Vector2f speed);
  void setPositionX(float x);
  void setPositionY(float y);
  void setVelocityX(float v_x);
  void setVelocityY(float v_y);

  void operator+=(const sf::Vector2f &speed);
};

// FUNCTIONS

float distance(const Boid &boid1, const Boid &boid2);
float deltaX(const Boid &boid1, const Boid &boid2);
float deltaY(const Boid &boid1, const Boid &boid2);

// SPEED CONTROL

void checkMinimumSpeed(Boid &boid);
void checkMaximumSpeed(Boid &boid);

// CHECK BORDERS
void toroidalBorders(Boid &boid);
void mirrorBorders(Boid &boid);

// BUILD

Boid buildBoid(float a);
Boid buildBoid(sf::Vector2f center, float a);

#endif