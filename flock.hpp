#ifndef FLOCK_H
#define FLOCK_H

#include "SFML/Graphics.hpp"
#include "boid.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <vector>

class Flock {

private:
  std::vector<Boid> flock_;
  sf::Color color_;

public:
  // COSTRUTTORI
  Flock(const std::vector<Boid> &flock, const sf::Color &color);
  Flock(const std::vector<Boid> &flock);
  Flock();

  // ADDERS
  void AddBoid(const Boid &boid);
  void AddBoids(const std::vector<Boid> &flock);

  // GETTERS
  Boid getBoid(size_t i) const;
  std::vector<Boid> getBoids() const;
  size_t getSize() const;
  sf::Color getFlockColor() const;

  sf::Vector2f getMassCenter() const;
  sf::Vector2f getMeanVelocity() const;
  float getMeanSpeed() const;

  std::vector<sf::Vector2f> getFlockPositions() const;
  std::vector<sf::Vector2f> getFlockVelocities() const;
  std::vector<float> getFlockPositionsX() const;
  std::vector<float> getFlockPositionsY() const;
  std::vector<float> getFlockVelocitiesX() const;
  std::vector<float> getFlockVelocitiesY() const;
  std::vector<float> getSpeedVector() const;

  // RULES
  // SEPARATION
  std::vector<sf::Vector2f> Separation(float s, float ds) const;
  // ALIGNMENT
  std::vector<sf::Vector2f> Alignment(float a) const;
  // COESION
  std::vector<sf::Vector2f> Cohesion(float c, bool toroidal) const;

  // UPDATE
  void updateFlock(const std::vector<sf::Vector2f> &separationSpeed,
                   const std::vector<sf::Vector2f> &alignSpeed,
                   const std::vector<sf::Vector2f> &coesionSpeed,
                   bool toroidal);

  void updateFlockRepel(const std::vector<sf::Vector2f> &separationSpeed,
                        const std::vector<sf::Vector2f> &alignmentSpeed,
                        const std::vector<sf::Vector2f> &coesionSpeed,
                        const std::vector<sf::Vector2f> &repelSpeed,
                        bool toroidal);
};

// REPEL
std::vector<sf::Vector2f> Repel(const std::vector<Flock> &flockstack, size_t i,
                                float r, float range);

// CREATE FLOCKS
Flock createRandomFlock();
Flock createFlock(size_t n, sf::Vector2f center, sf::Color color);

// DELETE FLOCKS

#endif