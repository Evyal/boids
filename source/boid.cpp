#include "boid.hpp"

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>
#include <random>

#include "constants.hpp"
#include "random.hpp"

namespace ev {

//////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS related to BOIDS

//////////////////////////////////////////////////////////////////////////////////////////

float deltaX(const Boid &boid1, const Boid &boid2) {
  return boid1.position.x - boid2.position.x;
}

//////////////////////////////////////////////////////////////////////////////////////////

float deltaY(const Boid &boid1, const Boid &boid2) {
  return boid1.position.y - boid2.position.y;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Distance function between 2D boids

float distance(const Boid &boid1, const Boid &boid2) {
  float dx = deltaX(boid1, boid2);
  float dy = deltaY(boid1, boid2);
  return std::sqrt(dx * dx + dy * dy);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Distance function between 2D vectors

float distance(const sf::Vector2f &a, const sf::Vector2f &b) {
  float dx = b.x - a.x;
  float dy = b.y - a.y;
  return std::sqrt(dx * dx + dy * dy);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Distance function between 2D vectors

float toroidalDistance(const sf::Vector2f &a, const sf::Vector2f &b) {
  float dx = std::abs(a.x - b.x);
  float dy = std::abs(a.y - b.y);
  float t = constants::fieldSide / 2.f;
  if (dx > t) {
    dx = constants::fieldSide - dx;
  }
  if (dy > t) {
    dy = constants::fieldSide - dy;
  }
  return std::sqrt(dx * dx + dy * dy);
}

//////////////////////////////////////////////////////////////////////////////////////////
// SPEED CONTROL

float getSpeed(const Boid &boid) {
  float vx = boid.velocity.x;
  float vy = boid.velocity.y;
  return std::sqrt(vx * vx + vy * vy);
}

void minimumSpeedControl(Boid &boid) {
  float speed = getSpeed(boid);
  if (speed > 0 && speed < constants::minBoidSpeed) {
    boid.velocity *= (constants::minBoidSpeed / speed);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void maximumSpeedControl(Boid &boid) {
  float speed = getSpeed(boid);
  if (speed > constants::maxBoidSpeed) {
    boid.velocity *= (constants::maxBoidSpeed / speed);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
// CHECK BORDERS

void toroidalBorders(Boid &boid) {
  // this use of fmod makes it output only positive numbers
  boid.position.x = (std::fmod(
      std::fmod(boid.position.x, constants::fieldSide) + constants::fieldSide,
      constants::fieldSide));
  boid.position.y = (std::fmod(
      std::fmod(boid.position.y, constants::fieldSide) + constants::fieldSide,
      constants::fieldSide));
}

//////////////////////////////////////////////////////////////////////////////////////////

void mirrorBorders(Boid &boid) {
  if (boid.position.x < 0.f) {
    boid.velocity.x = (std::abs(boid.velocity.x) + constants::speedBoostMirror);
    boid.position.x = 0;
  } else if (boid.position.x > constants::fieldSide) {
    boid.velocity.x = -std::abs(boid.velocity.x) - constants::speedBoostMirror;
    boid.position.x = constants::fieldSide;
  }

  if (boid.position.y < 0.f) {
    boid.velocity.y = (std::abs(boid.velocity.y) + constants::speedBoostMirror);
    boid.position.y = 0;
  } else if (boid.position.y > constants::fieldSide) {
    boid.velocity.y = -std::abs(boid.velocity.y) - constants::speedBoostMirror;
    boid.position.y = constants::fieldSide;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE RANDOM BOIDS

Boid randomBoid(std::mt19937 &engine, const sf::Vector2f &center, float a) {
  return {{randomBoidPosition(center, engine)}, {randomBoidVelocity(a, engine)}};
}

}  // namespace ev