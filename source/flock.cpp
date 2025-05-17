#include "flock.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <vector>

#include "boid.hpp"
#include "constants.hpp"
#include "random.hpp"
#include "structs.hpp"

namespace ev {

FlockPar Flock::parameters_ = constants::defaultFlockParameters;
bool Flock::toroidal_ = false;
bool Flock::repulsiveClick_ = false;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS

Flock::Flock(const std::vector<Boid> &flock)
    : boids_{flock}, color_{sf::Color::Black} {
  // Enforcing class invariant: a Flock must contain at least 2 boids.
  if (std::size(boids_) < 2) {
    throw std::invalid_argument("Flock must have at least 2 boids.");
  }
}

Flock::Flock(const std::vector<Boid> &flock, const sf::Color &color)
    : boids_{flock}, color_{color} {
  // Enforcing class invariant: a Flock must contain at least 2 boids.
  if (std::size(boids_) < 2) {
    throw std::invalid_argument("Flock must have at least 2 boids.");
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// GETTERS

Boid Flock::getBoid(size_t i) const {
  assert(boids_.size() > i);
  return boids_[i];
}
size_t Flock::getSize() const { return boids_.size(); }
sf::Color Flock::getFlockColor() const { return color_; }

////////////////////////////////////////////////////////////////////////////////////////////

float Flock::getMeanSpeed() const {
  assert((boids_.size() > 1));

  float meanSpeed{0};
  for (size_t j{0}; j < boids_.size(); j++) {
    meanSpeed += (boids_[j].getSpeed());
  }
  return meanSpeed / (static_cast<float>(boids_.size()));
}

////////////////////////////////////////////////////////////////////////////////////////

std::vector<sf::Vector2f> Flock::getFlockPositions() const {
  std::vector<sf::Vector2f> positions;
  assert((boids_.size() > 1));

  for (size_t i{0}; i < boids_.size(); i++) {
    positions.emplace_back(boids_[i].getPosition());
  }
  return positions;
}

//////////////////////////////////////////////////////////////////////////////////////////

std::vector<sf::Vector2f> Flock::getFlockVelocities() const {
  std::vector<sf::Vector2f> velocities;
  assert((boids_.size() > 1));

  for (size_t i{0}; i < boids_.size(); i++) {
    velocities.emplace_back(boids_[i].getVelocity());
  }
  return velocities;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Returns a vector with a speed for every boid of the flock

std::vector<float> Flock::getFlockSpeeds() const {
  std::vector<float> speeds;
  assert((boids_.size() > 1));

  for (size_t i{0}; i < boids_.size(); i++) {
    speeds.emplace_back(boids_[i].getSpeed());
  }
  return speeds;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// STATIC VARIABLES

FlockPar Flock::getParameters() { return parameters_; }
bool Flock::getToroidalMode() { return toroidal_; }
bool Flock::getRepulsiveClick() { return repulsiveClick_; }

//////////////////////////////////////////////////////////////////////////////////////////

void Flock::setParameters(const FlockPar &p) { parameters_ = p; }

void Flock::setSeparationStrength(float p) {
  parameters_.separationStrength = p;
}
void Flock::setSeparationRange(float p) { parameters_.separationRange = p; }
void Flock::setAlignmentStrength(float p) { parameters_.alignmentStrength = p; }
void Flock::setCohesionStrength(float p) { parameters_.cohesionStrength = p; }
void Flock::setInteractionRange(float p) { parameters_.interactionRange = p; }
void Flock::setRepelStrength(float p) { parameters_.repelStrength = p; }
void Flock::setRepelRange(float p) { parameters_.repelRange = p; }
void Flock::setClickStrength(float p) { parameters_.clickStrength = p; }

void Flock::setToroidalMode(bool p) { toroidal_ = p; }
void Flock::setRepulsiveClick(bool p) { repulsiveClick_ = p; }

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// RULES

//////////////////////////////////////////////////////////////////////////////////////////
// SEPARATION RULE

std::vector<sf::Vector2f> Flock::separation() const {
  std::vector<sf::Vector2f> separationSpeed{};
  assert((boids_.size() > 1));
  separationSpeed.reserve(boids_.size());

  for (size_t i{0}; i < boids_.size(); ++i) {
    separationSpeed.emplace_back();

    for (size_t j{0}; j < boids_.size(); ++j) {
      if (j == i) {
        continue;
      }
      if ((distance(boids_[j], boids_[i]) < parameters_.separationRange)) {
        separationSpeed[i] +=
            (boids_[j].getPosition() - boids_[i].getPosition()) *
            -parameters_.separationStrength;
      }
    }
  }
  return separationSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ALIGNMENT RULE

std::vector<sf::Vector2f> Flock::alignment() const {
  std::vector<sf::Vector2f> alignSpeed{};
  assert((boids_.size() > 1));
  alignSpeed.reserve(boids_.size());

  for (size_t i{0}; i < boids_.size(); ++i) {
    alignSpeed.emplace_back();
    int count{0};  // amount of boid[j] interacting with boid[i]

    for (size_t j{0}; j < boids_.size(); ++j) {
      if (j == i) {
        continue;
      }

      if (distance(boids_[i], boids_[j]) < parameters_.interactionRange) {
        alignSpeed[i] += ((boids_[j].getVelocity() - boids_[i].getVelocity()) *
                          (parameters_.alignmentStrength));
        count++;
      }
    }
    if (count) {
      alignSpeed[i] /= static_cast<float>(count);
    }
  }

  return alignSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////////
// COHESION RULE

std::vector<sf::Vector2f> Flock::cohesion() const {
  std::vector<sf::Vector2f> cohesionSpeed{};
  assert((boids_.size() > 1));
  cohesionSpeed.reserve(boids_.size());

  for (size_t i{0}; i < boids_.size(); i++) {
    cohesionSpeed.emplace_back();
    sf::Vector2f massCenter{0, 0};
    int count{0};  // number of boid[j] interacting with boid[i]

    for (size_t j{0}; j < boids_.size(); j++) {
      if (j == i) {
        continue;
      }
      if (distance(boids_[i], boids_[j]) < parameters_.interactionRange) {
        massCenter += (boids_[j].getPosition());
        count += 1;
      }
    }

    if (count) {
      cohesionSpeed[i] += ((massCenter / (static_cast<float>(count)) -
                            boids_[i].getPosition()) *
                           parameters_.cohesionStrength);
    }
  }

  return cohesionSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////////
// UPDATE

void Flock::updateFlock() {
  assert(boids_.size() > 1);

  const std::vector<sf::Vector2f> &separationSpeed{separation()};
  const std::vector<sf::Vector2f> &alignmentSpeed{alignment()};
  const std::vector<sf::Vector2f> &cohesionSpeed =
      toroidal_ ? toroidalCohesion() : cohesion();

  assert(boids_.size() == separationSpeed.size());
  assert(boids_.size() == alignmentSpeed.size());
  assert(boids_.size() == cohesionSpeed.size());

  for (size_t i{0}; i < boids_.size(); ++i) {
    boids_[i].setPosition(boids_[i].getPosition() +
                          boids_[i].getVelocity() / constants::speedScale);

    boids_[i] += (separationSpeed[i] + alignmentSpeed[i] + cohesionSpeed[i]);

    minimumSpeedControl(boids_[i]);
    maximumSpeedControl(boids_[i]);

    if (toroidal_) {
      toroidalBorders(boids_[i]);
    } else {
      mirrorBorders(boids_[i]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
// Update with repel between flocks

void Flock::updateFlock(const std::vector<sf::Vector2f> &repelSpeed) {
  assert(boids_.size() > 1);

  const std::vector<sf::Vector2f> &separationSpeed{separation()};
  const std::vector<sf::Vector2f> &alignmentSpeed{alignment()};
  const std::vector<sf::Vector2f> &cohesionSpeed =
      toroidal_ ? toroidalCohesion() : cohesion();

  assert(boids_.size() == separationSpeed.size());
  assert(boids_.size() == alignmentSpeed.size());
  assert(boids_.size() == cohesionSpeed.size());
  assert(boids_.size() == repelSpeed.size());

  for (size_t i{0}; i < boids_.size(); ++i) {
    boids_[i].setPosition(boids_[i].getPosition() +
                          boids_[i].getVelocity() / constants::speedScale);

    boids_[i] += (separationSpeed[i] + alignmentSpeed[i] + cohesionSpeed[i] +
                  repelSpeed[i]);

    minimumSpeedControl(boids_[i]);
    maximumSpeedControl(boids_[i]);

    if (toroidal_) {
      toroidalBorders(boids_[i]);
    } else {
      mirrorBorders(boids_[i]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
// REPEL ON CLICK

void Flock::repelOnClick(const sf::Vector2f &pos) {
  assert((boids_.size() > 1));

  for (size_t i{0}; i < boids_.size(); ++i) {
    if (distance(boids_[i].getPosition(), pos) < parameters_.interactionRange) {
      repulsiveClick_
          ? boids_[i] +=
            -((pos - boids_[i].getPosition()) * (parameters_.clickStrength))
          : boids_[i] +=
            ((pos - boids_[i].getPosition()) * (parameters_.clickStrength));
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// TOROIDAL RULES

std::vector<sf::Vector2f> Flock::toroidalCohesion() {
  std::vector<sf::Vector2f> cohesionSpeed{};
  assert((boids_.size() > 1));
  cohesionSpeed.reserve(boids_.size());

  for (size_t i{0}; i < boids_.size(); i++) {
    cohesionSpeed.emplace_back();
    sf::Vector2f massCenter{0, 0};
    int count{0};  // number of boid[j] interacting with boid[i]

    for (size_t j{0}; j < boids_.size(); j++) {
      if (j == i) {
        continue;
      }
      // TEMPORARY VARIABLE NEEDED for the LOGIC
      sf::Vector2f tempMassCenter{};

      // CHECK for TOROIDAL GEOMETRY
      if (deltaX(boids_[j], boids_[i]) > constants::fieldSide / 2) {
        tempMassCenter.x += (boids_[j].getPosition().x - constants::fieldSide);
      } else if (deltaX(boids_[j], boids_[i]) < -constants::fieldSide / 2) {
        tempMassCenter.x += (boids_[j].getPosition().x + constants::fieldSide);
      } else {
        tempMassCenter.x += (boids_[j].getPosition().x);
      }
      if (deltaY(boids_[j], boids_[i]) > constants::fieldSide / 2) {
        tempMassCenter.y += (boids_[j].getPosition().y - constants::fieldSide);
      } else if (deltaY(boids_[j], boids_[i]) < -constants::fieldSide / 2) {
        tempMassCenter.y += (boids_[j].getPosition().y + constants::fieldSide);
      } else {
        tempMassCenter.y += (boids_[j].getPosition().y);
      }

      if (distance(tempMassCenter, boids_[i].getPosition()) <
          parameters_.interactionRange) {
        count++;
        massCenter += tempMassCenter;
      }
    }

    if (count) {
      cohesionSpeed[i] +=
          ((massCenter / static_cast<float>(count) - boids_[i].getPosition()) *
           parameters_.cohesionStrength);
    }
  }
  return cohesionSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// REPEL between FLOCKS

std::vector<sf::Vector2f> repel(const std::vector<Flock> &flockstack,
                                size_t i) {
  std::vector<sf::Vector2f> repelSpeed;
  repelSpeed.reserve(flockstack[i].getSize());

  // for all the boids of the selected flock
  for (size_t j{0}; j < flockstack[i].getSize(); j++) {
    repelSpeed.emplace_back();
    // for all the other flocks
    for (size_t k{0}; k < flockstack.size(); k++) {
      if (i == k) {
        continue;
      }
      // iterate on all the elements of the flock
      for (size_t l{0}; l < flockstack[k].getSize(); l++) {
        // such that the distance is less than repel range
        if (distance(flockstack[i].getBoid(j), flockstack[k].getBoid(l)) <
            Flock::getParameters().repelRange) {
          repelSpeed[j] += ((flockstack[k].getBoid(l).getPosition() -
                             flockstack[i].getBoid(j).getPosition()) *
                            (-Flock::getParameters().repelStrength));
        }
      }
    }
  }

  return repelSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE FLOCK

Flock createFlock(size_t n, sf::Vector2f center, sf::Color color) {
  float a{ev::randomAngle()};

  std::vector<Boid> flock;
  for (size_t i{}; i < n; i++) {
    flock.emplace_back(createBoid(center, a));
  }

  assert(flock.size() >= constants::minFlockSize);

  return {flock, color};
}
}  // namespace ev