#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <SFML/Graphics/Color.hpp>

struct TguiPar {
  float posX{};
  float posY{};
  float width{};
  float height{};
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

#endif