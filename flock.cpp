#include "flock.hpp"
#include "SFML/Graphics.hpp"
#include "boid.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <random>
#include <vector>

extern float windowX;
extern float windowY;
extern std::default_random_engine rng;

// COSTRUTTORI

Flock::Flock(const std::vector<Boid> &flock, const sf::Color &color) // VA BENE?
    : flock_{flock}, color_{color} {}
Flock::Flock(const std::vector<Boid> &flock)
    : flock_{flock}, color_{sf::Color::Black} {}
Flock::Flock() : flock_{}, color_{sf::Color::Black} {}

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

std::vector<float> Flock::getFlockPositionsX() const {
  std::vector<float> positions;
  for (size_t i{0}; i < flock_.size(); i++) {
    positions.emplace_back(flock_[i].getPositionX());
  }
  return positions;
}

std::vector<float> Flock::getFlockPositionsY() const {
  std::vector<float> positions;
  for (size_t i{0}; i < flock_.size(); i++) {
    positions.emplace_back(flock_[i].getPositionY());
  }
  return positions;
}

std::vector<float> Flock::getFlockVelocitiesX() const {
  std::vector<float> velocities;
  for (size_t i{0}; i < flock_.size(); i++) {
    velocities.emplace_back(flock_[i].getVelocityX());
  }
  return velocities;
}

std::vector<float> Flock::getFlockVelocitiesY() const {
  std::vector<float> velocities;
  for (size_t i{0}; i < flock_.size(); i++) {
    velocities.emplace_back(flock_[i].getVelocityY());
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

// ADDERS

void Flock::AddBoid(const Boid &boid) { flock_.emplace_back(boid); }
void Flock::AddBoids(const std::vector<Boid> &flock) {
  for (auto i : flock)
    flock_.emplace_back(i);
}

// SEPARATION RULE

std::vector<sf::Vector2f> Flock::Separation(float s, float ds) const {
  std::vector<sf::Vector2f> separationSpeed{};
  assert((flock_.size() > 1));
  separationSpeed.clear();

  for (size_t i{0}; i < flock_.size(); ++i) {
    separationSpeed.emplace_back();

    for (size_t j{0}; j < flock_.size(); ++j) {
      if (j != i && (distance(flock_[j], flock_[i]) < ds) &&
          ((flock_[j].getPositionX() - flock_[i].getPositionX()) != 0) &&
          ((flock_[j].getPositionY() - flock_[i].getPositionY()) != 0)) {
        separationSpeed[i].x +=
            (1 * (flock_[j].getPositionX() - flock_[i].getPositionX()) * (-s));
        separationSpeed[i].y +=
            (1 * (flock_[j].getPositionY() - flock_[i].getPositionY()) * (-s));
      }
    }
  }
  return separationSpeed;
}

// ALIGNMENT RULE

std::vector<sf::Vector2f> Flock::Alignment(float a) const {
  std::vector<sf::Vector2f> alignSpeed{};
  assert((flock_.size() > 1));
  alignSpeed.clear();

  for (size_t i{0}; i < flock_.size(); ++i) {
    alignSpeed.emplace_back();
    for (size_t j{0}; j < flock_.size(); ++j) {
      if (j != i) {
        alignSpeed[i] += ((flock_[j].getVelocity() - flock_[i].getVelocity()) *
                          (a / (static_cast<float>(flock_.size()) - 1.f)));
      }
    }
  }

  return alignSpeed;
}

// COESION RULE

std::vector<sf::Vector2f> Flock::Cohesion(float c, bool toroidal) const {
  std::vector<sf::Vector2f> coesionSpeed{};
  assert((flock_.size() > 1));
  coesionSpeed.clear();

  if (toroidal) {
    for (size_t i{0}; i < flock_.size(); i++) {
      coesionSpeed.emplace_back();
      sf::Vector2f massCenter{0, 0};

      for (size_t j{0}; j < flock_.size(); j++) {
        if (j != i) {
          if (deltaX(flock_[j], flock_[i]) > windowX / 2) {
            massCenter.x += (flock_[j].getPositionX() - windowX);
          } else if (deltaX(flock_[j], flock_[i]) < -windowX / 2) {
            massCenter.x += (flock_[j].getPositionX() + windowX);
          } else {
            massCenter.x += (flock_[j].getPositionX());
          }
          if (deltaY(flock_[j], flock_[i]) > windowY / 2) {
            massCenter.y += (flock_[j].getPositionY() - windowY);
          } else if (deltaY(flock_[j], flock_[i]) < -windowY / 2) {
            massCenter.y += (flock_[j].getPositionY() + windowY);
          } else {
            massCenter.y += (flock_[j].getPositionY());
          }
        }
      }
      coesionSpeed[i] +=
          ((massCenter * (1 / (static_cast<float>(flock_.size()) - 1)) -
            flock_[i].getPosition()) *
           c);
    }
  } else {
    for (size_t i{0}; i < flock_.size(); i++) {
      coesionSpeed.emplace_back();
      sf::Vector2f massCenter{0, 0};

      for (size_t j{0}; j < flock_.size(); j++) {
        if (j != i) {
          massCenter += (flock_[j].getPosition() *
                         (1 / (static_cast<float>(flock_.size()) - 1)));
        }
      }
      coesionSpeed[i] += ((massCenter - flock_[i].getPosition()) * c);
    }
  }

  return coesionSpeed;
}

// UPDATE

void Flock::updateFlock(const std::vector<sf::Vector2f> &separationSpeed,
                        const std::vector<sf::Vector2f> &alignmentSpeed,
                        const std::vector<sf::Vector2f> &coesionSpeed,
                        bool toroidal) {
  for (size_t i{0}; i < flock_.size(); ++i) {
    flock_[i].setPosition(flock_[i].getPosition() +
                          flock_[i].getVelocity() / 100.f);
    flock_[i] += (separationSpeed[i] + alignmentSpeed[i] + coesionSpeed[i]);
    if (toroidal) {
      toroidalBorders(flock_[i]);
    } else {
      mirrorBorders(flock_[i]);
    }
    checkMinimumSpeed(flock_[i]);
    checkMaximumSpeed(flock_[i]);
  }
}

void Flock::updateFlockRepel(const std::vector<sf::Vector2f> &separationSpeed,
                             const std::vector<sf::Vector2f> &alignmentSpeed,
                             const std::vector<sf::Vector2f> &coesionSpeed,
                             const std::vector<sf::Vector2f> &repelSpeed,
                             bool toroidal) {
  for (size_t i{0}; i < flock_.size(); ++i) {
    flock_[i].setPosition(flock_[i].getPosition() +
                          flock_[i].getVelocity() / 160.f);
    flock_[i] += (separationSpeed[i] + alignmentSpeed[i] + coesionSpeed[i] +
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

// CREATE FLOCK

Flock createRandomFlock() {
  std::uniform_real_distribution positionCenter(0.f, 720.f);
  float centerX{positionCenter(rng)};
  float centerY{positionCenter(rng)};

  std::uniform_real_distribution angleCenter(0.f, 2.f * M_PIf);
  float angle{angleCenter(rng)};

  std::uniform_int_distribution flockSize(5, 100);
  size_t size{static_cast<size_t>(flockSize(rng))};

  std::vector<Boid> flock;
  for (size_t i{}; i < size; i++) {
    flock.emplace_back(buildBoid({centerX, centerY}, angle));
  }
  return {flock};
}

Flock createFlock(size_t n, sf::Vector2f center, sf::Color color) {
  std::uniform_real_distribution angleCenter(0.f, 2.f * M_PIf);
  float a{angleCenter(rng)};

  std::vector<Boid> flock;
  for (size_t i{}; i < n; i++) {
    flock.emplace_back(buildBoid(center, a));
  }
  return {flock, color};
}

std::vector<sf::Vector2f> Repel(const std::vector<Flock> &flockstack, size_t i,
                                float r, float range) {
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
                  range &&
              (flockstack[i].getBoid(j).getPositionX() -
                   flockstack[k].getBoid(l).getPositionX() !=
               0) &&
              (flockstack[i].getBoid(j).getPositionY() -
                   flockstack[k].getBoid(l).getPositionY() !=
               0)) { // TALI che la DISTANZA è MINORE del
                     // PARAMETRO
            repelSpeed[j] += ((flockstack[k].getBoid(l).getPosition() -
                               flockstack[i].getBoid(j).getPosition()) *
                              (-r)); // AGGIUNGI VELOCITà
          }
        }
    }
  }

  return repelSpeed;
}
