#ifndef EGUI_HPP
#define EGUI_HPP

#include "flock.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Vector2.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/EditBoxSlider.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <array>
#include <cstddef>
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
  // ON OFF BUTTON

  tgui::Button::Ptr switchButton;
  bool isSwitchOn = false;

  void createSwitchButton();
  void toggleSwitch();

  ////////////////////////////////////////////////////////////////////////////////
  // THREE WAY SWITCH

  tgui::Button::Ptr option1;
  tgui::Button::Ptr option2;
  tgui::Button::Ptr option3;
  tgui::Button::Ptr activeButton = nullptr; // Track the active button

  void createThreeWaySwitch();
  void toggleButtons(tgui::Button::Ptr pressedButton);
  void selectedOption();

  void selectedOption1();
  void selectedOption2();
  void selectedOption3();

  ////////////////////////////////////////////////////////////////////////////////
  // OPTION 1

  std::vector<tgui::Button::Ptr> dynamicButtons;
  std::vector<std::array<tgui::Label::Ptr, 4>> dynamicLabels;

  void createDeleteFlockButton(size_t index);
  void deleteDeleteFlockButton(size_t index);
  void repositionButtons();
  void drawStatistics();

  ////////////////////////////////////////////////////////////////////////////////
  // OPTION 2

  tgui::Slider createSlider(float posX, float posY, float width, float height,
                            int min, int max, int initialValue);

  tgui::Slider::Ptr boidsNumberSlider;
  tgui::Slider::Ptr centerXSlider;
  tgui::Slider::Ptr centerYSlider;
  tgui::Slider::Ptr redSlider;
  tgui::Slider::Ptr greenSlider;
  tgui::Slider::Ptr blueSlider;
  tgui::Button::Ptr addFlockButton;

  tgui::Label::Ptr maxBoidsNumberLabel;
  tgui::Label::Ptr boidsNumberSliderLabel;
  tgui::Label::Ptr centerXSliderLabel;
  tgui::Label::Ptr centerYSliderLabel;
  tgui::Label::Ptr redSliderLabel;
  tgui::Label::Ptr greenSliderLabel;
  tgui::Label::Ptr blueSliderLabel;
  tgui::Label::Ptr addFlockButtonLabel;

  void createBoidsNumberSlider();
  void createCenterXSlider();
  void createCenterYSlider();
  void createRedSlider();
  void createGreenSlider();
  void createBlueSlider();
  void handleSliderChange(tgui::Slider::Ptr changedSlider);
  void createAddFlockButton();
  void enableCreateFlockButton();

  ////////////////////////////////////////////////////////////////////////////////
  // OPTION 3

  tgui::EditBoxSlider::Ptr separationSlider;
  tgui::EditBoxSlider::Ptr separationRangeSlider;
  tgui::EditBoxSlider::Ptr alignmentSlider;
  tgui::EditBoxSlider::Ptr cohesionSlider;
  tgui::EditBoxSlider::Ptr interactionSlider;
  tgui::EditBoxSlider::Ptr repelSlider;
  tgui::EditBoxSlider::Ptr repelRangeSlider;

  tgui::Label::Ptr separationSliderLabel;
  tgui::Label::Ptr separationRangeSliderLabel;
  tgui::Label::Ptr alignmentSliderLabel;
  tgui::Label::Ptr cohesionSliderLabel;
  tgui::Label::Ptr interactionSliderLabel;
  tgui::Label::Ptr repelSliderLabel;
  tgui::Label::Ptr repelRangeSliderLabel;

  void createParametersSliders();

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
};

#endif
