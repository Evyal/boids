#include "boid.hpp"
#include "constants.hpp"
#include "random.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>

// COSTRUTTORI di DEFAULT

Boid::Boid(sf::Vector2f position, sf::Vector2f speed)
    : position_{position}, speed_{speed} {}
Boid::Boid() : position_{0., 0.}, speed_{0., 0.} {}

// GETTERS

sf::Vector2f Boid::getPosition() const { return position_; }
sf::Vector2f Boid::getVelocity() const { return speed_; }
float Boid::getPositionX() const { return position_.x; }
float Boid::getPositionY() const { return position_.y; }
float Boid::getVelocityX() const { return speed_.x; }
float Boid::getVelocityY() const { return speed_.y; }
float Boid::getSpeed() const {
  return sqrtf(powf(speed_.x, 2) + powf(speed_.y, 2));
}

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

// CHECK SPEED

void checkMinimumSpeed(Boid &boid) {
  if (boid.getSpeed() < constants::minBoidSpeed) {
    boid.setVelocity({boid.getVelocityX() * constants::minBoidSpeed / boid.getSpeed(),
                      boid.getVelocityY() * constants::minBoidSpeed / boid.getSpeed()});
  }
}
void checkMaximumSpeed(Boid &boid) {
  if (boid.getSpeed() > constants::maxBoidSpeed) {
    boid.setVelocity({boid.getVelocityX() * constants::maxBoidSpeed / boid.getSpeed(),
                      boid.getVelocityY() * constants::maxBoidSpeed / boid.getSpeed()});
  }
}
void Boid::operator+=(const sf::Vector2f &speed) { speed_ += speed; }

// FUNCTIONS

float distance(const Boid &boid1, const Boid &boid2) {
  return sqrtf(powf((boid1.getPositionX() - boid2.getPositionX()), 2) +
               powf((boid1.getPositionY() - boid2.getPositionY()), 2));
}
float deltaX(const Boid &boid1, const Boid &boid2) {
  return boid1.getPositionX() - boid2.getPositionX();
}
float deltaY(const Boid &boid1, const Boid &boid2) {
  return boid1.getPositionY() - boid2.getPositionY();
}

// BORDERS

void toroidalBorders(Boid &boid) {
  if (boid.getPositionX() > constants::fieldSide + constants::marginSize) {
    boid.setPositionX(boid.getPositionX() - constants::fieldSide);
  } else if (boid.getPositionX() < constants::marginSize) {
    boid.setPositionX(boid.getPositionX() + constants::fieldSide);
  }

  if (boid.getPositionY() > constants::fieldSide + constants::marginSize) {
    boid.setPositionY(boid.getPositionY() - constants::fieldSide);
  } else if (boid.getPositionY() < constants::marginSize) {
    boid.setPositionY(boid.getPositionY() + constants::fieldSide);
  }
}

void mirrorBorders(Boid &boid) {
  if (boid.getPositionX() < constants::marginSize) {
    boid.setVelocityX(std::abs(boid.getVelocityX()) + 15.f);
  } else if (boid.getPositionX() >
             constants::fieldSide + constants::marginSize) {
    boid.setVelocityX(-std::abs(boid.getVelocityX()) - 15.f);
  }
  if (boid.getPositionY() < constants::marginSize) {
    boid.setVelocityY(std::abs(boid.getVelocityY()) + 15.f);
  } else if (boid.getPositionY() >
             constants::fieldSide + constants::marginSize) {
    boid.setVelocityY(-std::abs(boid.getVelocityY()) - 15.f);
  }
}

// BUILD

Boid buildBoid(float a) { return {{randomPosition()}, {randomSpeed(a)}}; }
Boid buildBoid(sf::Vector2f center, float a) {
  return {{randomPosition(center)}, {randomSpeed(a)}};
}
