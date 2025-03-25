#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>

namespace ev {

class Boid;

struct TguiPar {
  float posX{};
  float posY{};
  float width{};
  float height{};
};

struct SwitchButtonPar : TguiPar {
  const std::string onText{"ON"};
  const std::string offText{"OFF"};
  const sf::Color onColor{sf::Color::White};
  const sf::Color offColor{sf::Color::White};
};
struct SlidersPar : TguiPar {
  float min{};
  float max{};
  float initialValue{};
};

struct LabelsPar {
  float posX{};
  float posY{};
  unsigned textSize{};
};

struct RectanglePar {
  float posX{};
  float posY{};
  float width{};
  float height{};
};

// DRAW BOID

sf::CircleShape getTriangleBoid(const Boid &boid,
                                const sf::Color &color = sf::Color::Black);

// function to create a rectangle from parameters

sf::RectangleShape getRectangle(const RectanglePar &par,
                                const sf::Color &color = sf::Color::Black);

}  // namespace ev

#endif