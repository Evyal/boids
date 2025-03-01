#include "graphics.hpp"
#include "boid.hpp"
#include "constants.hpp"
#include "structs.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <cmath>

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE BOIDS as CIRCLES

sf::CircleShape drawCircleBoid(const Boid &boid, sf::Color color) {
  sf::CircleShape boidBody{constants::boidSize};
  boidBody.setOrigin(constants::boidSize, constants::boidSize);
  boidBody.setPosition(boid.getPosition().x, boid.getPosition().y);
  boidBody.setFillColor(color);
  return boidBody;
}

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE BOIDS as TRIANGLES

sf::CircleShape drawTriangleBoid(const Boid &boid, sf::Color color) {
  sf::CircleShape boidBody(constants::boidSize, 3);
  boidBody.setScale(1, 2);
  boidBody.setFillColor(color);
  boidBody.setOrigin(constants::boidSize, constants::boidSize);
  boidBody.setPosition(boid.getPosition());

  boidBody.rotate(
      180 * std::atan2(boid.getVelocity().x, -boid.getVelocity().y) / M_PIf);
  return boidBody;
}

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE RECTANGLE

sf::RectangleShape drawRectangle(const RectangleParameters &par) {
  sf::RectangleShape rectangle(sf::Vector2f(par.width, par.height));
  rectangle.setPosition(par.posX, par.posY);
  rectangle.setFillColor(par.color);
  return rectangle;
}