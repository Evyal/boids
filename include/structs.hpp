#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <SFML/Graphics/Color.hpp>
#include <string>

namespace ev {

//////////////////////////////////////////////////////////////////////////////////////////
// Parameters for a generic TGUI object
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

//////////////////////////////////////////////////////////////////////////////////////////
// Parameters to create a sf::Rectangle
struct RectanglePar {
  float posX{};
  float posY{};
  float width{};
  float height{};
};

//////////////////////////////////////////////////////////////////////////////////////////
// Parameters for flocks' interactions.
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

//////////////////////////////////////////////////////////////////////////////////////////
// Struct for keeping MEAN and STD DEV

struct StatsPar {
  float mean{};
  float sigma{};
};
}  // namespace ev

#endif