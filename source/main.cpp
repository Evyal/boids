#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/ChatBox.hpp>
#include <cmath>
#include <cstdlib>

#include "../include/gui.hpp"

int main() {
  ev::Gui program;
  program.setup();
  program.run();

  return 0;
}