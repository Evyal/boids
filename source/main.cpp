#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/ChatBox.hpp>
#include <cmath>
#include <cstdlib>

#include "../include/egui.hpp"

int main() {
  Egui egui;
  egui.setup();
  egui.run();

  return 0;
}