#include "egui.hpp"
#include "constants.hpp"
#include "flock.hpp"
#include "graphics.hpp"
#include "random.hpp"
#include "statistics.hpp"
#include "structs.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <TGUI/TGUI.hpp>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

extern bool toroidal;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Egui::Egui() : window(sf::VideoMode(1050, 750), "Egui"), gui(window) {}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::setup() {

  // THE ORDER in WHICH OPTIONS are SET UP is IMPORTANT!!!

  sans.loadFromFile("../OpenSans-Regular.ttf");

  // CREATE OPTIONS

  createThreeWaySwitch(constants::button1, constants::button2,
                       constants::button3);

  // OPTION 2

  setupOpt2();

  // OPTION 3

  setupOpt3();

  // GENERATE FLOCKS at the BEGINNING

  addFlock(randomInt(10, 50), {randomFloat(15, 735), randomFloat(15, 735)},
           sf::Color{255, 0, 127}); // PINK
  addFlock(randomInt(10, 50), {randomFloat(15, 735), randomFloat(15, 735)},
           sf::Color{255, 0, 0}); // RED
  addFlock(randomInt(10, 50), {randomFloat(15, 735), randomFloat(15, 735)},
           sf::Color{255, 204, 0}); // YELLOW
  addFlock(randomInt(10, 50), {randomFloat(15, 735), randomFloat(15, 735)},
           sf::Color{153, 255, 51}); // GREEN
  addFlock(randomInt(10, 50), {randomFloat(15, 735), randomFloat(15, 735)},
           sf::Color{0, 204, 204}); // CYAN

  // OPTION 1

  createSwitchButton(constants::toroidalButton);
  setVisibleOpt1(true);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::run() {

  window.setPosition({120, 50});
  window.setFramerateLimit(constants::windowFrameRate);
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

    enableCreateFlockButton();

    drawInterface();
    drawFlocks();
    drawMargin();

    selectedOption();

    gui.draw();
    window.display();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// Sets up the GUI components

void Egui::createThreeWaySwitch(const TguiPar &button1, const TguiPar &button2,
                                const TguiPar &button3) {
  // Button 1
  sf::Color a = constants::offThreeWayBGColor;
  sf::Color b = constants::offThreeWayBGColorHover;
  sf::Color c = constants::threeWayBGColorDown;

  option1 = tgui::Button::create("Statistics");
  option1->setPosition(button1.posX, button1.posY);
  option1->setSize(button1.width, button1.height);
  option1->getRenderer()->setBackgroundColor(
      constants::onThreeWayBGColor); // Default "on"
  option1->getRenderer()->setBackgroundColorHover(
      constants::onThreeWayBGColorHover);
  option1->getRenderer()->setBackgroundColorDown(c);

  option1->onPress([this]() {
    toggleButtons(option1);
    selectedOption1();
  });

  gui.add(option1);

  // Button 2
  option2 = tgui::Button::create("Create flock");
  option2->setPosition(button2.posX, button2.posY);
  option2->setSize(button2.width, button2.height);
  option2->getRenderer()->setBackgroundColor(a); // Default "off"
  option2->getRenderer()->setBackgroundColorHover(b);
  option2->getRenderer()->setBackgroundColorDown(c);

  option2->onPress([this]() {
    toggleButtons(option2);
    selectedOption2();
  });

  gui.add(option2);

  // Button 3
  option3 = tgui::Button::create("Set\n"
                                 "parameters");
  option3->setPosition(button3.posX, button3.posY);
  option3->setSize(button3.width, button3.height);
  option3->getRenderer()->setBackgroundColor(a); // Default "off"
  option3->getRenderer()->setBackgroundColorHover(b);
  option3->getRenderer()->setBackgroundColorDown(c);

  option3->onPress([this]() {
    toggleButtons(option3);
    selectedOption3();
  });

  gui.add(option3);

  activeButton = option1;
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::toggleButtons(tgui::Button::Ptr pressedButton) {
  // Set all buttons to "off" (gray background)
  option1->getRenderer()->setBackgroundColor(constants::offThreeWayBGColor);
  option2->getRenderer()->setBackgroundColor(constants::offThreeWayBGColor);
  option3->getRenderer()->setBackgroundColor(constants::offThreeWayBGColor);

  option1->getRenderer()->setBackgroundColorHover(
      constants::offThreeWayBGColorHover);
  option2->getRenderer()->setBackgroundColorHover(
      constants::offThreeWayBGColorHover);
  option3->getRenderer()->setBackgroundColorHover(
      constants::offThreeWayBGColorHover);

  pressedButton->getRenderer()->setBackgroundColor(
      constants::onThreeWayBGColor);
  pressedButton->getRenderer()->setBackgroundColorHover(
      constants::onThreeWayBGColorHover);

  activeButton = pressedButton;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Updates CONTINUOUSLY to the SELECTED OPTION

void Egui::selectedOption() {
  if (activeButton == option1) {
    drawStatistics();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
// CHANGES WHAT DO DISPLAY ON CLICK

void Egui::selectedOption1() {
  setVisibleOpt1(true);
  setVisibleOpt2(false);
  setVisibleOpt3(false);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::selectedOption2() {
  setVisibleOpt1(false);
  setVisibleOpt2(true);
  setVisibleOpt3(false);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::selectedOption3() {
  setVisibleOpt1(false);
  setVisibleOpt2(false);
  setVisibleOpt3(true);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// OPTION 1

void Egui::createSwitchButton(const TguiPar &par) {
  switchButton = tgui::Button::create("Mirror Mode");
  switchButton->setPosition(par.posX, par.posY);
  switchButton->setSize(par.width, par.height);
  switchButton->getRenderer()->setBackgroundColor(constants::offToroidalColor);
  switchButton->getRenderer()->setBackgroundColorHover(
      constants::offToroidalHover);
  switchButton->getRenderer()->setBackgroundColorDown(
      constants::offToroidalDown);

  // Attach the toggleSwitch action to the button
  switchButton->onPress([this]() { toggleSwitch(); });

  gui.add(switchButton);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::toggleSwitch() {
  isSwitchOn = !isSwitchOn;

  if (isSwitchOn) {
    switchButton->setText("Toroidal Mode");
    switchButton->getRenderer()->setBackgroundColor(constants::onToroidalColor);
    switchButton->getRenderer()->setBackgroundColorHover(
        constants::onToroidalHover);
    switchButton->getRenderer()->setBackgroundColorDown(
        constants::onToroidalDown);
    toroidal = true;
  } else {
    switchButton->setText("Mirror Mode");
    switchButton->getRenderer()->setBackgroundColor(
        constants::offToroidalColor);
    switchButton->getRenderer()->setBackgroundColorHover(
        constants::offToroidalHover);
    switchButton->getRenderer()->setBackgroundColorDown(
        constants::offToroidalDown);
    toroidal = false;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void Egui::drawStatistics() {
  for (size_t i{0}; i < flockStack_.size(); i++) {
    float posIndex{static_cast<float>(i) * constants::distancePerIndex};

    RectanglePar rectangle1par{constants::statsRectangle1};
    rectangle1par.posY += posIndex;
    sf::RectangleShape rectangle1(getRectangle(rectangle1par));

    RectanglePar rectangle2par{constants::statsRectangle2};
    rectangle2par.posY += posIndex;
    sf::RectangleShape rectangle2(
        getRectangle(rectangle2par, sf::Color::White));

    RectanglePar rectangle3par{constants::statsRectangle3};
    rectangle3par.posY += posIndex;
    sf::RectangleShape rectangle3(
        getRectangle(rectangle3par, flockStack_[i].getFlockColor()));

    window.draw(rectangle1);
    window.draw(rectangle2);
    window.draw(rectangle3);

    printFlockStats(i);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createDeleteFlockButton(size_t index) {
  float posX{constants::deleteFlockButton.posX};
  float posY{constants::deleteFlockButton.posY};
  float width{constants::deleteFlockButton.width};
  float height{constants::deleteFlockButton.height};

  auto button = tgui::Button::create(std::to_string(index + 1));
  button->setPosition(
      posX, posY + static_cast<float>(index * constants::distancePerIndex));
  button->setSize(width, height);
  button->getRenderer()->setBackgroundColor(sf::Color::Red);
  button->onPress([this, index = dynamicButtons.size()]() {
    deleteFlock(index);
    deleteDeleteFlockButton(index);
  });

  gui.add(button);
  dynamicButtons.push_back(button);

  createStatisticsLabels(index);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createStatisticsLabels(size_t index) {
  float posX{constants::statisticsLabel.posX};
  float posY{constants::statisticsLabel.posY};
  unsigned textSize{constants::statisticsLabel.textSize};
  float posIndex{static_cast<float>(index * constants::distancePerIndex)};

  auto label0 = tgui::Label::create("Mean Distance: ");
  label0->setTextSize(textSize);
  label0->setPosition({posX, posY + posIndex});
  gui.add(label0);

  auto label1 = tgui::Label::create("Distance std dev: ");
  label1->setTextSize(textSize);
  label1->setPosition({posX, posY + constants::labelsDistance + posIndex});
  gui.add(label1);

  auto label2 = tgui::Label::create("Mean Speed: ");
  label2->setTextSize(textSize);
  label2->setPosition({posX, posY + 2 * constants::labelsDistance + posIndex});
  gui.add(label2);

  auto label3 = tgui::Label::create("Speed std dev: ");
  label3->setTextSize(textSize);
  label3->setPosition({posX, posY + 3 * constants::labelsDistance + posIndex});
  gui.add(label3);

  dynamicLabels.push_back({label0, label1, label2, label3});
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::printValue(const LabelsPar &par, int value, size_t index) {
  sf::Text text;

  text.setString(std::to_string(value));
  text.setFont(sans);
  text.setCharacterSize(par.textSize);
  text.setFillColor(sf::Color::Black);
  text.setPosition(par.posX, par.posY + static_cast<float>(index) *
                                            constants::distancePerIndex);

  window.draw(text);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::printFlockStats(size_t index) {

  int flockSize{static_cast<int>(flockStack_[index].getSize())};
  printValue(constants::flockSizeLabel, flockSize, index);

  LabelsPar par{constants::statisticsValueLabel};

  float meanDistanceValue{calculateMean(
      calculateDistances(flockStack_[index].getFlockPositions()))};
  int meanDistance{static_cast<int>(meanDistanceValue)};
  printValue(par, meanDistance, index);

  par.posY += constants::labelsDistance;

  int standardDeviation{static_cast<int>(calculateStandardDeviation(
      calculateDistances(flockStack_[index].getFlockPositions()),
      meanDistanceValue))};
  printValue(par, standardDeviation, index);

  par.posY += constants::labelsDistance;

  float meanSpeedValue{flockStack_[index].getMeanSpeed()};
  int meanSpeed{static_cast<int>(meanSpeedValue)};
  printValue(par, meanSpeed, index);

  par.posY += constants::labelsDistance;

  int SpeedStandardDeviation{static_cast<int>(calculateStandardDeviation(
      flockStack_[index].getSpeedVector(), meanSpeedValue))};
  printValue(par, SpeedStandardDeviation, index);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::deleteDeleteFlockButton(size_t index) {
  if (index >= dynamicButtons.size()) {
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
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::repositionButtons() {

  for (size_t i = 0; i < dynamicButtons.size(); ++i) {
    float posIndex{static_cast<float>(i * constants::distancePerIndex)};

    dynamicButtons[i]->setText(std::to_string(i + 1));
    dynamicButtons[i]->setPosition(constants::deleteFlockButton.posX,
                                   constants::deleteFlockButton.posY +
                                       posIndex);
    dynamicButtons[i]->onPress.disconnectAll();
    dynamicButtons[i]->onPress([this, i]() {
      deleteFlock(i);
      deleteDeleteFlockButton(i);
    });

    float posX{constants::statisticsLabel.posX};
    float posY{constants::statisticsLabel.posY};

    dynamicLabels[i][0]->setPosition({posX, posY + posIndex});
    dynamicLabels[i][1]->setPosition(
        {posX, posY + constants::labelsDistance + posIndex});
    dynamicLabels[i][2]->setPosition(
        {posX, posY + constants::labelsDistance * 2 + posIndex});
    dynamicLabels[i][3]->setPosition(
        {posX, posY + constants::labelsDistance * 3 + posIndex});
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::setVisibleOpt1(bool visible) {
  switchButton->setVisible(visible);

  for (size_t i = 0; i < dynamicButtons.size(); ++i) {
    dynamicButtons[i]->setVisible(visible);
  }

  for (auto &labels : dynamicLabels) {
    for (size_t i{0}; i < 4; i++) {
      labels[i]->setVisible(visible);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// OPTION 2

void Egui::createSliderOpt2(const SlidersPar &sliderPar) {

  auto slider = tgui::Slider::create(sliderPar.min, sliderPar.max);
  slider->setPosition(sliderPar.posX, sliderPar.posY);
  slider->setSize(sliderPar.width, sliderPar.height);
  slider->setValue(sliderPar.initialValue);
  gui.add(slider);

  option2Sliders.emplace_back(slider);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createLabelOpt2(const LabelsPar &labelsPar) {

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

  if (newTotal > constants::colorSliderTotalMax) {
    // If the sum exceeds 765, lower the current slider to keep it in range
    changedSlider->setValue(
        changedSlider->getValue() -
        static_cast<float>(newTotal - constants::colorSliderTotalMax));
  } else if (newTotal < constants::colorSliderTotalMin) {
    // If the sum is below 255, increase the slider to stay within bounds
    changedSlider->setValue(
        changedSlider->getValue() +
        static_cast<float>(constants::colorSliderTotalMin - newTotal));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::createAddFlockButton(const TguiPar &par) {
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
             {option2Sliders[1]->getValue(), option2Sliders[2]->getValue()},
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

void Egui::createSliderOpt3(const SlidersPar &params) {
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

void Egui::createLabelOpt3(const LabelsPar &labelsPar,
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
  sf::RectangleShape topSettings(getRectangle(constants::topSettingMargin));
  sf::RectangleShape bottomSettings(
      getRectangle(constants::bottomSettingMargin));
  sf::RectangleShape leftSettings(getRectangle(constants::leftSettingMargin));
  sf::RectangleShape rightSettings(getRectangle(constants::rightSettingMargin));

  window.draw(topSettings);
  window.draw(bottomSettings);
  window.draw(leftSettings);
  window.draw(rightSettings);

  // BLACK BACKGROUND
  sf::RectangleShape rectangle({constants::fieldSide, constants::fieldSide});
  rectangle.setPosition(constants::marginSize, constants::marginSize);
  rectangle.setFillColor(sf::Color::Black);

  window.draw(rectangle);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::drawMargin() {
  sf::Color color{constants::fieldColor};

  sf::RectangleShape topField(getRectangle(constants::topMargin, color));
  sf::RectangleShape bottomField(getRectangle(constants::bottomMargin, color));
  sf::RectangleShape leftField(getRectangle(constants::leftMargin, color));
  sf::RectangleShape rightField(getRectangle(constants::rightMargin, color));

  window.draw(topField);
  window.draw(bottomField);
  window.draw(leftField);
  window.draw(rightField);
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

    //   flockStack_[i].updateFlock(
    //       separationSlider->getValue() / constants::scalingFactor,
    //       separationRangeSlider->getValue(),
    //       alignmentSlider->getValue() / constants::scalingFactor,
    //       cohesionSlider->getValue() / constants::scalingFactor,
    //       interactionSlider->getValue(),
    //       Repel(flockStack_, i,
    //             repelSlider->getValue() / constants::scalingFactor,
    //             repelRangeSlider->getValue()));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Egui::drawFlocks() {
  for (size_t i{0}; i < bodyStack_.size(); i++) {
    bodyStack_[i].clear();
    sf::Color color{flockStack_[i].getFlockColor()};

    for (size_t j{0}; j < flockStack_[i].getSize(); j++) {
      bodyStack_[i].emplace_back(
          getTriangleBoid(flockStack_[i].getBoid(j), color));
      window.draw(bodyStack_[i][j]);
    }
  }
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