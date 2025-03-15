#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <SFML/Graphics/Color.hpp>
#include <string>

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

struct FlockPar {
  float separationStrength{};
  float separationRange{};
  float alignmentStrength{};
  float cohesionStrength{};
  float interactionRange{};
  float repelStrength{};
  float repelRange{};
  float clickStrength{};
};

#endif