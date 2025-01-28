#include "flock.hpp"
#include "boid.hpp"
#include "constants.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <random>
#include <vector>

extern std::default_random_engine rng;
extern bool toroidal;

//////////////////////////////////////////////////////////////////////////////////////////
// COSTRUTTORI

Flock::Flock(const std::vector<Boid> &flock, const sf::Color &color) // VA BENE?
    : flock_{flock}, color_{color} {}
Flock::Flock(const std::vector<Boid> &flock)
    : flock_{flock}, color_{sf::Color::Black} {}
Flock::Flock() : flock_{}, color_{sf::Color::Black} {}

//////////////////////////////////////////////////////////////////////////////////////////
// GETTERS

std::vector<Boid> Flock::getBoids() const { return flock_; }
Boid Flock::getBoid(size_t i) const { return flock_[i]; }
size_t Flock::getSize() const { return flock_.size(); }
sf::Color Flock::getFlockColor() const { return color_; }

sf::Vector2f Flock::getMassCenter() const {
  sf::Vector2f massCenter{0, 0};
  assert((flock_.size() > 1));
  for (size_t j{0}; j < flock_.size(); j++) {
    massCenter += (flock_[j].getPosition());
  }
  return {massCenter * (1 / (static_cast<float>(flock_.size())))};
}
sf::Vector2f Flock::getMeanVelocity() const {
  sf::Vector2f meanVelocity{0, 0};
  assert((flock_.size() > 1));
  for (size_t j{0}; j < flock_.size(); j++) {
    meanVelocity += (flock_[j].getVelocity());
  }
  return {meanVelocity * (1 / (static_cast<float>(flock_.size())))};
}

float Flock::getMeanSpeed() const {
  float meanSpeed{0};
  for (size_t j{0}; j < flock_.size(); j++) {
    meanSpeed += (flock_[j].getSpeed());
  }
  return meanSpeed / (static_cast<float>(flock_.size()));
}

std::vector<sf::Vector2f> Flock::getFlockPositions() const {
  std::vector<sf::Vector2f> positions;
  for (size_t i{0}; i < flock_.size(); i++) {
    positions.emplace_back(flock_[i].getPosition());
  }
  return positions;
}

std::vector<sf::Vector2f> Flock::getFlockVelocities() const {
  std::vector<sf::Vector2f> velocities;
  for (size_t i{0}; i < flock_.size(); i++) {
    velocities.emplace_back(flock_[i].getVelocity());
  }
  return velocities;
}

std::vector<float> Flock::getSpeedVector() const {
  std::vector<float> speeds;
  for (size_t i{0}; i < flock_.size(); i++) {
    speeds.emplace_back(flock_[i].getSpeed());
  }
  return speeds;
}

//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
// RULES

// SEPARATION RULE

std::vector<sf::Vector2f> Flock::Separation(float separation,
                                            float separationRange) const {
  std::vector<sf::Vector2f> separationSpeed{};
  assert((flock_.size() > 1));
  separationSpeed.clear();

  for (size_t i{0}; i < flock_.size(); ++i) {
    separationSpeed.emplace_back();

    for (size_t j{0}; j < flock_.size(); ++j) {
      if (j != i && (distance(flock_[j], flock_[i]) < separationRange) &&
          ((flock_[j].getPositionX() - flock_[i].getPositionX()) != 0) &&
          ((flock_[j].getPositionY() - flock_[i].getPositionY()) != 0)) {
        separationSpeed[i].x +=
            (1 * (flock_[j].getPositionX() - flock_[i].getPositionX()) *
             (-separation));
        separationSpeed[i].y +=
            (1 * (flock_[j].getPositionY() - flock_[i].getPositionY()) *
             (-separation));
      }
    }
  }
  return separationSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ALIGNMENT RULE

// ALIGMENT WITHOUT TOROIDAL ADJUSTMENTS
std::vector<sf::Vector2f> Flock::Alignment(float alignment,
                                           float interaction) const {
  std::vector<sf::Vector2f> alignSpeed{};
  assert((flock_.size() > 1));
  alignSpeed.clear();

  sf::Vector2f x{720.f, 0};
  sf::Vector2f y{720.f, 0};

  for (size_t i{0}; i < flock_.size(); ++i) {
    alignSpeed.emplace_back();
    for (size_t j{0}; j < flock_.size(); ++j) {
      if (j != i && distance(flock_[i], flock_[j]) < interaction) {
        alignSpeed[i] +=
            ((flock_[j].getVelocity() - flock_[i].getVelocity()) *
             (alignment / (static_cast<float>(flock_.size()) - 1.f)));
      }
    }
  }

  return alignSpeed;
}

// ALIGMENT with TOROIDAL MODE, too LAGGY
// std::vector<sf::Vector2f> Flock::Alignment(float alignment,
//                                            float interaction) const {
//   std::vector<sf::Vector2f> alignSpeed{};
//   assert((flock_.size() > 1));
//   alignSpeed.clear();

//   sf::Vector2f x{720.f, 0};
//   sf::Vector2f y{720.f, 0};

//   if (toroidal) { // EXTRA CHECK for INTERACTION with TOROIDAL MODE
//     for (size_t i{0}; i < flock_.size(); i++) {
//       alignSpeed.emplace_back();

//       for (size_t j{0}; j < flock_.size(); j++) {
//         if (j != i) {
//           if (distance(flock_[i], flock_[j]) < interaction ||
//               calculateDistance(flock_[i].getPosition() + x,
//                                 flock_[j].getPosition()) < interaction ||
//               calculateDistance(flock_[i].getPosition() - x,
//                                 flock_[j].getPosition()) < interaction ||
//               calculateDistance(flock_[i].getPosition() + y,
//                                 flock_[j].getPosition()) < interaction ||
//               calculateDistance(flock_[i].getPosition() - y,
//                                 flock_[j].getPosition()) < interaction) {
//             alignSpeed[i] +=
//                 ((flock_[j].getVelocity() - flock_[i].getVelocity()) *
//                  (alignment / (static_cast<float>(flock_.size()) - 1.f)));
//           }
//         }
//       }
//     }
//   } else {
//     for (size_t i{0}; i < flock_.size(); ++i) {
//       alignSpeed.emplace_back();
//       for (size_t j{0}; j < flock_.size(); ++j) {
//         if (j != i && distance(flock_[i], flock_[j]) < interaction) {
//           alignSpeed[i] +=
//               ((flock_[j].getVelocity() - flock_[i].getVelocity()) *
//                (alignment / (static_cast<float>(flock_.size()) - 1.f)));
//         }
//       }
//     }
//   }

//   return alignSpeed;
// }

//////////////////////////////////////////////////////////////////////////////////////////
// COESION RULE

std::vector<sf::Vector2f> Flock::Cohesion(float cohesion,
                                          float interaction) const {
  std::vector<sf::Vector2f> cohesionSpeed{};
  assert((flock_.size() > 1));
  cohesionSpeed.clear();

  if (toroidal) {
    for (size_t i{0}; i < flock_.size(); i++) {
      cohesionSpeed.emplace_back();
      sf::Vector2f massCenter{0, 0};

      for (size_t j{0}; j < flock_.size(); j++) {
        if (j != i) {
          if (deltaX(flock_[j], flock_[i]) > constants::fieldSide / 2) {
            massCenter.x += (flock_[j].getPositionX() - constants::fieldSide);
          } else if (deltaX(flock_[j], flock_[i]) < -constants::fieldSide / 2) {
            massCenter.x += (flock_[j].getPositionX() + constants::fieldSide);
          } else {
            massCenter.x += (flock_[j].getPositionX());
          }
          if (deltaY(flock_[j], flock_[i]) > constants::fieldSide / 2) {
            massCenter.y += (flock_[j].getPositionY() - constants::fieldSide);
          } else if (deltaY(flock_[j], flock_[i]) < -constants::fieldSide / 2) {
            massCenter.y += (flock_[j].getPositionY() + constants::fieldSide);
          } else {
            massCenter.y += (flock_[j].getPositionY());
          }
        }
      }
      cohesionSpeed[i] +=
          ((massCenter * (1 / (static_cast<float>(flock_.size()) - 1)) -
            flock_[i].getPosition()) *
           cohesion);
    }
  } else {
    for (size_t i{0}; i < flock_.size(); i++) {
      cohesionSpeed.emplace_back();
      sf::Vector2f massCenter{0, 0};
      int count{0};
      bool a{false};

      for (size_t j{0}; j < flock_.size(); j++) {
        if (j != i && distance(flock_[i], flock_[j]) < interaction) {
          massCenter += (flock_[j].getPosition());
          count += 1;
          a = true;
        }
      }
      if (a) {
        cohesionSpeed[i] += ((massCenter / (static_cast<float>(count)) -
                              flock_[i].getPosition()) *
                             cohesion);
      }
    }
  }

  return cohesionSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
// UPDATE

void Flock::updateFlock(const std::vector<sf::Vector2f> &separationSpeed,
                        const std::vector<sf::Vector2f> &alignmentSpeed,
                        const std::vector<sf::Vector2f> &cohesionSpeed,
                        const std::vector<sf::Vector2f> &repelSpeed) {
  for (size_t i{0}; i < flock_.size(); ++i) {
    flock_[i].setPosition(flock_[i].getPosition() +
                          flock_[i].getVelocity() / 150.f);
    flock_[i] += (separationSpeed[i] + alignmentSpeed[i] + cohesionSpeed[i] +
                  repelSpeed[i]);
    if (toroidal) {
      toroidalBorders(flock_[i]);
    } else {
      mirrorBorders(flock_[i]);
    }
    checkMinimumSpeed(flock_[i]);
    checkMaximumSpeed(flock_[i]);
  }
}

std::vector<sf::Vector2f> Repel(const std::vector<Flock> &flockstack, size_t i,
                                float repel, float repelRange) {
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
                  repelRange &&
              (flockstack[i].getBoid(j).getPositionX() -
                   flockstack[k].getBoid(l).getPositionX() !=
               0) &&
              (flockstack[i].getBoid(j).getPositionY() -
                   flockstack[k].getBoid(l).getPositionY() !=
               0)) { // TALI che la DISTANZA è MINORE del
                     // PARAMETRO
            repelSpeed[j] += ((flockstack[k].getBoid(l).getPosition() -
                               flockstack[i].getBoid(j).getPosition()) *
                              (-repel)); // AGGIUNGI VELOCITà
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
    flock.emplace_back(buildBoid(center, a));
  }
  return {flock, color};
}
