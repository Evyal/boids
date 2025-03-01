#include "egui.hpp"
#include "constants.hpp"
#include "flock.hpp"
#include "graphics.hpp"
#include "random.hpp"
#include "statistics.hpp"
#include "structs.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Slider.hpp>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

bool toroidal{false};

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Egui::Egui() : window(sf::VideoMode(1050, 750), "Egui"), gui(window) {}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::setup() {

  sans.loadFromFile("../OpenSans-Regular.ttf");

  createSwitchButton();
  createThreeWaySwitch();

  // OPTION 1

  for (auto &labels : dynamicLabels) {
    for (size_t i{0}; i < 4; i++) {
      labels[i]->setVisible(true);
    }
  }

  for (size_t i = 0; i < dynamicButtons.size(); ++i) {
    dynamicButtons[i]->setVisible(true);
  }

  // OPTION 2

  setupOpt2();

  // OPTION 3

  setupOpt3();

  // GENERATE FLOCKS at the BEGINNING

  addFlock(10, {randomFloat(15, 735), randomFloat(15, 735)},
           sf::Color{255, 0, 127}); // PINK
  addFlock(20, {randomFloat(15, 735), randomFloat(15, 735)},
           sf::Color{255, 0, 0}); // RED
  addFlock(30, {randomFloat(15, 735), randomFloat(15, 735)},
           sf::Color{255, 204, 0}); // YELLOW
  addFlock(40, {randomFloat(15, 735), randomFloat(15, 735)},
           sf::Color{153, 255, 51}); // GREEN
  addFlock(50, {randomFloat(15, 735), randomFloat(15, 735)},
           sf::Color{0, 204, 204}); // CYAN
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::run() {

  window.setPosition({120, 50});
  window.setFramerateLimit(50);
  sf::Event event;

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      gui.handleEvent(event);
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      default:
        break;
      }
    }

    evolveFlock();

    window.clear(sf::Color::White);

    drawFlocks();

    enableCreateFlockButton();
    drawInterface();
    selectedOption();

    gui.draw();
    window.display();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// Sets up the GUI components

void Egui::createSwitchButton() {
  switchButton = tgui::Button::create("Mirror Mode");
  switchButton->setPosition(770, 80);
  switchButton->setSize(260, 50);
  switchButton->getRenderer()->setBackgroundColor(sf::Color(153, 255, 255));
  switchButton->getRenderer()->setBackgroundColorHover(
      sf::Color(204, 255, 255));
  switchButton->getRenderer()->setBackgroundColorDown(sf::Color(204, 255, 255));

  // Attach the toggleSwitch action to the button
  switchButton->onPress([this]() { toggleSwitch(); });

  gui.add(switchButton);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::toggleSwitch() {
  isSwitchOn = !isSwitchOn;

  if (isSwitchOn) {
    switchButton->setText("Toroidal Mode");
    switchButton->getRenderer()->setBackgroundColor(sf::Color(204, 255, 153));
    switchButton->getRenderer()->setBackgroundColorHover(
        sf::Color(229, 255, 204));
    switchButton->getRenderer()->setBackgroundColorDown(
        sf::Color(229, 255, 204));
    toroidal = true;
  } else {
    switchButton->setText("Mirror Mode");
    switchButton->getRenderer()->setBackgroundColor(sf::Color(153, 255, 255));
    switchButton->getRenderer()->setBackgroundColorHover(
        sf::Color(204, 255, 255));
    switchButton->getRenderer()->setBackgroundColorDown(
        sf::Color(204, 255, 255));
    toroidal = false;
  }

  // Add any action to perform when the switch is toggled
  //   std::cout << "Switch state: " << (isSwitchOn ? "ON" : "OFF") <<
  //   std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createThreeWaySwitch() {
  // Button 1
  option1 = tgui::Button::create("Statistics");
  option1->setPosition(770, 20);
  option1->setSize(80, 50);
  option1->getRenderer()->setBackgroundColor(
      sf::Color(255, 255, 160)); // Default "on"
  option1->getRenderer()->setBackgroundColorHover(
      sf::Color(255, 255, 160)); // Prevent white hover
  option1->getRenderer()->setBackgroundColorDown(sf::Color(160, 160, 160));

  option1->onPress([this]() {
    toggleButtons(option1);
    selectedOption1();
  });

  activeButton = option1;
  gui.add(option1);

  // Button 2
  option2 = tgui::Button::create("Create flock");
  option2->setPosition(860, 20);
  option2->setSize(80, 50);
  option2->getRenderer()->setBackgroundColor(
      sf::Color(128, 128, 128)); // Default "off"
  option2->getRenderer()->setBackgroundColorHover(
      sf::Color(190, 190, 190)); // Prevent white hover
  option2->getRenderer()->setBackgroundColorDown(sf::Color(160, 160, 160));

  option2->onPress([this]() {
    toggleButtons(option2);
    selectedOption2();
  });

  gui.add(option2);

  // Button 3
  option3 = tgui::Button::create("Set\n"
                                 "parameters");
  option3->setPosition(950, 20);
  option3->setSize(80, 50);
  option3->getRenderer()->setBackgroundColor(
      sf::Color(128, 128, 128)); // Default "off"
  option3->getRenderer()->setBackgroundColorHover(
      sf::Color(190, 190, 190)); // Prevent white hover
  option3->getRenderer()->setBackgroundColorDown(sf::Color(160, 160, 160));

  option3->onPress([this]() {
    toggleButtons(option3);
    selectedOption3();
  });

  gui.add(option3);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::toggleButtons(tgui::Button::Ptr pressedButton) {
  // Set all buttons to "off" (gray background)
  option1->getRenderer()->setBackgroundColor(sf::Color(128, 128, 128));
  option2->getRenderer()->setBackgroundColor(sf::Color(128, 128, 128));
  option3->getRenderer()->setBackgroundColor(sf::Color(128, 128, 128));
  option1->getRenderer()->setBackgroundColorHover(
      sf::Color(190, 190, 190)); // Prevent white hover
  option2->getRenderer()->setBackgroundColorHover(
      sf::Color(190, 190, 190)); // Prevent white hover
  option3->getRenderer()->setBackgroundColorHover(
      sf::Color(190, 190, 190)); // Prevent white hover

  // Set the active button to "on" (green background)
  pressedButton->getRenderer()->setBackgroundColor(sf::Color(255, 255, 160));
  pressedButton->getRenderer()->setBackgroundColorHover(
      sf::Color(255, 255, 160));

  activeButton = pressedButton;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Updates CONTINUOUSLY to the SELECTED OPTION

void Egui::selectedOption() {
  if (activeButton == option1) {
    drawStatistics();

  } else if (activeButton == option2) {

  } else if (activeButton == option3) {
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::selectedOption1() {
  // OPTION 1 TRUE

  switchButton->setVisible(true);

  for (size_t i = 0; i < dynamicButtons.size(); ++i) {
    dynamicButtons[i]->setVisible(true);
  }

  for (auto &labels : dynamicLabels) {
    for (size_t i{0}; i < 4; i++) {
      labels[i]->setVisible(true);
    }
  }

  // OPTION 2 FALSE

  setVisibleOpt2(false);

  // OPTION 3 FALSE

  setVisibleOpt3(false);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::selectedOption2() {
  // OPTION 1 FALSE
  switchButton->setVisible(false);

  for (size_t i = 0; i < dynamicButtons.size(); ++i) {
    dynamicButtons[i]->setVisible(false);
  }

  for (auto &labels : dynamicLabels) {
    for (size_t i{0}; i < 4; i++) {
      labels[i]->setVisible(false);
    }
  }

  // OPTION 2 TRUE

  setVisibleOpt2(true);

  // OPTION 3 FALSE

  setVisibleOpt3(false);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::selectedOption3() {
  // OPTION 1 FALSE
  switchButton->setVisible(false);

  for (size_t i = 0; i < dynamicButtons.size(); ++i) {
    dynamicButtons[i]->setVisible(false);
  }

  for (auto &labels : dynamicLabels) {
    for (size_t i{0}; i < 4; i++) {
      labels[i]->setVisible(false);
    }
  }

  // OPTION 2 FALSE

  setVisibleOpt2(false);

  // OPTION 3 TRUE

  setVisibleOpt3(true);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// OPTION 1

void Egui::drawStatistics() {
  for (unsigned i{0}; i < flockStack_.size(); i++) {
    sf::RectangleShape rectangle1(sf::Vector2f(260, 110));
    rectangle1.setPosition(770, 140 + static_cast<float>(i) * 120);
    rectangle1.setFillColor(sf::Color::Black);
    window.draw(rectangle1);

    sf::RectangleShape rectangle(sf::Vector2f(250, 100));
    rectangle.setPosition(775, 145 + static_cast<float>(i) * 120);
    window.draw(rectangle);

    sf::RectangleShape rectangle2(sf::Vector2f(15, 90));
    rectangle2.setPosition(765, 150 + static_cast<float>(i) * 120);
    rectangle2.setFillColor(flockStack_[i].getFlockColor());
    window.draw(rectangle2);

    // sf::CircleShape circleBlack(18);
    // circleBlack.setOrigin(18, 18);
    // circleBlack.setPosition(805, 195 + static_cast<float>(i) * 120);
    // circleBlack.setFillColor(sf::Color::Black);
    // window.draw(circleBlack);

    // sf::CircleShape circle(17);
    // circle.setOrigin(17, 17);
    // circle.setPosition(805, 195 + static_cast<float>(i) * 120);
    // circle.setFillColor(flockStack_[i].getFlockColor());
    // window.draw(circle);

    printFlock(i);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createDeleteFlockButton(size_t index) {
  auto button = tgui::Button::create(std::to_string(index + 1));
  button->setPosition(1020, 185 + index * 120);
  button->setSize(15, 15);
  button->getRenderer()->setBackgroundColor(sf::Color::Red);
  button->onPress([this, index = dynamicButtons.size()]() {
    std::cout << "Button " << index + 1 << " pressed!\n";
    deleteFlock(index);
    deleteDeleteFlockButton(index);
  });

  gui.add(button);
  dynamicButtons.push_back(button);

  auto label0 = tgui::Label::create("Mean Distance: ");
  label0->setTextSize(15);
  label0->setPosition({825, 150 + index * 120});
  gui.add(label0);

  auto label1 = tgui::Label::create("Distance std dev: ");
  label1->setTextSize(15);
  label1->setPosition({825, 170 + index * 120});
  gui.add(label1);

  auto label2 = tgui::Label::create("Mean Speed: ");
  label2->setTextSize(15);
  label2->setPosition({825, 200 + index * 120});
  gui.add(label2);

  auto label3 = tgui::Label::create("Speed std dev: ");
  label3->setTextSize(15);
  label3->setPosition({825, 220 + index * 120});
  gui.add(label3);

  dynamicLabels.push_back({label0, label1, label2, label3});
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::deleteDeleteFlockButton(size_t index) {
  if (index >= static_cast<size_t>(dynamicButtons.size())) {
    std::cout << "Invalid button index: " << index << "\n";
    return;
  }

  // Remove the button from GUI and erase it from the vector
  gui.remove(dynamicButtons[index]);
  dynamicButtons.erase(dynamicButtons.begin() + static_cast<long>(index));

  for (size_t i{0}; i < 4; i++) {
    gui.remove(dynamicLabels[index][i]);
  }
  dynamicLabels.erase(dynamicLabels.begin() + static_cast<long>(index));

  // Reposition the remaining buttons
  if (dynamicButtons.size() > 0) {
    repositionButtons();
  }

  // std::cout << "Button " << index + 1 << " removed successfully.\n";
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::repositionButtons() {
  for (size_t i = 0; i < dynamicButtons.size(); ++i) {
    dynamicButtons[i]->setText(std::to_string(i + 1));
    dynamicButtons[i]->setPosition(1020, 185 + i * 120);
    dynamicButtons[i]->onPress.disconnectAll();
    dynamicButtons[i]->onPress([this, index = i]() {
      // std::cout << "Button " << index + 1 << " pressed!\n";
      deleteFlock(index);
      deleteDeleteFlockButton(index);
    });

    // CREATE CONSTANTS, please

    dynamicLabels[i][0]->setPosition({825, 150 + i * 120});
    dynamicLabels[i][1]->setPosition({825, 170 + i * 120});
    dynamicLabels[i][2]->setPosition({825, 200 + i * 120});
    dynamicLabels[i][3]->setPosition({825, 220 + i * 120});
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// OPTION 2

void Egui::createSliderOpt2(const SlidersParameters &sliderPar) {

  auto slider = tgui::Slider::create(static_cast<float>(sliderPar.min),
                                     static_cast<float>(sliderPar.max));
  slider->setPosition(sliderPar.posX, sliderPar.posY);
  slider->setSize(sliderPar.width, sliderPar.height);
  slider->setValue(static_cast<float>(sliderPar.initialValue));
  gui.add(slider);

  option2Sliders.emplace_back(slider);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createLabelOpt2(const LabelsParameters &labelsPar) {

  auto label = tgui::Label::create();
  label->setPosition(labelsPar.posX, labelsPar.posY);
  label->getRenderer()->setTextColor(sf::Color::White);
  label->setTextSize(labelsPar.textSize);
  label->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(label);

  option2Labels.emplace_back(label);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::setLabelTextOpt2(size_t i, const std::string &text) {
  option2Labels[i]->setText(
      text + std::to_string(static_cast<int>(option2Sliders[i]->getValue())));

  option2Sliders[i]->onValueChange([this, i, text]() {
    option2Labels[i]->setText(
        text + std::to_string(static_cast<int>(option2Sliders[i]->getValue())));
  });
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::setupOpt2() {
  createSliderOpt2(constants::boidsNumberSlider);
  createSliderOpt2(constants::centerXSlider);
  createSliderOpt2(constants::centerYSlider);
  createSliderOpt2(constants::redSlider);
  createSliderOpt2(constants::greenSlider);
  createSliderOpt2(constants::blueSlider);

  createLabelOpt2(constants::boidsNumberSliderLabel);
  createLabelOpt2(constants::centerXSliderLabel);
  createLabelOpt2(constants::centerYSliderLabel);
  createLabelOpt2(constants::redSliderLabel);
  createLabelOpt2(constants::greenSliderLabel);
  createLabelOpt2(constants::blueSliderLabel);
  createLabelOpt2(constants::maxBoidsNumberLabel); // INDEX 6

  // VALUE SHOULD CHANGE when FLOCK are created or destructed
  option2Labels[6]->setText("Number of boids: " + std::to_string(10) + "/250");

  setLabelTextOpt2(0, "Create N boids: ");
  setLabelTextOpt2(1, "Center of Spawn X: ");
  setLabelTextOpt2(2, "Center of Spawn Y: ");
  setLabelTextOpt2(3, "Red: ");
  setLabelTextOpt2(4, "Green: ");
  setLabelTextOpt2(5, "Blue: ");

  // HANDLE MAXIMUM VALUE of COLOUR SLIDERS
  option2Sliders[3]->onValueChange(
      [&]() { handleColorSliderChange(option2Sliders[3]); });
  option2Sliders[4]->onValueChange(
      [&]() { handleColorSliderChange(option2Sliders[4]); });
  option2Sliders[5]->onValueChange(
      [&]() { handleColorSliderChange(option2Sliders[5]); });

  createAddFlockButton(constants::addFlockButton);
  createLabelOpt2(constants::addFlockButtonLabel); // LABEL with INDEX 7
  addFlockButtonLabel = option2Labels[7];
  addFlockButtonLabel->setText(
      "Number of flocks: " + std::to_string(flockStack_.size()) + "/5");

  setVisibleOpt2(false);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::setVisibleOpt2(bool visible) {
  for (auto &i : option2Sliders) {
    i->setVisible(visible);
  }
  for (auto &i : option2Labels) {
    i->setVisible(visible);
  }
  addFlockButton->setVisible(visible);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::handleColorSliderChange(tgui::Slider::Ptr changedSlider) {
  int newTotal = static_cast<int>(option2Sliders[3]->getValue() +
                                  option2Sliders[4]->getValue() +
                                  option2Sliders[5]->getValue());

  // 3 is RED, 4 is GREEN, 5 is BLUE

  // If the new total exceeds the cap of 510, adjust the current slider's value
  if (newTotal > 510) {
    // Restore the slider's value to prevent exceeding the total cap
    changedSlider->setValue(changedSlider->getValue() -
                            static_cast<float>((newTotal - 510)));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createAddFlockButton(const TguiParameters &par) {
  addFlockButton = tgui::Button::create("Create Flock");
  addFlockButton->setPosition(par.posX, par.posY);
  addFlockButton->setSize(par.width, par.height);
  addFlockButton->getRenderer()->setBackgroundColor(
      sf::Color(128, 128, 128)); // Default "off"
  addFlockButton->getRenderer()->setBackgroundColorHover(
      sf::Color(128, 128, 128)); // Prevent white hover
  addFlockButton->getRenderer()->setBackgroundColorDown(
      sf::Color(255, 255, 204));

  addFlockButton->onPress([this]() {
    addFlock(static_cast<size_t>(option2Sliders[0]->getValue()),
             {option2Sliders[1]->getValue() + constants::marginSize,
              option2Sliders[2]->getValue() + constants::marginSize},
             sf::Color(static_cast<uint8_t>(option2Sliders[3]->getValue()),
                       static_cast<uint8_t>(option2Sliders[4]->getValue()),
                       static_cast<uint8_t>(option2Sliders[5]->getValue())));
  });

  gui.add(addFlockButton);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::enableCreateFlockButton() {
  if (flockStack_.size() == 5 || getActiveBoids() > 245) {

    // index 0 is boids number
    // index 6 is boids max number

    // option2Sliders[0]->setMaximum(5);
    option2Sliders[0]->setEnabled(false);

    option2Labels[0]->setText("Create N boids: Disabled");
    option2Labels[6]->setText(
        "Number of boids: " + std::to_string(getActiveBoids()) + "/250");

    addFlockButton->setEnabled(false);

  } else if (getActiveBoids() > 150) {
    option2Sliders[0]->setMaximum(250 - static_cast<float>(getActiveBoids()));
    option2Sliders[0]->setEnabled(true);
    option2Labels[0]->setText(
        "Create N boids: " +
        std::to_string(static_cast<int>(option2Sliders[0]->getValue())));
    option2Labels[6]->setText(
        "Number of boids: " + std::to_string(getActiveBoids()) + "/250");

    addFlockButton->setEnabled(true);

  } else {
    option2Sliders[0]->setMaximum(100);
    option2Sliders[0]->setEnabled(true);

    option2Labels[0]->setText(
        "Create N boids: " +
        std::to_string(static_cast<int>(option2Sliders[0]->getValue())));
    option2Labels[6]->setText(
        "Number of boids: " + std::to_string(getActiveBoids()) + "/250");

    addFlockButton->setEnabled(true);
  }

  assert(flockStack_.size() < 6);
  assert(getActiveBoids() <= 250);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// OPTION 3

void Egui::createSliderOpt3(const SlidersParameters &params) {
  auto slider = tgui::EditBoxSlider::create();
  slider->setPosition(params.posX, params.posY);
  slider->setSize(params.width, params.height);
  slider->setMinimum(params.min);
  slider->setMaximum(params.max);
  slider->setValue(params.initialValue);

  gui.add(slider);

  option3Sliders.emplace_back(slider);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createLabelOpt3(const LabelsParameters &labelsPar,
                           const std::string &text) {

  auto label = tgui::Label::create();
  label->setPosition(labelsPar.posX, labelsPar.posY);
  label->setTextSize(labelsPar.textSize);
  label->getRenderer()->setTextColor(sf::Color::Black);
  label->setText(text);
  gui.add(label);

  option3Labels.emplace_back(label);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::setupOpt3() {
  createSliderOpt3(constants::separationSlider);
  createSliderOpt3(constants::separationRangeSlider);
  createSliderOpt3(constants::alignmentSlider);
  createSliderOpt3(constants::cohesionSlider);
  createSliderOpt3(constants::interactionSlider);
  createSliderOpt3(constants::repelSlider);
  createSliderOpt3(constants::repelRangeSlider);

  createLabelOpt3(constants::separationSliderLabel, "Separation Strenght");
  createLabelOpt3(constants::separationRangeSliderLabel, "Separation Range");
  createLabelOpt3(constants::alignmentSliderLabel, "Alignment Strenght");
  createLabelOpt3(constants::cohesionSliderLabel, "Cohesion Strenght");
  createLabelOpt3(constants::interactionSliderLabel, "Interaction Range");
  createLabelOpt3(constants::repelSliderLabel, "Repel Strenght");
  createLabelOpt3(constants::repelRangeSliderLabel, "Repel Range");

  separationSlider = option3Sliders[0];
  separationRangeSlider = option3Sliders[1];
  alignmentSlider = option3Sliders[2];
  cohesionSlider = option3Sliders[3];
  interactionSlider = option3Sliders[4];
  repelSlider = option3Sliders[5];
  repelRangeSlider = option3Sliders[6];

  setVisibleOpt3(false);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::setVisibleOpt3(bool visible) {
  for (auto &i : option3Sliders) {
    i->setVisible(visible);
  }
  for (auto &i : option3Labels) {
    i->setVisible(visible);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// Draw Interface

void Egui::drawInterface() {
  sf::RectangleShape topField(drawRectangle(constants::topMargin));
  sf::RectangleShape bottomField(drawRectangle(constants::bottomMargin));
  sf::RectangleShape leftField(drawRectangle(constants::leftMargin));
  sf::RectangleShape rightField(drawRectangle(constants::rightMargin));

  window.draw(topField);
  window.draw(bottomField);
  window.draw(leftField);
  window.draw(rightField);

  sf::RectangleShape topSettings(drawRectangle(constants::topSettingMargin));
  sf::RectangleShape bottomSettings(drawRectangle(constants::topSettingMargin));
  sf::RectangleShape leftSettings(drawRectangle(constants::topSettingMargin));
  sf::RectangleShape rightSettings(drawRectangle(constants::topSettingMargin));

  window.draw(topSettings);
  window.draw(bottomSettings);
  window.draw(leftSettings);
  window.draw(rightSettings);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void Egui::addFlock(size_t n, sf::Vector2f center, sf::Color color) {
  if (flockStack_.size() < constants::maxFlockNumber) {
    flockStack_.emplace_back(createFlock(n, center, color));
    createDeleteFlockButton(flockStack_.size() - 1);
    addFlockButtonLabel->setText(
        "Number of flocks: " + std::to_string(flockStack_.size()) + "/5");

    for (auto &labels : dynamicLabels) {
      for (size_t i{0}; i < 4; i++) {
        labels[i]->setVisible(false);
      }
    }

    for (size_t i = 0; i < dynamicButtons.size(); ++i) {
      dynamicButtons[i]->setVisible(false);
    }

  } else {
    std::cout << "There are already 5 flocks!\n";
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::deleteFlock(size_t i) {
  flockStack_.erase(flockStack_.begin() + static_cast<long>(i));
  addFlockButtonLabel->setText(
      "Number of flocks: " + std::to_string(flockStack_.size()) + "/5");
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::evolveFlock() {
  bodyStack_.resize(flockStack_.size());
  for (size_t i{0}; i < flockStack_.size(); i++) {
    flockStack_[i].updateFlock(
        flockStack_[i].Separation(separationSlider->getValue() /
                                      constants::scalingFactor,
                                  separationRangeSlider->getValue()),
        flockStack_[i].Alignment(alignmentSlider->getValue() /
                                     constants::scalingFactor,
                                 interactionSlider->getValue()),
        flockStack_[i].Cohesion(cohesionSlider->getValue() /
                                    constants::scalingFactor,
                                interactionSlider->getValue()),
        Repel(flockStack_, i,
              repelSlider->getValue() / constants::scalingFactor,
              repelRangeSlider->getValue()));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::drawFlocks() {
  for (size_t i{0}; i < bodyStack_.size(); i++) {
    bodyStack_[i].clear();
    sf::Color color{flockStack_[i].getFlockColor()};

    for (size_t j{0}; j < flockStack_[i].getSize(); j++) {
      bodyStack_[i].emplace_back(
          drawTriangleBoid(flockStack_[i].getBoid(j), color));
      window.draw(bodyStack_[i][j]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::printFlock(size_t i) {

  sf::Text flockSize;

  flockSize.setString(
      std::to_string(static_cast<int>(flockStack_[i].getSize())));
  flockSize.setFont(sans);
  flockSize.setCharacterSize(20);
  flockSize.setOrigin(10, 10);
  flockSize.setFillColor(sf::Color::Black);
  flockSize.setPosition(800, 190 + static_cast<float>(i) * 120);

  window.draw(flockSize);

  sf::Text meanDistance;

  float meanDistanceValue{
      calculateMean(calculateDistances(flockStack_[i].getFlockPositions()))};
  meanDistance.setString(std::to_string(static_cast<int>(meanDistanceValue)));
  meanDistance.setFont(sans);
  meanDistance.setCharacterSize(20);
  meanDistance.setFillColor(sf::Color::Black);
  meanDistance.setPosition(975, 145.f + static_cast<float>(i) * 120);

  window.draw(meanDistance);

  sf::Text standardDeviation;

  standardDeviation.setString(
      std::to_string(static_cast<int>(calculateStandardDeviation(
          calculateDistances(flockStack_[i].getFlockPositions()),
          meanDistanceValue))));
  standardDeviation.setFont(sans);
  standardDeviation.setCharacterSize(20);
  standardDeviation.setFillColor(sf::Color::Black);
  standardDeviation.setPosition(975, 165.f + static_cast<float>(i) * 120);

  window.draw(standardDeviation);

  sf::Text meanSpeed;

  float meanSpeedValue{flockStack_[i].getMeanSpeed()};
  meanSpeed.setString(std::to_string(static_cast<int>(meanSpeedValue)));
  meanSpeed.setFont(sans);
  meanSpeed.setCharacterSize(20);
  meanSpeed.setFillColor(sf::Color::Black);
  meanSpeed.setPosition(975, 195.f + static_cast<float>(i) * 120);

  window.draw(meanSpeed);

  sf::Text SpeedStandardDeviation;

  SpeedStandardDeviation.setString(
      std::to_string(static_cast<int>(calculateStandardDeviation(
          flockStack_[i].getSpeedVector(), meanSpeedValue))));
  SpeedStandardDeviation.setFont(sans);
  SpeedStandardDeviation.setCharacterSize(20);
  SpeedStandardDeviation.setFillColor(sf::Color::Black);
  SpeedStandardDeviation.setPosition(975, 215.f + static_cast<float>(i) * 120);

  window.draw(SpeedStandardDeviation);
}

//////////////////////////////////////////////////////////////////////////////////////////

size_t Egui::getActiveBoids() {
  size_t activeBoids{};
  for (const auto &flock : flockStack_) {
    activeBoids += flock.getSize();
  }
  return activeBoids;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////