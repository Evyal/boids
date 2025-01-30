#include "boid.hpp"
#include "constants.hpp"
#include "random.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// COSTRUTTORI di DEFAULT

Boid::Boid(sf::Vector2f position, sf::Vector2f speed)
    : position_{position}, speed_{speed} {}
Boid::Boid() : position_{0., 0.}, speed_{0., 0.} {}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// GETTERS

sf::Vector2f Boid::getPosition() const { return position_; }
sf::Vector2f Boid::getVelocity() const { return speed_; }
float Boid::getSpeed() const {
  return sqrtf(powf(speed_.x, 2) + powf(speed_.y, 2));
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// SETTERS

void Boid::setPosition(sf::Vector2f position) {
  position_.x = position.x;
  position_.y = position.y;
}
void Boid::setVelocity(sf::Vector2f speed) {
  speed_.x = speed.x;
  speed_.y = speed.y;
}
void Boid::setPositionX(float x) { position_.x = x; }
void Boid::setPositionY(float y) { position_.y = y; }
void Boid::setVelocityX(float v_x) { speed_.x = v_x; }
void Boid::setVelocityY(float v_y) { speed_.y = v_y; }

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS

float distance(const Boid &boid1, const Boid &boid2) {
  return sqrtf(powf((boid1.getPosition().x - boid2.getPosition().x), 2) +
               powf((boid1.getPosition().y - boid2.getPosition().y), 2));
}

//////////////////////////////////////////////////////////////////////////////////////////

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
void Boid::operator+=(const sf::Vector2f &speed) { speed_ += speed; }

//////////////////////////////////////////////////////////////////////////////////////////
// CHECK BORDERS

void toroidalBorders(Boid &boid) {
  if (boid.getPosition().x > constants::fieldSide + constants::marginSize) {
    boid.setPositionX(boid.getPosition().x - constants::fieldSide);
  } else if (boid.getPosition().x < constants::marginSize) {
    boid.setPositionX(boid.getPosition().x + constants::fieldSide);
  }

  if (boid.getPosition().y > constants::fieldSide + constants::marginSize) {
    boid.setPositionY(boid.getPosition().y - constants::fieldSide);
  } else if (boid.getPosition().y < constants::marginSize) {
    boid.setPositionY(boid.getPosition().y + constants::fieldSide);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void mirrorBorders(Boid &boid) {
  if (boid.getPosition().x < constants::marginSize) {
    boid.setVelocityX(std::abs(boid.getVelocity().x) + constants::speedBoostMirror);
  } else if (boid.getPosition().x >
             constants::fieldSide + constants::marginSize) {
    boid.setVelocityX(-std::abs(boid.getVelocity().x) - constants::speedBoostMirror);
  }
  if (boid.getPosition().y < constants::marginSize) {
    boid.setVelocityY(std::abs(boid.getVelocity().y) + constants::speedBoostMirror);
  } else if (boid.getPosition().y >
             constants::fieldSide + constants::marginSize) {
    boid.setVelocityY(-std::abs(boid.getVelocity().y) - constants::speedBoostMirror);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// BUILD

Boid buildBoid(sf::Vector2f center, float a) {
  return {{randomPosition(center)}, {randomSpeed(a)}};
}
