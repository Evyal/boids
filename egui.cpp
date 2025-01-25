#include "egui.hpp"
#include "constants.hpp"
#include "control.hpp"
#include "flock.hpp"
#include "graphics.hpp"
#include <SFML/Graphics/Color.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <cstddef>
#include <cstdint>
#include <string>

extern float separation;
extern float separationRange;
extern float alignment;
extern float cohesion;
extern float repel;
extern float repelRange;
extern bool toroidal;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Egui::Egui() : window(sf::VideoMode(1050, 750), "Egui"), gui(window) {}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::setup() {
  createThreeWaySwitch();

  createBoidsNumberSlider();
  boidsNumberSlider->setVisible(false);
  boidsNumberSliderLabel->setVisible(false);

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

  addFlock();
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

    if (flockStack_.size() == 5) {
      addFlockButton->setEnabled(false);
    } else {
      addFlockButton->setEnabled(true);
    }

    window.clear(sf::Color::White);
    evolveFlock();
    drawInterface();
    selectedOption();

    gui.draw();
    window.display();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// Sets up the GUI components

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

    boidsNumberSlider->setVisible(false);
    boidsNumberSliderLabel->setVisible(false);

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
  });

  activeButton = option1;
  gui.add(option1);

  // Button 2
  option2 = tgui::Button::create("Edit flocks");
  option2->setPosition(860, 20);
  option2->setSize(80, 50);
  option2->getRenderer()->setBackgroundColor(
      sf::Color(128, 128, 128)); // Default "off"
  option2->getRenderer()->setBackgroundColorHover(
      sf::Color(190, 190, 190)); // Prevent white hover
  option2->getRenderer()->setBackgroundColorDown(sf::Color(160, 160, 160));

  option2->onPress([this]() {
    toggleButtons(option2);

    boidsNumberSlider->setVisible(true);
    boidsNumberSliderLabel->setVisible(true);

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
  });

  gui.add(option2);

  // Button 3
  option3 = tgui::Button::create("Set \nparameters");
  option3->setPosition(950, 20);
  option3->setSize(80, 50);
  option3->getRenderer()->setBackgroundColor(
      sf::Color(128, 128, 128)); // Default "off"
  option3->getRenderer()->setBackgroundColorHover(
      sf::Color(190, 190, 190)); // Prevent white hover
  option3->getRenderer()->setBackgroundColorDown(sf::Color(160, 160, 160));

  option3->onPress([this]() {
    toggleButtons(option3);

    boidsNumberSlider->setVisible(false);
    boidsNumberSliderLabel->setVisible(false);

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

void Egui::selectedOption() {
  if (activeButton == option1) {
    drawStatistics();
    for (size_t i = 0; i < dynamicButtons.size(); ++i) {
      dynamicButtons[i]->setVisible(true);
    }
  } else if (activeButton == option2) {
    for (size_t i = 0; i < dynamicButtons.size(); ++i) {
      dynamicButtons[i]->setVisible(false);
    }
  } else if (activeButton == option3) {
    for (size_t i = 0; i < dynamicButtons.size(); ++i) {
      dynamicButtons[i]->setVisible(false);
    }
  }
}

///
// OPTION 1

void Egui::drawStatistics() {
  for (unsigned i{0}; i < flockStack_.size(); i++) {
    sf::RectangleShape rectangle1(sf::Vector2f(250, 105));
    rectangle1.setPosition(775, 140 + static_cast<float>(i) * 120);
    rectangle1.setFillColor(sf::Color::Black); // COLORE dello STORMO
    window.draw(rectangle1);

    sf::RectangleShape rectangle(sf::Vector2f(240, 95));
    rectangle.setPosition(780, 145 + static_cast<float>(i) * 120);
    window.draw(rectangle);

    sf::RectangleShape rectangle2(sf::Vector2f(15, 85));
    rectangle2.setPosition(770, 150 + static_cast<float>(i) * 120);
    rectangle2.setFillColor(flockStack_[i].getFlockColor());
    window.draw(rectangle2);
  }
}

void Egui::createDeleteFlockButton(size_t index) {
  auto button = tgui::Button::create(std::to_string(index + 1));
  button->setPosition(1015, 185 + index * 120);
  button->setSize(20, 20);
  button->getRenderer()->setBackgroundColor(sf::Color::Red);
  button->onPress([this, index = dynamicButtons.size()]() {
    std::cout << "Button " << index + 1 << " pressed!\n";
    deleteFlock(index);
    deleteDeleteFlockButton(index);
  });

  gui.add(button);                  // Add button to GUI
  dynamicButtons.push_back(button); // Store button in the map
}

void Egui::deleteDeleteFlockButton(size_t index) {
  if (index < 0 || index >= static_cast<int>(dynamicButtons.size())) {
    std::cout << "Invalid button index: " << index << "\n";
    return;
  }

  // Remove the button from GUI and erase it from the vector
  gui.remove(dynamicButtons[index]);
  dynamicButtons.erase(dynamicButtons.begin() + index);

  // Reposition the remaining buttons
  if (dynamicButtons.size() > 0) {
    repositionButtons();
  }

  std::cout << "Button " << index + 1 << " removed successfully.\n";
}

void Egui::repositionButtons() {
  for (size_t i = 0; i < dynamicButtons.size(); ++i) {
    dynamicButtons[i]->setText(std::to_string(i + 1));
    dynamicButtons[i]->setPosition(1015, 185 + i * 120);
    dynamicButtons[i]->onPress.disconnectAll();
    dynamicButtons[i]->onPress([this, index = i]() {
      std::cout << "Button " << index + 1 << " pressed!\n";
      deleteFlock(index);
      deleteDeleteFlockButton(index);
    });
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// OPTION 2

void Egui::createSlider(float posX, float posY, float width, int min, int max,
                        int initialValue) {

  auto slider = tgui::Slider::create(min, max);
  slider->setPosition(posX, posY); // Set position
  slider->setSize(width, 20);      // Set width and fixed height
  slider->setValue(initialValue);  // Set initial value
  gui.add(slider);                 // Add the slider to the GUI

  // Create the label for this slider
  auto label = tgui::Label::create();
  label->setPosition(posX + width + 10,
                     posY - 5); // Position next to the slider
  label->setText("Value: " + std::to_string(initialValue));
  label->getRenderer()->setTextColor(sf::Color::White);
  gui.add(label); // Add the label to the GUI

  // Connect slider to update the corresponding label
  slider->onValueChange([this, label, slider]() {
    label->setText("Value: " +
                   std::to_string(static_cast<int>(slider->getValue())));
  });
}

void Egui::createBoidsNumberSlider() {

  boidsNumberSlider = tgui::Slider::create();
  boidsNumberSlider->setPosition(775, 130); // Set position
  boidsNumberSlider->setSize(250, 20);      // Set width and fixed height
  boidsNumberSlider->setMinimum(5);         // Set minimum value
  boidsNumberSlider->setMaximum(50);        // Set maximum value
  boidsNumberSlider->setValue(10);          // Set initial value
  gui.add(boidsNumberSlider);               // Add the slider to the GUI

  // Create the label for this slider
  boidsNumberSliderLabel = tgui::Label::create();
  boidsNumberSliderLabel->setPosition(775,
                                      100); // Position next to the slider
  boidsNumberSliderLabel->setText("Number of boids: " + std::to_string(10));
  boidsNumberSliderLabel->setTextSize(15);
  boidsNumberSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(boidsNumberSliderLabel); // Add the label to the GUI

  // Connect slider to update the corresponding label
  boidsNumberSlider->onValueChange([this]() {
    boidsNumberSliderLabel->setText(
        "Number of boids: " +
        std::to_string(static_cast<int>(boidsNumberSlider->getValue())));
  });
}

void Egui::createCenterXSlider() {

  centerXSlider = tgui::Slider::create();
  centerXSlider->setPosition(775, 210); // Set position
  centerXSlider->setSize(250, 20);      // Set width and fixed height
  centerXSlider->setMinimum(0);         // Set minimum value
  centerXSlider->setMaximum(720);       // Set maximum value
  centerXSlider->setValue(360);         // Set initial value
  gui.add(centerXSlider);               // Add the slider to the GUI

  // Create the label for this slider
  centerXSliderLabel = tgui::Label::create();
  centerXSliderLabel->setPosition(775,
                                  180); // Position next to the slider
  centerXSliderLabel->setText("Center of Spawn X: " + std::to_string(360));
  centerXSliderLabel->setTextSize(15);
  centerXSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(centerXSliderLabel); // Add the label to the GUI

  // Connect slider to update the corresponding label
  centerXSlider->onValueChange([this]() {
    centerXSliderLabel->setText(
        "Center of Spawn X: " +
        std::to_string(static_cast<int>(centerXSlider->getValue())));
  });
}

void Egui::createCenterYSlider() {

  centerYSlider = tgui::Slider::create();
  centerYSlider->setPosition(775, 290); // Set position
  centerYSlider->setSize(250, 20);      // Set width and fixed height
  centerYSlider->setMinimum(0);         // Set minimum value
  centerYSlider->setMaximum(720);       // Set maximum value
  centerYSlider->setValue(360);         // Set initial value
  gui.add(centerYSlider);               // Add the slider to the GUI

  // Create the label for this slider
  centerYSliderLabel = tgui::Label::create();
  centerYSliderLabel->setPosition(775,
                                  260); // Position next to the slider
  centerYSliderLabel->setText("Center of Spawn Y: " + std::to_string(360));
  centerYSliderLabel->setTextSize(15);
  centerYSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(centerYSliderLabel); // Add the label to the GUI

  // Connect slider to update the corresponding label
  centerYSlider->onValueChange([this]() {
    centerYSliderLabel->setText(
        "Center of Spawn Y: " +
        std::to_string(static_cast<int>(centerYSlider->getValue())));
  });
}

void Egui::createRedSlider() {

  redSlider = tgui::Slider::create();
  redSlider->setPosition(775, 370); // Set position
  redSlider->setSize(250, 20);      // Set width and fixed height
  redSlider->setMinimum(0);         // Set minimum value
  redSlider->setMaximum(255);       // Set maximum value
  redSlider->setValue(0);           // Set initial value
  gui.add(redSlider);               // Add the slider to the GUI

  // Create the label for this slider
  redSliderLabel = tgui::Label::create();
  redSliderLabel->setPosition(775,
                              340); // Position next to the slider
  redSliderLabel->setText("Red: " + std::to_string(0));
  redSliderLabel->setTextSize(15);
  redSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(redSliderLabel); // Add the label to the GUI

  // Connect slider to update the corresponding label
  redSlider->onValueChange([this]() {
    redSliderLabel->setText(
        "Red: " + std::to_string(static_cast<int>(redSlider->getValue())));
  });
}

void Egui::createGreenSlider() {

  greenSlider = tgui::Slider::create();
  greenSlider->setPosition(775, 450); // Set position
  greenSlider->setSize(250, 20);      // Set width and fixed height
  greenSlider->setMinimum(0);         // Set minimum value
  greenSlider->setMaximum(255);       // Set maximum value
  greenSlider->setValue(0);           // Set initial value
  gui.add(greenSlider);               // Add the slider to the GUI

  // Create the label for this slider
  greenSliderLabel = tgui::Label::create();
  greenSliderLabel->setPosition(775,
                                420); // Position next to the slider
  greenSliderLabel->setText("Green: " + std::to_string(0));
  greenSliderLabel->setTextSize(15);
  greenSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(greenSliderLabel); // Add the label to the GUI

  // Connect slider to update the corresponding label
  greenSlider->onValueChange([this]() {
    greenSliderLabel->setText(
        "Green: " + std::to_string(static_cast<int>(greenSlider->getValue())));
  });
}

void Egui::createBlueSlider() {

  blueSlider = tgui::Slider::create();
  blueSlider->setPosition(775, 530); // Set position
  blueSlider->setSize(250, 20);      // Set width and fixed height
  blueSlider->setMinimum(0);         // Set minimum value
  blueSlider->setMaximum(255);       // Set maximum value
  blueSlider->setValue(0);           // Set initial value
  gui.add(blueSlider);               // Add the slider to the GUI

  // Create the label for this slider
  blueSliderLabel = tgui::Label::create();
  blueSliderLabel->setPosition(775,
                               500); // Position next to the slider
  blueSliderLabel->setText("Blue: " + std::to_string(0));
  blueSliderLabel->setTextSize(15);
  blueSliderLabel->getRenderer()->setTextColor(sf::Color::Black);
  gui.add(blueSliderLabel); // Add the label to the GUI

  // Connect slider to update the corresponding label
  blueSlider->onValueChange([this]() {
    blueSliderLabel->setText(
        "Blue: " + std::to_string(static_cast<int>(blueSlider->getValue())));
  });
}

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

// void Egui::createDeleteFlockButton() {
//   deleteFlockButton = tgui::Button::create("Create Flock");
//   deleteFlockButton->setPosition(770, 580);
//   deleteFlockButton->setSize(250, 80);
//   deleteFlockButton->getRenderer()->setBackgroundColor(
//       sf::Color(128, 128, 128)); // Default "off"
//   deleteFlockButton->getRenderer()->setBackgroundColorHover(
//       sf::Color(128, 128, 128)); // Prevent white hover
//   deleteFlockButton->getRenderer()->setBackgroundColorDown(
//       sf::Color(255, 255, 204));

//   deleteFlockButton->onPress([this]() { deleteFlock(i); });

//   gui.add(deleteFlockButton);
// }

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void Egui::drawInterface() {
  sf::RectangleShape top(sf::Vector2f(750, 15));
  top.setPosition(0, 0);
  top.setFillColor(sf::Color::Black);
  sf::RectangleShape bottom(sf::Vector2f(750, 15));
  bottom.setPosition(0, 735);
  bottom.setFillColor(sf::Color::Black);
  sf::RectangleShape left(sf::Vector2f(15, 720));
  left.setPosition(0, 15);
  left.setFillColor(sf::Color::Black);
  sf::RectangleShape right(sf::Vector2f(15, 720));
  right.setPosition(735, 15);
  right.setFillColor(sf::Color::Black);

  window.draw(top);
  window.draw(bottom);
  window.draw(left);
  window.draw(right);

  sf::RectangleShape topS(sf::Vector2f(290, 5));
  topS.setPosition(755, 5);
  topS.setFillColor(sf::Color::Black);
  sf::RectangleShape bottomS(sf::Vector2f(290, 5));
  bottomS.setPosition(755, 740);
  bottomS.setFillColor(sf::Color::Black);
  sf::RectangleShape leftS(sf::Vector2f(5, 740));
  leftS.setPosition(755, 5);
  leftS.setFillColor(sf::Color::Black);
  sf::RectangleShape rightS(sf::Vector2f(5, 740));
  rightS.setPosition(1040, 5);
  rightS.setFillColor(sf::Color::Black);

  window.draw(topS);
  window.draw(bottomS);
  window.draw(leftS);
  window.draw(rightS);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void Egui::addFlock(size_t n, sf::Vector2f center, sf::Color color) {
  if (flockStack_.size() < constants::maxFlockNumber) {
    flockStack_.emplace_back(createFlock(n, center, color));
    createDeleteFlockButton(flockStack_.size() - 1);
    addFlockButtonLabel->setText(
        "Number of flocks: " + std::to_string(flockStack_.size()) + "/5");
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
    flockStack_[i].updateFlockRepel(
        flockStack_[i].Separation(separation, separationRange),
        flockStack_[i].Alignment(alignment),
        flockStack_[i].Cohesion(cohesion, toroidal),
        Repel(flockStack_, i, repel, repelRange), toroidal);

    bodyStack_[i].clear();

    for (size_t j{0}; j < flockStack_[i].getSize(); j++) {
      bodyStack_[i].emplace_back(boidTriangle(flockStack_[i], j));
    }

    drawFlock(window, bodyStack_[i]);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////