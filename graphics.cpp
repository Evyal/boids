#include "graphics.hpp"
#include "boid.hpp"
#include "constants.hpp"
#include "structs.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE BOIDS as CIRCLES

sf::CircleShape getCircleBoid(const Boid &boid, const sf::Color &color) {
  sf::CircleShape boidBody{constants::boidSize};
  boidBody.setOrigin(constants::boidSize, constants::boidSize);
  boidBody.setPosition(boid.getPosition().x, boid.getPosition().y);
  boidBody.setFillColor(color);
  return boidBody;
}

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE BOIDS as TRIANGLES

sf::CircleShape getTriangleBoid(const Boid &boid, const sf::Color &color) {
  sf::CircleShape boidBody(constants::boidSize, 3);
  boidBody.setScale(1, 2);
  boidBody.setFillColor(color);
  boidBody.setOrigin(constants::boidSize, constants::boidSize);
  sf::Vector2f offSet{constants::marginSize, constants::marginSize};
  boidBody.setPosition(boid.getPosition() + offSet);

  boidBody.rotate(
      180 * std::atan2(boid.getVelocity().x, -boid.getVelocity().y) / M_PIf);
  return boidBody;
}

//////////////////////////////////////////////////////////////////////////////////////////
// CREATE RECTANGLE

sf::RectangleShape getRectangle(const RectanglePar &par,
                                const sf::Color &color) {
  sf::RectangleShape rectangle(sf::Vector2f(par.width, par.height));
  rectangle.setPosition(par.posX, par.posY);
  rectangle.setFillColor(color);
  return rectangle;
}