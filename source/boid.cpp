#include "../include/boid.hpp"

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>

#include "../include/constants.hpp"
#include "../include/random.hpp"

//////////////////////////////////////////////////////////////////////////////////////////
// COSTRUTTORI

Boid::Boid() : position_{0., 0.}, velocity_{0., 0.} {}
Boid::Boid(const sf::Vector2f &position, const sf::Vector2f &velocity)
    : position_{position}, velocity_{velocity} {}

//////////////////////////////////////////////////////////////////////////////////////////
// GETTERS

sf::Vector2f Boid::getPosition() const { return position_; }
sf::Vector2f Boid::getVelocity() const { return velocity_; }
float Boid::getSpeed() const {
  return sqrtf(powf(velocity_.x, 2) + powf(velocity_.y, 2));
}

//////////////////////////////////////////////////////////////////////////////////////////
// SETTERS

void Boid::setPosition(const sf::Vector2f &position) {
  position_.x = position.x;
  position_.y = position.y;
}
void Boid::setVelocity(const sf::Vector2f &velocity) {
  velocity_.x = velocity.x;
  velocity_.y = velocity.y;
}
void Boid::setPositionX(float x) { position_.x = x; }
void Boid::setPositionY(float y) { position_.y = y; }
void Boid::setVelocityX(float v_x) { velocity_.x = v_x; }
void Boid::setVelocityY(float v_y) { velocity_.y = v_y; }

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS

//////////////////////////////////////////////////////////////////////////////////////////
// Distance function between 2D vectors

float distance(const sf::Vector2f &a, const sf::Vector2f &b) {
  float dx = b.x - a.x;
  float dy = b.y - a.y;
  return std::sqrt(dx * dx + dy * dy);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Distance function between 2D boids

float distance(const Boid &boid1, const Boid &boid2) {
  return sqrtf(powf((boid1.getPosition().x - boid2.getPosition().x), 2) +
               powf((boid1.getPosition().y - boid2.getPosition().y), 2));
}

//////////////////////////////////////////////////////////////////////////////////////////
// Distance function between 2D vectors

float distanceX(const Boid &boid1, const Boid &boid2) {
  return boid1.getPosition().x - boid2.getPosition().x;
}

//////////////////////////////////////////////////////////////////////////////////////////

float distanceY(const Boid &boid1, const Boid &boid2) {
  return boid1.getPosition().y - boid2.getPosition().y;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// CHECK SPEED

void checkMinimumSpeed(Boid &boid) {
  if (0 < boid.getSpeed() && boid.getSpeed() < constants::minBoidSpeed) {
    boid.setVelocity(
        {boid.getVelocity().x * constants::minBoidSpeed / boid.getSpeed(),
         boid.getVelocity().y * constants::minBoidSpeed / boid.getSpeed()});
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void checkMaximumSpeed(Boid &boid) {
  if (boid.getSpeed() > constants::maxBoidSpeed) {
    boid.setVelocity(
        {boid.getVelocity().x * constants::maxBoidSpeed / boid.getSpeed(),
         boid.getVelocity().y * constants::maxBoidSpeed / boid.getSpeed()});
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Boid::operator+=(const sf::Vector2f &velocity) { velocity_ += velocity; }

//////////////////////////////////////////////////////////////////////////////////////////
// CHECK BORDERS

void toroidalBorders(Boid &boid) {
  // this makes fmod output only positive numbers
  boid.setPositionX(
      std::fmod(std::fmod(boid.getPosition().x, constants::fieldSide) +
                    constants::fieldSide,
                constants::fieldSide));
  boid.setPositionY(
      std::fmod(std::fmod(boid.getPosition().y, constants::fieldSide) +
                    constants::fieldSide,
                constants::fieldSide));
}

//////////////////////////////////////////////////////////////////////////////////////////

void mirrorBorders(Boid &boid) {
  if (boid.getPosition().x < 0.f) {
    boid.setVelocityX(std::abs(boid.getVelocity().x) +
                      constants::speedBoostMirror);
    boid.setPositionX(0);
  } else if (boid.getPosition().x > constants::fieldSide) {
    boid.setVelocityX(-std::abs(boid.getVelocity().x) -
                      constants::speedBoostMirror);
    boid.setPositionX(constants::fieldSide);
  }

  if (boid.getPosition().y < 0.f) {
    boid.setVelocityY(std::abs(boid.getVelocity().y) +
                      constants::speedBoostMirror);
    boid.setPositionY(0);
  } else if (boid.getPosition().y > constants::fieldSide) {
    boid.setVelocityY(-std::abs(boid.getVelocity().y) -
                      constants::speedBoostMirror);
    boid.setPositionY(constants::fieldSide);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// BUILD

Boid createBoid(sf::Vector2f center, float a) {
  return {{randomBoidPosition(center)}, {randomBoidSpeed(a)}};
}
