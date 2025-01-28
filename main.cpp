#include "egui.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/ChatBox.hpp>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <random>

std::default_random_engine rng(static_cast<size_t>(
    std::chrono::steady_clock::now().time_since_epoch().count()));



int main() {

  Egui egui;
  egui.setup();
  egui.run();

  return 0;
}