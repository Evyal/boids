#include "graphics.hpp"
#include "boid.hpp"
#include "constants.hpp"
#include "flock.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <cmath>
#include <cstddef>

// DRAW BOIDS as CIRCLES

sf::CircleShape boidCircle(const Flock &flock, size_t i) {
  sf::CircleShape boidBody{constants::boidSize};
  boidBody.setOrigin(constants::boidSize, constants::boidSize);
  boidBody.setPosition(flock.getBoid(i).getPosition().x,
                       flock.getBoid(i).getPosition().y);
  boidBody.setFillColor(flock.getFlockColor());
  return boidBody;
}

// DRAW BOIDS as TRIANGLES

sf::CircleShape boidTriangle(const Flock &flock, size_t i) {
  sf::CircleShape boidBody(constants::boidSize, 3);
  boidBody.setScale(1, 2);
  boidBody.setFillColor(flock.getFlockColor());
  boidBody.setOrigin(constants::boidSize, constants::boidSize);
  boidBody.setPosition(flock.getBoid(i).getPosition());

  boidBody.rotate(180 *
                  std::atan2(flock.getBoid(i).getVelocity().x,
                             -flock.getBoid(i).getVelocity().y) /
                  M_PIf);
  return boidBody;
}
