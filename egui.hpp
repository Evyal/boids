#ifndef EGUI_HPP
#define EGUI_HPP

#include "flock.hpp"
#include "structs.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Vector2.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/EditBoxSlider.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Slider.hpp>
#include <array>
#include <cstddef>
#include <string>
#include <vector>

class Egui {
public:
  ////////////////////////////////////////////////////////////////////////////////

  Egui();       // Constructor
  void setup(); // Sets up the application
  void run();   // Runs the application

private:
  ////////////////////////////////////////////////////////////////////////////////
  // WINDOW

  sf::RenderWindow window;
  tgui::Gui gui;

  ////////////////////////////////////////////////////////////////////////////////
  // keep track of FLOCKS and their GRAPHICS

  std::vector<Flock> flockStack_;
  std::vector<std::vector<sf::CircleShape>> bodyStack_;

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // THREE WAY SWITCH, SELECT OPTION

  tgui::Button::Ptr option1;
  tgui::Button::Ptr option2;
  tgui::Button::Ptr option3;
  tgui::Button::Ptr activeButton = nullptr; // Track the active button

  void createThreeWaySwitch();
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
  tgui::Button::Ptr switchButton;
  bool isSwitchOn = false;

  void createSwitchButton();
  void toggleSwitch();

  ////////////////////////////////////////////////////////////////////////////////

  std::vector<tgui::Button::Ptr> dynamicButtons;
  std::vector<std::array<tgui::Label::Ptr, 4>> dynamicLabels;

  void createDeleteFlockButton(size_t index);
  void deleteDeleteFlockButton(size_t index);
  void repositionButtons();

  ////////////////////////////////////////////////////////////////////////////////

  void drawStatistics();

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // OPTION 2

  std::vector<tgui::Slider::Ptr> option2Sliders;
  std::vector<tgui::Label::Ptr> option2Labels;

  // CREATE and STORE
  void createSliderOpt2(const SlidersParameters &sliderPar);
  void createLabelOpt2(const LabelsParameters &labelsPar);
  void setLabelTextOpt2(size_t i, const std::string &text);

  void handleColorSliderChange(tgui::Slider::Ptr changedSlider);

  tgui::Button::Ptr addFlockButton;
  tgui::Label::Ptr addFlockButtonLabel;

  void createAddFlockButton(const TguiParameters &par);
  void enableCreateFlockButton();

  ////////////////////////////////////////////////////////////////////////////////

  void setupOpt2();
  void setVisibleOpt2(bool visible);

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // OPTION 3

  std::vector<tgui::EditBoxSlider::Ptr> option3Sliders;
  std::vector<tgui::Label::Ptr> option3Labels;

  // 0 separationSlider
  // 1 separationRangeSlider
  // 2 alignmentSlider
  // 3 cohesionSlider
  // 4 interactionSlider
  // 5 repelSlider
  // 6 repelRangeSlider

  tgui::EditBoxSlider::Ptr separationSlider;
  tgui::EditBoxSlider::Ptr separationRangeSlider;
  tgui::EditBoxSlider::Ptr alignmentSlider;
  tgui::EditBoxSlider::Ptr cohesionSlider;
  tgui::EditBoxSlider::Ptr interactionSlider;
  tgui::EditBoxSlider::Ptr repelSlider;
  tgui::EditBoxSlider::Ptr repelRangeSlider;

  void createParametersSliders();

  void createSliderOpt3(const SlidersParameters &sliderPar);
  void createLabelOpt3(const LabelsParameters &labelsPar,
                       const std::string &text);

  ////////////////////////////////////////////////////////////////////////////////

  void setupOpt3();
  void setVisibleOpt3(bool visible);

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // INTERFACE

  void drawInterface();

  ////////////////////////////////////////////////////////////////////////////////
  // FLOCKS and DRAWING

  sf::Font sans;

  void addFlock(size_t n = 20, sf::Vector2f center = {360, 360},
                sf::Color color = sf::Color::Black);
  void deleteFlock(size_t i);
  void evolveFlock();
  void drawFlocks();
  void printFlock(size_t i);

  ////////////////////////////////////////////////////////////////////////////////

  size_t getActiveBoids();

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
};

#endif
