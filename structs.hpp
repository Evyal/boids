#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <SFML/Graphics/Color.hpp>

struct TguiParameters {
  float posX{};
  float posY{};
  float width{};
  float height{};
};
struct SlidersParameters : TguiParameters {
  float min{};
  float max{};
  float initialValue{};
};

struct LabelsParameters {
  float posX{};
  float posY{};
  unsigned textSize{};
};

struct RectangleParameters {
  float posX{};
  float posY{};
  float width{};
  float height{};
  sf::Color color{sf::Color::Black};
};

struct TextParameters {
    float posX{};
    float posY{};
    float width{};
    float height{};
    sf::Color color{sf::Color::Black};
  };

#endif