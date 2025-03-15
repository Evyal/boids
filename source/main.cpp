#include "../include/egui.hpp"
#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/ChatBox.hpp>
#include <cmath>
#include <cstdlib>

int main() {

  Egui egui;
  egui.setup();
  egui.run();

  return 0;
}