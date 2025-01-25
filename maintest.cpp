#include "SFML/Graphics.hpp"
#include "constants.hpp"
#include "control.hpp"
#include "egui.hpp"
#include "flock.hpp"
#include "graphics.hpp"
#include "random.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/ChatBox.hpp>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

extern float windowX;
extern float windowY;

float separation{0.5f};
float separationRange{12.0f};
float alignment{0.03f};
float cohesion{0.015f};
float repel{0.3f};
float repelRange{20.0f};
bool toroidal{false};

std::default_random_engine rng(static_cast<size_t>(
    std::chrono::steady_clock::now().time_since_epoch().count()));

int main() {

  Egui egui;
  egui.setup();
  egui.run();

  return 0;
}