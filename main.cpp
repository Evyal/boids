#include "egui.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
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