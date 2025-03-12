#include "flock.hpp"
#include "boid.hpp"
#include "constants.hpp"
#include "structs.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <random>
#include <vector>

extern std::default_random_engine rng;

FlockPar Flock::parameters_ = constants::defaultFlockParameters;
bool Flock::toroidal_ = false;
bool Flock::repulsiveClick_ = false;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// COSTRUTTORI

Flock::Flock() : flock_{}, color_{sf::Color::Black} {}

Flock::Flock(const std::vector<Boid> &flock)
    : flock_{flock}, color_{sf::Color::Black} {}

Flock::Flock(const std::vector<Boid> &flock, const sf::Color &color)
    : flock_{flock}, color_{color} {}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// GETTERS

Boid Flock::getBoid(size_t i) const {
  assert(flock_.size() > i);
  return flock_[i];
}
size_t Flock::getSize() const { return flock_.size(); }
sf::Color Flock::getFlockColor() const { return color_; }

////////////////////////////////////////////////////////////////////////////////////////////

float Flock::getMeanSpeed() const {
  assert((flock_.size() > 1));

  float meanSpeed{0};
  for (size_t j{0}; j < flock_.size(); j++) {
    meanSpeed += (flock_[j].getSpeed());
  }
  return meanSpeed / (static_cast<float>(flock_.size()));
}

////////////////////////////////////////////////////////////////////////////////////////

std::vector<sf::Vector2f> Flock::getFlockPositions() const {
  std::vector<sf::Vector2f> positions;
  assert((flock_.size() > 1));

  for (size_t i{0}; i < flock_.size(); i++) {
    positions.emplace_back(flock_[i].getPosition());
  }
  return positions;
}

//////////////////////////////////////////////////////////////////////////////////////////

std::vector<sf::Vector2f> Flock::getFlockVelocities() const {
  std::vector<sf::Vector2f> velocities;
  assert((flock_.size() > 1));

  for (size_t i{0}; i < flock_.size(); i++) {
    velocities.emplace_back(flock_[i].getVelocity());
  }
  return velocities;
}

//////////////////////////////////////////////////////////////////////////////////////////

std::vector<float> Flock::getSpeedVector() const {
  std::vector<float> speeds;
  assert((flock_.size() > 1));

  for (size_t i{0}; i < flock_.size(); i++) {
    speeds.emplace_back(flock_[i].getSpeed());
  }
  return speeds;
}

//////////////////////////////////////////////////////////////////////////////////////////

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

std::vector<sf::Vector2f> Flock::Separation() const {
  std::vector<sf::Vector2f> separationSpeed{};
  assert((flock_.size() > 1));
  separationSpeed.clear();

  for (size_t i{0}; i < flock_.size(); ++i) {
    separationSpeed.emplace_back();

    for (size_t j{0}; j < flock_.size(); ++j) {
      if (j != i &&
          (distance(flock_[j], flock_[i]) < parameters_.separationRange)) {
        if ((flock_[j].getPosition().x - flock_[i].getPosition().x) != 0) {
          separationSpeed[i].x +=
              (1 * (flock_[j].getPosition().x - flock_[i].getPosition().x) *
               (-parameters_.separationStrength));
        }
        if ((flock_[j].getPosition().y - flock_[i].getPosition().y) != 0) {
          separationSpeed[i].y +=
              (1 * (flock_[j].getPosition().y - flock_[i].getPosition().y) *
               (-parameters_.separationStrength));
        }
      }
    }
  }
  return separationSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ALIGNMENT RULE

std::vector<sf::Vector2f> Flock::Alignment() const {
  std::vector<sf::Vector2f> alignSpeed{};
  assert((flock_.size() > 1));
  alignSpeed.clear();

  for (size_t i{0}; i < flock_.size(); ++i) {
    alignSpeed.emplace_back();
    int count{0};

    for (size_t j{0}; j < flock_.size(); ++j) {
      if (j != i &&
          distance(flock_[i], flock_[j]) < parameters_.interactionRange) {
        alignSpeed[i] += ((flock_[j].getVelocity() - flock_[i].getVelocity()) *
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

std::vector<sf::Vector2f> Flock::Cohesion() const {

  std::vector<sf::Vector2f> cohesionSpeed{};
  assert((flock_.size() > 1));
  cohesionSpeed.clear();

  for (size_t i{0}; i < flock_.size(); i++) {
    cohesionSpeed.emplace_back();
    sf::Vector2f massCenter{0, 0};
    int count{0};

    for (size_t j{0}; j < flock_.size(); j++) {
      if (j != i &&
          distance(flock_[i], flock_[j]) < parameters_.interactionRange) {
        massCenter += (flock_[j].getPosition());
        count += 1;
      }
    }

    if (count) {
      cohesionSpeed[i] += ((massCenter / (static_cast<float>(count)) -
                            flock_[i].getPosition()) *
                           parameters_.cohesionStrength);
    }
  }

  return cohesionSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////////
// UPDATE

void Flock::updateFlock(const std::vector<sf::Vector2f> &repelSpeed) {

  assert(flock_.size() > 1);

  const std::vector<sf::Vector2f> &separationSpeed{Separation()};
  const std::vector<sf::Vector2f> &alignmentSpeed{Alignment()};
  const std::vector<sf::Vector2f> &cohesionSpeed =
      toroidal_ ? toroidalCohesion() : Cohesion();

  assert(flock_.size() == separationSpeed.size());
  assert(flock_.size() == alignmentSpeed.size());
  assert(flock_.size() == cohesionSpeed.size());
  assert(flock_.size() == repelSpeed.size());

  for (size_t i{0}; i < flock_.size(); ++i) {
    flock_[i].setPosition(flock_[i].getPosition() +
                          flock_[i].getVelocity() / constants::speedScale);

    flock_[i] += (separationSpeed[i] + alignmentSpeed[i] + cohesionSpeed[i] +
                  repelSpeed[i]);

    checkMinimumSpeed(flock_[i]);
    checkMaximumSpeed(flock_[i]);

    if (toroidal_) {
      toroidalBorders(flock_[i]);
    } else {
      mirrorBorders(flock_[i]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// TOROIDAL RULES

std::vector<sf::Vector2f> Flock::toroidalCohesion() {
  std::vector<sf::Vector2f> cohesionSpeed{};
  assert((flock_.size() > 1));
  cohesionSpeed.clear();

  for (size_t i{0}; i < flock_.size(); i++) {
    cohesionSpeed.emplace_back();
    sf::Vector2f massCenter{0, 0};
    int count{};

    for (size_t j{0}; j < flock_.size(); j++) {
      if (j == i) {
        continue;
      }
      // TEMPORARY VARIABLE NEEDED for the LOGIC
      sf::Vector2f tempMassCenter{};

      if (distanceX(flock_[j], flock_[i]) > constants::fieldSide / 2) {
        tempMassCenter.x += (flock_[j].getPosition().x - constants::fieldSide);
      } else if (distanceX(flock_[j], flock_[i]) < -constants::fieldSide / 2) {
        tempMassCenter.x += (flock_[j].getPosition().x + constants::fieldSide);
      } else {
        tempMassCenter.x += (flock_[j].getPosition().x);
      }
      if (distanceY(flock_[j], flock_[i]) > constants::fieldSide / 2) {
        tempMassCenter.y += (flock_[j].getPosition().y - constants::fieldSide);
      } else if (distanceY(flock_[j], flock_[i]) < -constants::fieldSide / 2) {
        tempMassCenter.y += (flock_[j].getPosition().y + constants::fieldSide);
      } else {
        tempMassCenter.y += (flock_[j].getPosition().y);
      }

      if (distance(tempMassCenter, flock_[i].getPosition()) <
          parameters_.interactionRange) {
        count++;
        massCenter += {tempMassCenter.x, tempMassCenter.y};
      }
    }

    if (count) {
      cohesionSpeed[i] +=
          ((massCenter / static_cast<float>(count) - flock_[i].getPosition()) *
           parameters_.cohesionStrength);
    }
  }
  return cohesionSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////////
// REPEL ON CLICK

void Flock::RepelOnClick(const sf::Vector2f &pos) {
  assert((flock_.size() > 1));

  for (size_t i{0}; i < flock_.size(); ++i) {
    if (distance(flock_[i].getPosition(), pos) < parameters_.interactionRange) {
      repulsiveClick_
          ? flock_[i] +=
            ((flock_[i].getPosition() - pos) * (parameters_.clickStrength))
          : flock_[i] +=
            -((flock_[i].getPosition() - pos) * (parameters_.clickStrength));
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// REPEL between FLOCKS

std::vector<sf::Vector2f> Repel(const std::vector<Flock> &flockstack,
                                size_t i) {
  std::vector<sf::Vector2f> repelSpeed;
  repelSpeed.clear();

  for (size_t j{0}; j < flockstack[i].getSize();
       j++) { // PER TUTTI gli ELEMENTI del PRIMO FLOCK
    repelSpeed.emplace_back();
    for (size_t k{0}; k < flockstack.size(); k++) {
      if (i != k) // PER TUTTI gli ALTRI FLOCK
        for (size_t l{0}; l < flockstack[k].getSize();
             l++) { // SOMMA SU TUTTI I BOID di OGNI SINGOLO FLOCK
          if (distance(flockstack[i].getBoid(j), flockstack[k].getBoid(l)) <
                  Flock::getParameters().repelRange &&
              (flockstack[i].getBoid(j).getPosition().x -
                   flockstack[k].getBoid(l).getPosition().x !=
               0) &&
              (flockstack[i].getBoid(j).getPosition().y -
                   flockstack[k].getBoid(l).getPosition().y !=
               0)) { // TALI che la DISTANZA è MINORE del
            // PARAMETRO
            repelSpeed[j] +=
                ((flockstack[k].getBoid(l).getPosition() -
                  flockstack[i].getBoid(j).getPosition()) *
                 (-Flock::getParameters().repelStrength)); // AGGIUNGI VELOCITà
          }
        }
    }
  }

  return repelSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE FLOCK

Flock createFlock(size_t n, sf::Vector2f center, sf::Color color) {
  std::uniform_real_distribution angleCenter(0.f, 2.f * M_PIf);
  float a{angleCenter(rng)};

  std::vector<Boid> flock;
  for (size_t i{}; i < n; i++) {
    flock.emplace_back(createBoid(center, a));
  }

  assert(flock.size() >= constants::minFlockSize);

  return {flock, color};
}
