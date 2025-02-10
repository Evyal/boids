#include "egui.hpp"
#include "constants.hpp"
#include "flock.hpp"
#include "graphics.hpp"
#include "random.hpp"
#include "statistics.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/Label.hpp>
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

  // OPTION 2
  createThreeWaySwitch();

  createBoidsNumberSlider();
  boidsNumberSlider->setVisible(false);
  boidsNumberSliderLabel->setVisible(false);
  maxBoidsNumberLabel->setVisible(false);

  createCenterXSlider();
  centerXSlider->setVisible(false);
  centerXSliderLabel->setVisible(false);

  createCenterYSlider();
  centerYSlider->setVisible(false);
  centerYSliderLabel->setVisible(false);

  createRedSlider();
  redSlider->setVisible(false);
  redSliderLabel->setVisible(false);

  createGreenSlider();
  greenSlider->setVisible(false);
  greenSliderLabel->setVisible(false);

  createBlueSlider();
  blueSlider->setVisible(false);
  blueSliderLabel->setVisible(false);

  createAddFlockButton();
  addFlockButton->setVisible(false);
  addFlockButtonLabel->setVisible(false);

  // OPTION 3

  createParametersSliders();

  separationSlider->setVisible(false);
  separationSliderLabel->setVisible(false);

  separationRangeSlider->setVisible(false);
  separationRangeSliderLabel->setVisible(false);

  alignmentSlider->setVisible(false);
  alignmentSliderLabel->setVisible(false);

  cohesionSlider->setVisible(false);
  cohesionSliderLabel->setVisible(false);

  interactionSlider->setVisible(false);
  interactionSliderLabel->setVisible(false);

  repelSlider->setVisible(false);
  repelSliderLabel->setVisible(false);

  repelRangeSlider->setVisible(false);
  repelRangeSliderLabel->setVisible(false);

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

  for (auto &labels : dynamicLabels) {
    for (size_t i{0}; i < 4; i++) {
      labels[i]->setVisible(true);
    }
  }

  for (size_t i = 0; i < dynamicButtons.size(); ++i) {
    dynamicButtons[i]->setVisible(true);
  }
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

  boidsNumberSlider->setVisible(false);
  boidsNumberSliderLabel->setVisible(false);
  maxBoidsNumberLabel->setVisible(false);

  centerXSlider->setVisible(false);
  centerXSliderLabel->setVisible(false);

  centerYSlider->setVisible(false);
  centerYSliderLabel->setVisible(false);

  redSlider->setVisible(false);
  redSliderLabel->setVisible(false);

  greenSlider->setVisible(false);
  greenSliderLabel->setVisible(false);

  blueSlider->setVisible(false);
  blueSliderLabel->setVisible(false);

  addFlockButton->setVisible(false);
  addFlockButtonLabel->setVisible(false);

  // OPTION 3 FALSE

  separationSlider->setVisible(false);
  separationSliderLabel->setVisible(false);

  separationRangeSlider->setVisible(false);
  separationRangeSliderLabel->setVisible(false);

  alignmentSlider->setVisible(false);
  alignmentSliderLabel->setVisible(false);

  cohesionSlider->setVisible(false);
  cohesionSliderLabel->setVisible(false);

  interactionSlider->setVisible(false);
  interactionSliderLabel->setVisible(false);

  repelSlider->setVisible(false);
  repelSliderLabel->setVisible(false);

  repelRangeSlider->setVisible(false);
  repelRangeSliderLabel->setVisible(false);
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
  boidsNumberSlider->setVisible(true);
  boidsNumberSliderLabel->setVisible(true);
  maxBoidsNumberLabel->setVisible(true);

  centerXSlider->setVisible(true);
  centerXSliderLabel->setVisible(true);

  centerYSlider->setVisible(true);
  centerYSliderLabel->setVisible(true);

  redSlider->setVisible(true);
  redSliderLabel->setVisible(true);

  greenSlider->setVisible(true);
  greenSliderLabel->setVisible(true);

  blueSlider->setVisible(true);
  blueSliderLabel->setVisible(true);

  addFlockButton->setVisible(true);
  addFlockButtonLabel->setVisible(true);

  // OPTION 3 FALSE

  separationSlider->setVisible(false);
  separationSliderLabel->setVisible(false);

  separationRangeSlider->setVisible(false);
  separationRangeSliderLabel->setVisible(false);

  alignmentSlider->setVisible(false);
  alignmentSliderLabel->setVisible(false);

  cohesionSlider->setVisible(false);
  cohesionSliderLabel->setVisible(false);

  interactionSlider->setVisible(false);
  interactionSliderLabel->setVisible(false);

  repelSlider->setVisible(false);
  repelSliderLabel->setVisible(false);

  repelRangeSlider->setVisible(false);
  repelRangeSliderLabel->setVisible(false);
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

  boidsNumberSlider->setVisible(false);
  boidsNumberSliderLabel->setVisible(false);
  maxBoidsNumberLabel->setVisible(false);

  centerXSlider->setVisible(false);
  centerXSliderLabel->setVisible(false);

  centerYSlider->setVisible(false);
  centerYSliderLabel->setVisible(false);

  redSlider->setVisible(false);
  redSliderLabel->setVisible(false);

  greenSlider->setVisible(false);
  greenSliderLabel->setVisible(false);

  blueSlider->setVisible(false);
  blueSliderLabel->setVisible(false);

  addFlockButton->setVisible(false);
  addFlockButtonLabel->setVisible(false);

  // OPTION 3 TRUE

  separationSlider->setVisible(true);
  separationSliderLabel->setVisible(true);

  separationRangeSlider->setVisible(true);
  separationRangeSliderLabel->setVisible(true);

  alignmentSlider->setVisible(true);
  alignmentSliderLabel->setVisible(true);

  cohesionSlider->setVisible(true);
  cohesionSliderLabel->setVisible(true);

  interactionSlider->setVisible(true);
  interactionSliderLabel->setVisible(true);

  repelSlider->setVisible(true);
  repelSliderLabel->setVisible(true);

  repelRangeSlider->setVisible(true);
  repelRangeSliderLabel->setVisible(true);
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

void Egui::createSlider(float posX, float posY, float width, float height,
                        int min, int max, int initialValue) {

  auto slider =
      tgui::Slider::create(static_cast<float>(min), static_cast<float>(max));
  slider->setPosition(posX, posY);
  slider->setSize(width, height);
  slider->setValue(static_cast<float>(initialValue));
  gui.add(slider);

  auto label = tgui::Label::create();
  label->setPosition(posX + width + 10, posY - 5);
  label->setText("Value: " + std::to_string(initialValue));
  label->getRenderer()->setTextColor(sf::Color::White);
  gui.add(label);

  slider->onValueChange([label, slider]() {
    label->setText("Value: " +
                   std::to_string(static_cast<int>(slider->getValue())));
  });
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createBoidsNumberSlider() {

  boidsNumberSlider = tgui::Slider::create();
  boidsNumberSlider->setPosition(775, 190); // Set position
  boidsNumberSlider->setSize(250, 20);      // Set width and fixed height
  boidsNumberSlider->setMinimum(5);         // Set minimum value
  boidsNumberSlider->setMaximum(100);       // Set maximum value
  boidsNumberSlider->setValue(10);          // Set initial value
  gui.add(boidsNumberSlider);               // Add the slider to the GUI

  // Create the label for this slider
  boidsNumberSliderLabel = tgui::Label::create();
  boidsNumberSliderLabel->setPosition(775,
                                      160); // Position next to the slider
  boidsNumberSliderLabel->setText("Create N boids: " + std::to_string(10));
  boidsNumberSliderLabel->setTextSize(15);
  boidsNumberSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(boidsNumberSliderLabel); // Add the label to the GUI

  // Connect slider to update the corresponding label
  boidsNumberSlider->onValueChange([this]() {
    boidsNumberSliderLabel->setText(
        "Create N boids: " +
        std::to_string(static_cast<int>(boidsNumberSlider->getValue())));
  });

  maxBoidsNumberLabel = tgui::Label::create();
  maxBoidsNumberLabel->setPosition(775,
                                   115); // Position next to the slider
  maxBoidsNumberLabel->setText("Number of boids: " + std::to_string(10) +
                               "/250");
  maxBoidsNumberLabel->setTextSize(19);
  maxBoidsNumberLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(maxBoidsNumberLabel);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createCenterXSlider() {

  centerXSlider = tgui::Slider::create();
  centerXSlider->setPosition(775, 270);
  centerXSlider->setSize(250, 20);
  centerXSlider->setMinimum(0);
  centerXSlider->setMaximum(720);
  centerXSlider->setValue(360);
  gui.add(centerXSlider);

  centerXSliderLabel = tgui::Label::create();
  centerXSliderLabel->setPosition(775, 240);
  centerXSliderLabel->setText("Center of Spawn X: " + std::to_string(360));
  centerXSliderLabel->setTextSize(15);
  centerXSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(centerXSliderLabel);

  centerXSlider->onValueChange([this]() {
    centerXSliderLabel->setText(
        "Center of Spawn X: " +
        std::to_string(static_cast<int>(centerXSlider->getValue())));
  });
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createCenterYSlider() {

  centerYSlider = tgui::Slider::create();
  centerYSlider->setPosition(775, 330);
  centerYSlider->setSize(250, 20);
  centerYSlider->setMinimum(0);
  centerYSlider->setMaximum(720);
  centerYSlider->setValue(360);
  gui.add(centerYSlider);

  centerYSliderLabel = tgui::Label::create();
  centerYSliderLabel->setPosition(775, 300);
  centerYSliderLabel->setText("Center of Spawn Y: " + std::to_string(360));
  centerYSliderLabel->setTextSize(15);
  centerYSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(centerYSliderLabel);

  centerYSlider->onValueChange([this]() {
    centerYSliderLabel->setText(
        "Center of Spawn Y: " +
        std::to_string(static_cast<int>(centerYSlider->getValue())));
  });
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createRedSlider() {

  redSlider = tgui::Slider::create();
  redSlider->setPosition(775, 410);
  redSlider->setSize(250, 20);
  redSlider->setMinimum(0);
  redSlider->setMaximum(constants::colorSliderMax);
  redSlider->setValue(0);
  redSlider->onValueChange([&]() { handleSliderChange(redSlider); });
  gui.add(redSlider);

  redSliderLabel = tgui::Label::create();
  redSliderLabel->setPosition(775, 380);
  redSliderLabel->setText("Red: " + std::to_string(0));
  redSliderLabel->setTextSize(15);
  redSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(redSliderLabel);

  redSlider->onValueChange([this]() {
    redSliderLabel->setText(
        "Red: " + std::to_string(static_cast<int>(redSlider->getValue())));
  });
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createGreenSlider() {

  greenSlider = tgui::Slider::create();
  greenSlider->setPosition(775, 470);
  greenSlider->setSize(250, 20);
  greenSlider->setMinimum(0);
  greenSlider->setMaximum(constants::colorSliderMax);
  greenSlider->setValue(0);
  greenSlider->onValueChange([&]() { handleSliderChange(greenSlider); });
  gui.add(greenSlider);

  greenSliderLabel = tgui::Label::create();
  greenSliderLabel->setPosition(775, 440);
  greenSliderLabel->setText("Green: " + std::to_string(0));
  greenSliderLabel->setTextSize(15);
  greenSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(greenSliderLabel);

  greenSlider->onValueChange([this]() {
    greenSliderLabel->setText(
        "Green: " + std::to_string(static_cast<int>(greenSlider->getValue())));
  });
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createBlueSlider() {

  blueSlider = tgui::Slider::create();
  blueSlider->setPosition(775, 530);
  blueSlider->setSize(250, 20);
  blueSlider->setMinimum(0);
  blueSlider->setMaximum(constants::colorSliderMax);
  blueSlider->onValueChange([&]() { handleSliderChange(blueSlider); });
  blueSlider->setValue(0);

  gui.add(blueSlider);

  blueSliderLabel = tgui::Label::create();
  blueSliderLabel->setPosition(775, 500);
  blueSliderLabel->setText("Blue: " + std::to_string(0));
  blueSliderLabel->setTextSize(15);
  blueSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(blueSliderLabel);

  blueSlider->onValueChange([this]() {
    blueSliderLabel->setText(
        "Blue: " + std::to_string(static_cast<int>(blueSlider->getValue())));
  });
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::handleSliderChange(tgui::Slider::Ptr changedSlider) {
  int newTotal = static_cast<int>(
      redSlider->getValue() + greenSlider->getValue() + blueSlider->getValue());

  // If the new total exceeds the cap of 510, adjust the current slider's value
  if (newTotal > 510) {
    // Restore the slider's value to prevent exceeding the total cap
    changedSlider->setValue(changedSlider->getValue() -
                            static_cast<float>((newTotal - 510)));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createAddFlockButton() {
  addFlockButton = tgui::Button::create("Create Flock");
  addFlockButton->setPosition(775, 645);
  addFlockButton->setSize(250, 80);
  addFlockButton->getRenderer()->setBackgroundColor(
      sf::Color(128, 128, 128)); // Default "off"
  addFlockButton->getRenderer()->setBackgroundColorHover(
      sf::Color(128, 128, 128)); // Prevent white hover
  addFlockButton->getRenderer()->setBackgroundColorDown(
      sf::Color(255, 255, 204));

  addFlockButton->onPress([this]() {
    addFlock(
        static_cast<size_t>(boidsNumberSlider->getValue()),
        {centerXSlider->getValue() + 15.f, centerYSlider->getValue() + 15.f},
        sf::Color(static_cast<uint8_t>(redSlider->getValue()),
                  static_cast<uint8_t>(greenSlider->getValue()),
                  static_cast<uint8_t>(blueSlider->getValue())));
  });

  gui.add(addFlockButton);

  addFlockButtonLabel = tgui::Label::create(
      "Number of flocks: " + std::to_string(flockStack_.size()) + "/5");
  addFlockButtonLabel->setPosition(775, 600);
  addFlockButtonLabel->setSize(250, 40);
  addFlockButtonLabel->setTextSize(20);
  addFlockButtonLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(addFlockButtonLabel); // Add the label to the GUI
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::enableCreateFlockButton() {
  if (flockStack_.size() == 5 || getActiveBoids() > 245) {
    boidsNumberSlider->setMaximum(5);
    boidsNumberSlider->setEnabled(false);
    boidsNumberSliderLabel->setText("Create N boids: Disabled");
    maxBoidsNumberLabel->setText(
        "Number of boids: " + std::to_string(getActiveBoids()) + "/250");

    addFlockButton->setEnabled(false);

  } else if (getActiveBoids() > 150) {
    boidsNumberSlider->setMaximum(250 - static_cast<float>(getActiveBoids()));
    boidsNumberSlider->setEnabled(true);
    boidsNumberSliderLabel->setText(
        "Create N boids: " +
        std::to_string(static_cast<int>(boidsNumberSlider->getValue())));
    maxBoidsNumberLabel->setText(
        "Number of boids: " + std::to_string(getActiveBoids()) + "/250");

    addFlockButton->setEnabled(true);

  } else {
    boidsNumberSlider->setMaximum(100);
    boidsNumberSlider->setEnabled(true);
    boidsNumberSliderLabel->setText(
        "Create N boids: " +
        std::to_string(static_cast<int>(boidsNumberSlider->getValue())));
    maxBoidsNumberLabel->setText(
        "Number of boids: " + std::to_string(getActiveBoids()) + "/250");

    addFlockButton->setEnabled(true);
  }

  assert(flockStack_.size() < 6);
  assert(getActiveBoids() <= 250);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// OPTION 3

void Egui::createParametersSliders() {
  separationSlider = tgui::EditBoxSlider::create();
  separationSlider->setPosition(775, 150);
  separationSlider->setSize(250, 20);
  separationSlider->setMinimum(0);
  separationSlider->setMaximum(constants::maxSeparationStrength * 1000);
  separationSlider->setValue(constants::defaultSeparationStrenght * 1000);
  separationSlider->setStep(0.1f);
  gui.add(separationSlider);

  separationSliderLabel = tgui::Label::create();
  separationSliderLabel->setPosition(775, 120);
  separationSliderLabel->setText("Separation Strenght");
  separationSliderLabel->setTextSize(15);
  separationSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(separationSliderLabel);

  //////////////////////////////////////////////////////////////////////////////////////////

  separationRangeSlider = tgui::EditBoxSlider::create();
  separationRangeSlider->setPosition(775, 210);
  separationRangeSlider->setSize(250, 20);
  separationRangeSlider->setMinimum(0);
  separationRangeSlider->setMaximum(constants::maxSeparationRange);
  separationRangeSlider->setValue(constants::defaultSeparationRange);
  gui.add(separationRangeSlider);

  separationRangeSliderLabel = tgui::Label::create();
  separationRangeSliderLabel->setPosition(775, 180);
  separationRangeSliderLabel->setText("Separation Range");
  separationRangeSliderLabel->setTextSize(15);
  separationRangeSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(separationRangeSliderLabel);

  //////////////////////////////////////////////////////////////////////////////////////////

  alignmentSlider = tgui::EditBoxSlider::create();
  alignmentSlider->setPosition(775, 270);
  alignmentSlider->setSize(250, 20);
  alignmentSlider->setMinimum(0);
  alignmentSlider->setMaximum(constants::maxAlignmentStrength * 1000);
  alignmentSlider->setValue(constants::defaultAlignmentStrenght * 1000);
  gui.add(alignmentSlider);

  alignmentSliderLabel = tgui::Label::create();
  alignmentSliderLabel->setPosition(775, 240);
  alignmentSliderLabel->setText("Alignment Strenght");
  alignmentSliderLabel->setTextSize(15);
  alignmentSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(alignmentSliderLabel);

  //////////////////////////////////////////////////////////////////////////////////////////

  cohesionSlider = tgui::EditBoxSlider::create();
  cohesionSlider->setPosition(775, 330);
  cohesionSlider->setSize(250, 20);
  cohesionSlider->setMinimum(0);
  cohesionSlider->setMaximum(constants::maxCohesionStrength * 1000);
  cohesionSlider->setValue(constants::defaultCohesionStrenght * 1000);
  gui.add(cohesionSlider);

  cohesionSliderLabel = tgui::Label::create();
  cohesionSliderLabel->setPosition(775, 300);
  cohesionSliderLabel->setText("Cohesion Strenght");
  cohesionSliderLabel->setTextSize(15);
  cohesionSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(cohesionSliderLabel);

  //////////////////////////////////////////////////////////////////////////////////////////

  interactionSlider = tgui::EditBoxSlider::create();
  interactionSlider->setPosition(775, 390);
  interactionSlider->setSize(250, 20);
  interactionSlider->setMinimum(0);
  interactionSlider->setMaximum(constants::maxInteractionRange);
  interactionSlider->setValue(constants::defaultInteractionRange);
  gui.add(interactionSlider);

  interactionSliderLabel = tgui::Label::create();
  interactionSliderLabel->setPosition(775, 360);
  interactionSliderLabel->setText("Interaction Range");
  interactionSliderLabel->setTextSize(15);
  interactionSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(interactionSliderLabel);

  //////////////////////////////////////////////////////////////////////////////////////////

  repelSlider = tgui::EditBoxSlider::create();
  repelSlider->setPosition(775, 450);
  repelSlider->setSize(250, 20);
  repelSlider->setMinimum(0);
  repelSlider->setMaximum(constants::maxRepelStrenght * 1000);
  repelSlider->setValue(constants::defaultRepelStrenght * 1000);
  gui.add(repelSlider);

  repelSliderLabel = tgui::Label::create();
  repelSliderLabel->setPosition(775, 420);
  repelSliderLabel->setText("Repel Strenght");
  repelSliderLabel->setTextSize(15);
  repelSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(repelSliderLabel);

  //////////////////////////////////////////////////////////////////////////////////////////

  repelRangeSlider = tgui::EditBoxSlider::create();
  repelRangeSlider->setPosition(775, 510);
  repelRangeSlider->setSize(250, 20);
  repelRangeSlider->setMinimum(0);
  repelRangeSlider->setMaximum(constants::maxRepelRange);
  repelRangeSlider->setValue(constants::defaultRepelRange);
  gui.add(repelRangeSlider);

  repelRangeSliderLabel = tgui::Label::create();
  repelRangeSliderLabel->setPosition(775, 480);
  repelRangeSliderLabel->setText("Repel range");
  repelRangeSliderLabel->setTextSize(15);
  repelRangeSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(repelRangeSliderLabel);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// Draw Interface

void Egui::drawInterface() {
  sf::RectangleShape topField(sf::Vector2f(750, 15));
  topField.setPosition(0, 0);
  topField.setFillColor(sf::Color::Black);
  sf::RectangleShape bottomField(sf::Vector2f(750, 15));
  bottomField.setPosition(0, 735);
  bottomField.setFillColor(sf::Color::Black);
  sf::RectangleShape leftField(sf::Vector2f(15, 720));
  leftField.setPosition(0, 15);
  leftField.setFillColor(sf::Color::Black);
  sf::RectangleShape rightField(sf::Vector2f(15, 720));
  rightField.setPosition(735, 15);
  rightField.setFillColor(sf::Color::Black);

  window.draw(topField);
  window.draw(bottomField);
  window.draw(leftField);
  window.draw(rightField);

  sf::RectangleShape topSettings(sf::Vector2f(290, 5));
  topSettings.setPosition(755, 5);
  topSettings.setFillColor(sf::Color::Black);
  sf::RectangleShape bottomSettings(sf::Vector2f(290, 5));
  bottomSettings.setPosition(755, 740);
  bottomSettings.setFillColor(sf::Color::Black);
  sf::RectangleShape leftSettings(sf::Vector2f(5, 740));
  leftSettings.setPosition(755, 5);
  leftSettings.setFillColor(sf::Color::Black);
  sf::RectangleShape rightSettings(sf::Vector2f(5, 740));
  rightSettings.setPosition(1040, 5);
  rightSettings.setFillColor(sf::Color::Black);

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
        flockStack_[i].Separation(separationSlider->getValue() / 1000,
                                  separationRangeSlider->getValue()),
        flockStack_[i].Alignment(alignmentSlider->getValue() / 1000,
                                 interactionSlider->getValue()),
        flockStack_[i].Cohesion(cohesionSlider->getValue() / 1000,
                                interactionSlider->getValue()),
        Repel(flockStack_, i, repelSlider->getValue() / 1000,
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
  flockSize.setOrigin(10,10);
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