#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <array>
#include <cstddef>
#include <string>
#include <vector>

#include "flock.hpp"
#include "structs.hpp"
#include "switchbutton.hpp"

namespace ev {

class Gui {
 public:
  ////////////////////////////////////////////////////////////////////////////////

  Gui();
  void setup();
  void run();

 private:
  ////////////////////////////////////////////////////////////////////////////////
  // WINDOW

  sf::RenderWindow window_;
  tgui::Gui gui_;

  ////////////////////////////////////////////////////////////////////////////////
  // keep track of FLOCKS and their GRAPHICS

  std::vector<Flock> flockStack_;
  std::vector<std::vector<sf::CircleShape>> bodyStack_;
  sf::Font sans;

  ////////////////////////////////////////////////////////////////////////////////

  bool pause_{false};

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // INTERFACE

  sf::Color backgroundColour_{sf::Color::Black};

  void drawMargin();
  void drawInterface();

  ////////////////////////////////////////////////////////////////////////////////
  // THREE WAY SWITCH, SELECT OPTION

  tgui::Button::Ptr option1;
  tgui::Button::Ptr option2;
  tgui::Button::Ptr option3;
  tgui::Button::Ptr activeButton = nullptr;

  void createThreeWaySwitch(const TguiPar &button1, const TguiPar &button2,
                            const TguiPar &button3);
  void toggleButtons(tgui::Button::Ptr pressedButton);

  // CONTINUOUS SELECTION
  void selectedOption();

  // SELECTION on CLICK
  void selectedOption1();
  void selectedOption2();
  void selectedOption3();

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // OPTION 1

  // ON OFF BUTTON, for MIRROR or TOROIDAL MODE
  std::shared_ptr<SwitchButton> graphicButton;

  ////////////////////////////////////////////////////////////////////////////////

  std::vector<tgui::Button::Ptr> dynamicButtons;
  std::vector<std::array<tgui::Label::Ptr, 4>> dynamicLabels;

  void createDeleteFlockButton(size_t index);
  void createStatisticsLabel(size_t index);
  void deleteDeleteFlockButton(size_t index);
  void repositionButtons();

  ////////////////////////////////////////////////////////////////////////////////

  void drawStatistics();

  void printValue(const LabelsPar &par, int value, size_t index);
  void printFlockStats();
  void printToroidalFlockStats();

  ////////////////////////////////////////////////////////////////////////////////

  void setupOpt1();
  void setVisibleOpt1(bool visible);

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // OPTION 2

  std::vector<tgui::Slider::Ptr> option2Sliders;
  std::vector<tgui::Label::Ptr> option2Labels;

  // CREATE and STORE
  void createSliderOpt2(const SlidersPar &sliderPar);
  void createLabelOpt2(const LabelsPar &labelsPar);
  void setLabelTextOpt2(size_t index, const std::string &text);

  void handleColorSliderChange(tgui::Slider::Ptr changedSlider);

  // OPTION TO CREATE NEW FLOCKS
  tgui::Button::Ptr addFlockButton;
  tgui::Label::Ptr addFlockButtonLabel;

  void createAddFlockButton(const TguiPar &par);
  void enableCreateFlockButton();

  ////////////////////////////////////////////////////////////////////////////////

  void setupOpt2();
  void setVisibleOpt2(bool visible);

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // OPTION 3

  std::vector<tgui::EditBoxSlider::Ptr> option3Sliders;
  std::vector<tgui::Label::Ptr> option3Labels;

  tgui::EditBoxSlider::Ptr separationSlider;       // 0
  tgui::EditBoxSlider::Ptr separationRangeSlider;  // 1
  tgui::EditBoxSlider::Ptr alignmentSlider;        // 2
  tgui::EditBoxSlider::Ptr cohesionSlider;         // 3
  tgui::EditBoxSlider::Ptr interactionSlider;      // 4
  tgui::EditBoxSlider::Ptr repelSlider;            // 5
  tgui::EditBoxSlider::Ptr repelRangeSlider;       // 6
  tgui::EditBoxSlider::Ptr clickStrengthSlider;    // 7
  tgui::EditBoxSlider::Ptr frameRateLimitSlider;   // 8

  void createSliderOpt3(const SlidersPar &sliderPar);
  void createLabelOpt3(const LabelsPar &labelsPar, const std::string &text);

  ////////////////////////////////////////////////////////////////////////////////

  // ON OFF BUTTON, for MIRROR or TOROIDAL MODE
  std::shared_ptr<SwitchButton> toroidalButton;
  std::shared_ptr<SwitchButton> repulsiveClickButton;

  ////////////////////////////////////////////////////////////////////////////////

  void setupOpt3();
  void setVisibleOpt3(bool visible);

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // FLOCKS and DRAWING

  void addFlock(size_t n = 20, sf::Vector2f center = {360, 360},
                sf::Color color = sf::Color::Black);
  void deleteFlock(size_t i);
  void evolveFlocks();
  void drawFlocks();

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // OTHER RANDOM FUNCS

  size_t getActiveBoids();

  void interactWithFlocks();

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
};

}  // namespace ev

#endif
