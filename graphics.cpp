#include "graphics.hpp"
#include "boid.hpp"
#include "constants.hpp"
#include "flock.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <cmath>
#include <cstddef>

// DRAW FLOCK

sf::CircleShape boidCircle(const Flock &flock, size_t i) {
  sf::CircleShape boidBody{constants::boidSize};
  boidBody.setOrigin(constants::boidSize, constants::boidSize);
  boidBody.setPosition(flock.getBoid(i).getPositionX(),
                       flock.getBoid(i).getPositionY());
  boidBody.setFillColor(flock.getFlockColor());
  return boidBody;
}

sf::CircleShape boidTriangle(const Flock &flock, size_t i) {
  sf::CircleShape boidBody(constants::boidSize, 3);
  boidBody.setScale(1, 2);
  boidBody.setFillColor(flock.getFlockColor());
  boidBody.setOrigin(constants::boidSize, constants::boidSize);
  boidBody.setPosition(flock.getBoid(i).getPositionX(),
                       flock.getBoid(i).getPositionY());

  // if (flock.getBoid(i).getSpeedY() >= 0) {
  boidBody.rotate(180 *
                  std::atan2(flock.getBoid(i).getVelocityX(),
                             -flock.getBoid(i).getVelocityY()) /
                  M_PIf);
  return boidBody;
}
