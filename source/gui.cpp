#include "../include/gui.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <TGUI/Color.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/EditBoxSlider.hpp>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "../include/constants.hpp"
#include "../include/flock.hpp"
#include "../include/graphics.hpp"
#include "../include/random.hpp"
#include "../include/statistics.hpp"
#include "../include/structs.hpp"
#include "../include/switchbutton.hpp"

namespace ev {

Gui::Gui()
    : window_(sf::VideoMode(constants::windowWidth, constants::windowHeight),
              "Flocks Simulation"),
      gui_(window_) {}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::setup() {
  // THE ORDER in WHICH OPTIONS are SET UP is IMPORTANT!!!

  sans_.loadFromFile("../assets/OpenSans-Regular.ttf");

  // CREATE OPTIONS

  createThreeWaySwitch(constants::button1, constants::button2,
                       constants::button3);

  // OPTION 2

  setupOpt2();

  // OPTION 3

  setupOpt3();

  // GENERATE FLOCKS at the BEGINNING

  addFlock(randomGen::randomInt<size_t>(10, 50),
           {ev::randomVec2f(0.f, constants::fieldSide)},
           sf::Color{255, 0, 127});  // PINK
  addFlock(randomGen::randomInt<size_t>(10, 50),
           {ev::randomVec2f(0.f, constants::fieldSide)},
           sf::Color{255, 0, 0});  // RED
  addFlock(randomGen::randomInt<size_t>(10, 50),
           {ev::randomVec2f(0.f, constants::fieldSide)},
           sf::Color{255, 204, 0});  // YELLOW
  addFlock(randomGen::randomInt<size_t>(10, 50),
           {ev::randomVec2f(0.f, constants::fieldSide)},
           sf::Color{153, 255, 51});  // GREEN
  addFlock(randomGen::randomInt<size_t>(10, 50),
           {ev::randomVec2f(0.f, constants::fieldSide)},
           sf::Color{0, 204, 204});  // CYAN

  // OPTION 1

  setupOpt1();
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::run() {
  window_.setPosition({120, 50});
  window_.setFramerateLimit(constants::windowFrameRate);
  sf::Event event;

  while (window_.isOpen()) {
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Space) {
        pause_ = !pause_;
        continue;
      }

      gui_.handleEvent(event);

      switch (event.type) {
        case sf::Event::Closed: {
          window_.close();
          break;
        }

        default:
          break;
      }
    }

    if (!pause_) {
      interactWithFlocks();
      evolveFlocks();
    }

    window_.clear(sf::Color::White);

    enableCreateFlockButton();

    drawInterface();
    drawFlocks();
    drawMargin();

    selectedOption();

    gui_.draw();
    window_.display();
  }
  gui_.removeAllWidgets();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// Draw Interface

void Gui::drawInterface() {
  sf::RectangleShape topSettings(getRectangle(constants::topSettingMargin));
  sf::RectangleShape bottomSettings(
      getRectangle(constants::bottomSettingMargin));
  sf::RectangleShape leftSettings(getRectangle(constants::leftSettingMargin));
  sf::RectangleShape rightSettings(getRectangle(constants::rightSettingMargin));

  window_.draw(topSettings);
  window_.draw(bottomSettings);
  window_.draw(leftSettings);
  window_.draw(rightSettings);

  // BLACK BACKGROUND

  sf::RectangleShape rectangle({constants::fieldSide, constants::fieldSide});
  rectangle.setPosition(constants::marginSize, constants::marginSize);
  rectangle.setFillColor(backgroundColour_);

  window_.draw(rectangle);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::drawMargin() {
  sf::RectangleShape topField(
      getRectangle(constants::topMargin, constants::marginColor));
  sf::RectangleShape bottomField(
      getRectangle(constants::bottomMargin, constants::marginColor));
  sf::RectangleShape leftField(
      getRectangle(constants::leftMargin, constants::marginColor));
  sf::RectangleShape rightField(
      getRectangle(constants::rightMargin, constants::marginColor));

  window_.draw(topField);
  window_.draw(bottomField);
  window_.draw(leftField);
  window_.draw(rightField);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// Sets up the GUI components

void Gui::createThreeWaySwitch(const TguiPar &button1, const TguiPar &button2,
                               const TguiPar &button3) {
  // Button 1
  sf::Color a = constants::offThreeWayBGColor;
  sf::Color b = constants::offThreeWayBGColorHover;
  sf::Color c = constants::threeWayBGColorDown;

  option1_ = tgui::Button::create(
      "Graphics &\n"
      "statistics");
  option1_->setPosition(button1.posX, button1.posY);
  option1_->setSize(button1.width, button1.height);
  option1_->getRenderer()->setBackgroundColor(
      constants::onThreeWayBGColor);  // Default "on"
  option1_->getRenderer()->setBackgroundColorHover(
      constants::onThreeWayBGColorHover);
  option1_->getRenderer()->setBackgroundColorDown(c);

  option1_->onPress([this]() {
    toggleButtons(option1_);
    selectedOption1();
  });

  gui_.add(option1_);

  // Button 2
  option2_ = tgui::Button::create(
      "Create\n"
      "flocks");
  option2_->setPosition(button2.posX, button2.posY);
  option2_->setSize(button2.width, button2.height);
  option2_->getRenderer()->setBackgroundColor(a);  // Default "off"
  option2_->getRenderer()->setBackgroundColorHover(b);
  option2_->getRenderer()->setBackgroundColorDown(c);

  option2_->onPress([this]() {
    toggleButtons(option2_);
    selectedOption2();
  });

  gui_.add(option2_);

  // Button 3
  option3_ = tgui::Button::create(
      "Simulation\n"
      "parameters");
  option3_->setPosition(button3.posX, button3.posY);
  option3_->setSize(button3.width, button3.height);
  option3_->getRenderer()->setBackgroundColor(a);  // Default "off"
  option3_->getRenderer()->setBackgroundColorHover(b);
  option3_->getRenderer()->setBackgroundColorDown(c);

  option3_->onPress([this]() {
    toggleButtons(option3_);
    selectedOption3();
  });

  gui_.add(option3_);

  activeButton_ = option1_;
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::toggleButtons(tgui::Button::Ptr pressedButton) {
  // Set all buttons to "off"
  option1_->getRenderer()->setBackgroundColor(constants::offThreeWayBGColor);
  option2_->getRenderer()->setBackgroundColor(constants::offThreeWayBGColor);
  option3_->getRenderer()->setBackgroundColor(constants::offThreeWayBGColor);

  option1_->getRenderer()->setBackgroundColorHover(
      constants::offThreeWayBGColorHover);
  option2_->getRenderer()->setBackgroundColorHover(
      constants::offThreeWayBGColorHover);
  option3_->getRenderer()->setBackgroundColorHover(
      constants::offThreeWayBGColorHover);

  pressedButton->getRenderer()->setBackgroundColor(
      constants::onThreeWayBGColor);
  pressedButton->getRenderer()->setBackgroundColorHover(
      constants::onThreeWayBGColorHover);

  activeButton_ = pressedButton;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Updates CONTINUOUSLY to the SELECTED OPTION

void Gui::selectedOption() {
  if (activeButton_ == option1_) {
    drawStatistics();
    if (Flock::getToroidalMode()) {
      printToroidalFlockStats();
    } else {
      printFlockStats();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
// CHANGES WHAT DO DISPLAY ON CLICK

void Gui::selectedOption1() {
  setVisibleOpt1(true);
  setVisibleOpt2(false);
  setVisibleOpt3(false);
}

void Gui::selectedOption2() {
  setVisibleOpt1(false);
  setVisibleOpt2(true);
  setVisibleOpt3(false);
}

void Gui::selectedOption3() {
  setVisibleOpt1(false);
  setVisibleOpt2(false);
  setVisibleOpt3(true);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// OPTION 1

void Gui::drawStatistics() {
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

    window_.draw(rectangle1);
    window_.draw(rectangle2);
    window_.draw(rectangle3);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::createDeleteFlockButton(size_t index) {
  float posX{constants::deleteFlockButton.posX};
  float posY{constants::deleteFlockButton.posY};
  float width{constants::deleteFlockButton.width};
  float height{constants::deleteFlockButton.height};

  auto button = tgui::Button::create(std::to_string(index + 1));
  button->setPosition(
      posX, posY + static_cast<float>(index * constants::distancePerIndex));
  button->setSize(width, height);
  button->getRenderer()->setBackgroundColor(sf::Color::Red);
  button->onPress([this, index = dynamicButtons_.size()]() {
    deleteFlock(index);
    deleteDeleteFlockButton(index);
  });

  gui_.add(button);
  dynamicButtons_.push_back(button);

  createStatisticsLabel(index);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::createStatisticsLabel(size_t index) {
  float posX{constants::statisticsLabel.posX};
  float posY{constants::statisticsLabel.posY};
  unsigned textSize{constants::statisticsLabel.textSize};
  float posIndex{static_cast<float>(index * constants::distancePerIndex)};

  auto label0 = tgui::Label::create("Mean Distance: ");
  label0->setTextSize(textSize);
  label0->setPosition({posX, posY + posIndex});
  gui_.add(label0);

  auto label1 = tgui::Label::create("Distance std dev: ");
  label1->setTextSize(textSize);
  label1->setPosition({posX, posY + constants::labelsDistance + posIndex});
  gui_.add(label1);

  auto label2 = tgui::Label::create("Mean Speed: ");
  label2->setTextSize(textSize);
  label2->setPosition({posX, posY + 2 * constants::labelsDistance + posIndex});
  gui_.add(label2);

  auto label3 = tgui::Label::create("Speed std dev: ");
  label3->setTextSize(textSize);
  label3->setPosition({posX, posY + 3 * constants::labelsDistance + posIndex});
  gui_.add(label3);

  dynamicLabels_.push_back({label0, label1, label2, label3});
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::printValue(const LabelsPar &par, int value, size_t index) {
  sf::Text text;

  text.setString(std::to_string(value));
  text.setFont(sans_);
  text.setCharacterSize(par.textSize);
  text.setFillColor(sf::Color::Black);
  text.setPosition(par.posX, par.posY + static_cast<float>(index) *
                                            constants::distancePerIndex);

  window_.draw(text);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::printFlockStats() {
  for (size_t index{0}; index < flockStack_.size(); index++) {
    int flockSize{static_cast<int>(flockStack_[index].getSize())};
    printValue(constants::flockSizeLabel, flockSize, index);

    LabelsPar par{constants::statisticsValueLabel};

    std::vector<float> distances{
        calculateDistances(flockStack_[index].getFlockPositions())};

    float meanDistanceValue{calculateMean(distances)};
    printValue(par, static_cast<int>(meanDistanceValue), index);

    par.posY += constants::labelsDistance;

    printValue(par,
               static_cast<int>(
                   calculateStandardDeviation(distances, meanDistanceValue)),
               index);

    par.posY += constants::labelsDistance;

    float meanSpeedValue{flockStack_[index].getMeanSpeed()};

    printValue(par, static_cast<int>(meanSpeedValue), index);

    par.posY += constants::labelsDistance;

    printValue(par,
               static_cast<int>(calculateStandardDeviation(
                   flockStack_[index].getSpeedVector(), meanSpeedValue)),
               index);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::printToroidalFlockStats() {
  for (size_t index{0}; index < flockStack_.size(); index++) {
    int flockSize{static_cast<int>(flockStack_[index].getSize())};
    printValue(constants::flockSizeLabel, flockSize, index);

    LabelsPar par{constants::statisticsValueLabel};

    std::vector<float> distances{
        calculateToroidalDistances(flockStack_[index].getFlockPositions())};
    float meanDistanceValue{calculateMean(distances)};

    printValue(par, static_cast<int>(meanDistanceValue), index);

    par.posY += constants::labelsDistance;

    printValue(par,
               static_cast<int>(
                   calculateStandardDeviation(distances, meanDistanceValue)),
               index);

    par.posY += constants::labelsDistance;

    float meanSpeedValue{flockStack_[index].getMeanSpeed()};

    printValue(par, static_cast<int>(meanSpeedValue), index);

    par.posY += constants::labelsDistance;

    printValue(par,
               static_cast<int>(calculateStandardDeviation(
                   flockStack_[index].getSpeedVector(), meanSpeedValue)),
               index);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::deleteDeleteFlockButton(size_t index) {
  if (index >= dynamicButtons_.size()) {
    std::cout << "Invalid button index: " << index << "\n";
    return;
  }

  // Remove the button from GUI and erase it from the vector
  gui_.remove(dynamicButtons_[index]);
  dynamicButtons_.erase(dynamicButtons_.begin() + static_cast<long>(index));

  for (size_t i{0}; i < 4; i++) {
    gui_.remove(dynamicLabels_[index][i]);
  }
  dynamicLabels_.erase(dynamicLabels_.begin() + static_cast<long>(index));

  // Reposition the remaining buttons
  if (dynamicButtons_.size() > 0) {
    repositionButtons();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::repositionButtons() {
  for (size_t i = 0; i < dynamicButtons_.size(); ++i) {
    float posIndex{static_cast<float>(i * constants::distancePerIndex)};

    dynamicButtons_[i]->setText(std::to_string(i + 1));
    dynamicButtons_[i]->setPosition(
        constants::deleteFlockButton.posX,
        constants::deleteFlockButton.posY + posIndex);
    dynamicButtons_[i]->onPress.disconnectAll();
    dynamicButtons_[i]->onPress([this, i]() {
      deleteFlock(i);
      deleteDeleteFlockButton(i);
    });

    float posX{constants::statisticsLabel.posX};
    float posY{constants::statisticsLabel.posY};

    dynamicLabels_[i][0]->setPosition({posX, posY + posIndex});
    dynamicLabels_[i][1]->setPosition(
        {posX, posY + constants::labelsDistance + posIndex});
    dynamicLabels_[i][2]->setPosition(
        {posX, posY + constants::labelsDistance * 2 + posIndex});
    dynamicLabels_[i][3]->setPosition(
        {posX, posY + constants::labelsDistance * 3 + posIndex});
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::setupOpt1() {
  graphicsButton_ = SwitchButton::create(constants::graphicsButton);
  // COLOR for the BACKGROUND and TEXT of the BUTTON are INVERTED for visibility
  const sf::Color &textOff{constants::onGraphicsButtonColor};
  const sf::Color &textOn{constants::offGraphicsButtonColor};

  graphicsButton_->getRenderer()->setTextColor(textOff);
  graphicsButton_->getRenderer()->setTextColorHover(textOff);
  graphicsButton_->getRenderer()->setTextColorDown(textOff);

  graphicsButton_->setOffAction([this]() -> void {
    backgroundColour_ = sf::Color::Black;
    graphicsButton_->getRenderer()->setTextColor(textOff);
    graphicsButton_->getRenderer()->setTextColorHover(textOff);
    graphicsButton_->getRenderer()->setTextColorDown(textOff);
  });
  graphicsButton_->setOnAction([this]() -> void {
    backgroundColour_ = sf::Color::White;
    graphicsButton_->getRenderer()->setTextColor(textOn);
    graphicsButton_->getRenderer()->setTextColorHover(textOn);
    graphicsButton_->getRenderer()->setTextColorDown(textOn);
  });

  gui_.add(graphicsButton_);

  setVisibleOpt1(true);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::setVisibleOpt1(bool visible) {
  graphicsButton_->setVisible(visible);

  for (size_t i = 0; i < dynamicButtons_.size(); ++i) {
    dynamicButtons_[i]->setVisible(visible);
  }

  for (auto &labels : dynamicLabels_) {
    for (size_t i{0}; i < 4; i++) {
      labels[i]->setVisible(visible);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// OPTION 2

void Gui::createSliderOpt2(const SlidersPar &sliderPar) {
  auto slider = tgui::Slider::create(sliderPar.min, sliderPar.max);
  slider->setPosition(sliderPar.posX, sliderPar.posY);
  slider->setSize(sliderPar.width, sliderPar.height);
  slider->setValue(sliderPar.initialValue);
  gui_.add(slider);

  option2Sliders_.emplace_back(slider);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::createLabelOpt2(const LabelsPar &labelsPar) {
  auto label = tgui::Label::create();
  label->setPosition(labelsPar.posX, labelsPar.posY);
  label->getRenderer()->setTextColor(sf::Color::White);
  label->setTextSize(labelsPar.textSize);
  label->getRenderer()->setTextColor(sf::Color::Black);
  gui_.add(label);

  option2Labels_.emplace_back(label);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::setLabelTextOpt2(size_t index, const std::string &text) {
  option2Labels_[index]->setText(
      text +
      std::to_string(static_cast<int>(option2Sliders_[index]->getValue())));

  option2Sliders_[index]->onValueChange([this, index, text]() {
    option2Labels_[index]->setText(
        text +
        std::to_string(static_cast<int>(option2Sliders_[index]->getValue())));
  });
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::setupOpt2() {
  createSliderOpt2(constants::boidsNumberSlider);
  createSliderOpt2(constants::centerXSlider);
  createSliderOpt2(constants::centerYSlider);
  createSliderOpt2(constants::redSlider);
  createSliderOpt2(constants::greenSlider);
  createSliderOpt2(constants::blueSlider);

  createLabelOpt2(constants::boidsNumberSliderLabel);  // index 0
  createLabelOpt2(constants::centerXSliderLabel);      // index 1
  createLabelOpt2(constants::centerYSliderLabel);      // index 2
  createLabelOpt2(constants::redSliderLabel);          // index 3
  createLabelOpt2(constants::greenSliderLabel);        // index 4
  createLabelOpt2(constants::blueSliderLabel);         // index 5
  createLabelOpt2(constants::maxBoidsNumberLabel);     // index 6

  // Value changes when flocks are created or destructed
  option2Labels_[6]->setText("Number of boids: " + std::to_string(10) + "/250");

  setLabelTextOpt2(0, "Create N boids: ");
  setLabelTextOpt2(1, "Center of Spawn X: ");
  setLabelTextOpt2(2, "Center of Spawn Y: ");
  setLabelTextOpt2(3, "Red: ");
  setLabelTextOpt2(4, "Green: ");
  setLabelTextOpt2(5, "Blue: ");

  // HANDLE MAXIMUM VALUE of COLOUR SLIDERS
  option2Sliders_[3]->onValueChange(
      [&]() { handleColorSliderChange(option2Sliders_[3]); });
  option2Sliders_[4]->onValueChange(
      [&]() { handleColorSliderChange(option2Sliders_[4]); });
  option2Sliders_[5]->onValueChange(
      [&]() { handleColorSliderChange(option2Sliders_[5]); });

  createAddFlockButton(constants::addFlockButton);
  createLabelOpt2(constants::addFlockButtonLabel);  // index 7
  addFlockButtonLabel_ = option2Labels_[7];
  addFlockButtonLabel_->setText(
      "Number of flocks: " + std::to_string(flockStack_.size()) + "/5");

  setVisibleOpt2(false);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::setVisibleOpt2(bool visible) {
  for (auto &i : option2Sliders_) {
    i->setVisible(visible);
  }
  for (auto &i : option2Labels_) {
    i->setVisible(visible);
  }
  addFlockButton_->setVisible(visible);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::handleColorSliderChange(tgui::Slider::Ptr changedSlider) {
  int newTotal = static_cast<int>(option2Sliders_[3]->getValue() +
                                  option2Sliders_[4]->getValue() +
                                  option2Sliders_[5]->getValue());

  // 3 is RED, 4 is GREEN, 5 is BLUE

  if (newTotal > constants::colorSliderTotalMax) {
    // If sum exceeds 765, lower current slider value to keep it within bounds
    changedSlider->setValue(
        changedSlider->getValue() -
        static_cast<float>(newTotal - constants::colorSliderTotalMax));
  } else if (newTotal < constants::colorSliderTotalMin) {
    // If sum is below 255, increase current slider value to keep it in bounds
    changedSlider->setValue(
        changedSlider->getValue() +
        static_cast<float>(constants::colorSliderTotalMin - newTotal));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::createAddFlockButton(const TguiPar &par) {
  addFlockButton_ = tgui::Button::create("Create Flock");
  addFlockButton_->setPosition(par.posX, par.posY);
  addFlockButton_->setSize(par.width, par.height);
  addFlockButton_->getRenderer()->setBackgroundColor(
      sf::Color(128, 128, 128));  // Default "off"
  addFlockButton_->getRenderer()->setBackgroundColorHover(
      sf::Color(128, 128, 128));
  addFlockButton_->getRenderer()->setBackgroundColorDown(
      sf::Color(255, 255, 204));

  addFlockButton_->onPress([this]() {
    addFlock(static_cast<size_t>(option2Sliders_[0]->getValue()),
             {option2Sliders_[1]->getValue(), option2Sliders_[2]->getValue()},
             sf::Color(static_cast<uint8_t>(option2Sliders_[3]->getValue()),
                       static_cast<uint8_t>(option2Sliders_[4]->getValue()),
                       static_cast<uint8_t>(option2Sliders_[5]->getValue())));
  });

  gui_.add(addFlockButton_);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::enableCreateFlockButton() {
  if (flockStack_.size() == 5 || getActiveBoids() > 245) {
    // index 0 is boids number
    // index 6 is boids max number

    option2Sliders_[0]->setEnabled(false);

    option2Labels_[0]->setText("Create N boids: Disabled");
    option2Labels_[6]->setText(
        "Number of boids: " + std::to_string(getActiveBoids()) + "/250");

    addFlockButton_->setEnabled(false);

  } else if (getActiveBoids() > 150) {
    option2Sliders_[0]->setMaximum(250 - static_cast<float>(getActiveBoids()));
    option2Sliders_[0]->setEnabled(true);
    option2Labels_[0]->setText(
        "Create N boids: " +
        std::to_string(static_cast<int>(option2Sliders_[0]->getValue())));
    option2Labels_[6]->setText(
        "Number of boids: " + std::to_string(getActiveBoids()) + "/250");

    addFlockButton_->setEnabled(true);

  } else {
    option2Sliders_[0]->setMaximum(100);
    option2Sliders_[0]->setEnabled(true);

    option2Labels_[0]->setText(
        "Create N boids: " +
        std::to_string(static_cast<int>(option2Sliders_[0]->getValue())));
    option2Labels_[6]->setText(
        "Number of boids: " + std::to_string(getActiveBoids()) + "/250");

    addFlockButton_->setEnabled(true);
  }

  assert(flockStack_.size() < 6);
  assert(getActiveBoids() <= 250);
}

//////////////////////////////////////////////////////////////////////////////////////////

size_t Gui::getActiveBoids() {
  size_t activeBoids{};
  for (const auto &flock : flockStack_) {
    activeBoids += flock.getSize();
  }
  return activeBoids;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// OPTION 3

void Gui::createSliderOpt3(const SlidersPar &params) {
  auto slider = tgui::EditBoxSlider::create();
  slider->setPosition(params.posX, params.posY);
  slider->setSize(params.width, params.height);
  slider->setMinimum(params.min);
  slider->setMaximum(params.max);
  slider->setValue(params.initialValue);

  gui_.add(slider);

  option3Sliders_.emplace_back(slider);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::createLabelOpt3(const LabelsPar &labelsPar, const std::string &text) {
  auto label = tgui::Label::create();
  label->setPosition(labelsPar.posX, labelsPar.posY);
  label->setTextSize(labelsPar.textSize);
  label->getRenderer()->setTextColor(sf::Color::Black);
  label->setText(text);
  gui_.add(label);

  option3Labels_.emplace_back(label);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void Gui::setupOpt3() {
  createSliderOpt3(constants::separationSlider);
  createSliderOpt3(constants::separationRangeSlider);
  createSliderOpt3(constants::alignmentSlider);
  createSliderOpt3(constants::cohesionSlider);
  createSliderOpt3(constants::interactionSlider);
  createSliderOpt3(constants::repelSlider);
  createSliderOpt3(constants::repelRangeSlider);
  createSliderOpt3(constants::clickStrengthSlider);
  createSliderOpt3(constants::frameRateLimitSlider);

  createLabelOpt3(constants::separationSliderLabel, "Separation Strength");
  createLabelOpt3(constants::separationRangeSliderLabel, "Separation Range");
  createLabelOpt3(constants::alignmentSliderLabel, "Alignment Strength");
  createLabelOpt3(constants::cohesionSliderLabel, "Cohesion Strength");
  createLabelOpt3(constants::interactionSliderLabel, "Interaction Range");
  createLabelOpt3(constants::repelSliderLabel, "Repel Strength");
  createLabelOpt3(constants::repelRangeSliderLabel, "Repel Range");
  createLabelOpt3(constants::clickStrengthSliderLabel, "Click Strength");
  createLabelOpt3(constants::frameRateLimitSliderLabel, "Frame Rate Limit");
  createLabelOpt3(constants::parametersLabel, "INTERACTION PARAMETERS");
  createLabelOpt3(constants::extraLabel, "ADDITIONAL OPTIONS");

  separationSlider_ = option3Sliders_[0];
  separationRangeSlider_ = option3Sliders_[1];
  alignmentSlider_ = option3Sliders_[2];
  cohesionSlider_ = option3Sliders_[3];
  interactionSlider_ = option3Sliders_[4];
  repelSlider_ = option3Sliders_[5];
  repelRangeSlider_ = option3Sliders_[6];
  clickStrengthSlider_ = option3Sliders_[7];
  frameRateLimitSlider_ = option3Sliders_[8];

  // Set up action on click
  separationSlider_->onValueChange([this]() {
    Flock::setSeparationStrength(separationSlider_->getValue() /
                                 constants::scalingFactor);
  });

  separationRangeSlider_->onValueChange([this]() {
    Flock::setSeparationRange(separationRangeSlider_->getValue());
  });

  alignmentSlider_->onValueChange([this]() {
    Flock::setAlignmentStrength(alignmentSlider_->getValue() /
                                constants::scalingFactor);
  });

  cohesionSlider_->onValueChange([this]() {
    Flock::setCohesionStrength(cohesionSlider_->getValue() /
                               constants::scalingFactor);
  });

  interactionSlider_->onValueChange(
      [this]() { Flock::setInteractionRange(interactionSlider_->getValue()); });

  repelSlider_->onValueChange([this]() {
    Flock::setRepelStrength(repelSlider_->getValue() /
                            constants::scalingFactor);
  });

  repelRangeSlider_->onValueChange(
      [this]() { Flock::setRepelRange(repelRangeSlider_->getValue()); });

  clickStrengthSlider_->onValueChange([this]() {
    Flock::setClickStrength(clickStrengthSlider_->getValue() /
                            constants::scalingFactor);
  });

  frameRateLimitSlider_->onValueChange([this]() {
    window_.setFramerateLimit(
        static_cast<unsigned>(frameRateLimitSlider_->getValue()));
  });

  // Create switchbuttons and assign actions
  toroidalButton_ = SwitchButton::create(constants::toroidalButton);
  toroidalButton_->setOffAction(
      []() -> void { Flock::setToroidalMode(false); });
  toroidalButton_->setOnAction([]() -> void { Flock::setToroidalMode(true); });

  repulsiveClickButton_ =
      SwitchButton::create(constants::clickInteractionButton);
  repulsiveClickButton_->setOffAction(
      []() -> void { Flock::setRepulsiveClick(false); });
  repulsiveClickButton_->setOnAction(
      []() -> void { Flock::setRepulsiveClick(true); });

  gui_.add(toroidalButton_);
  gui_.add(repulsiveClickButton_);

  setVisibleOpt3(false);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::setVisibleOpt3(bool visible) {
  for (auto &i : option3Sliders_) {
    i->setVisible(visible);
  }
  for (auto &i : option3Labels_) {
    i->setVisible(visible);
  }
  toroidalButton_->setVisible(visible);
  repulsiveClickButton_->setVisible(visible);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void Gui::addFlock(size_t n, sf::Vector2f center, sf::Color color) {
  if (flockStack_.size() < constants::maxFlockNumber) {
    flockStack_.emplace_back(createFlock(n, center, color));
    createDeleteFlockButton(flockStack_.size() - 1);
    addFlockButtonLabel_->setText(
        "Number of flocks: " + std::to_string(flockStack_.size()) + "/5");

    for (auto &labels : dynamicLabels_) {
      for (size_t i{0}; i < 4; i++) {
        labels[i]->setVisible(false);
      }
    }

    for (size_t i = 0; i < dynamicButtons_.size(); ++i) {
      dynamicButtons_[i]->setVisible(false);
    }

  } else {
    std::cout << "There are already 5 flocks!\n";
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::deleteFlock(size_t i) {
  flockStack_.erase(flockStack_.begin() + static_cast<long>(i));
  addFlockButtonLabel_->setText(
      "Number of flocks: " + std::to_string(flockStack_.size()) + "/5");
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::evolveFlocks() {
  for (size_t i{0}; i < flockStack_.size(); i++) {
    flockStack_[i].updateFlock(repel(flockStack_, i));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
// Interact with left click

void Gui::interactWithFlocks() {
  int max{static_cast<int>(constants::fieldSide + 2 * constants::marginSize)};

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
    for (auto &i : flockStack_) {
      if ((mousePos.x > 0) && (mousePos.x < max) && (mousePos.y > 0) &&
          (mousePos.y < max))
        i.repelOnClick(
            {static_cast<float>(mousePos.x) - constants::marginSize,
             static_cast<float>(mousePos.y) - constants::marginSize});
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////

void Gui::drawFlocks() {
  bodyStack_.resize(flockStack_.size());

  for (size_t i{0}; i < bodyStack_.size(); i++) {
    bodyStack_[i].clear();
    sf::Color color{flockStack_[i].getFlockColor()};

    for (size_t j{0}; j < flockStack_[i].getSize(); j++) {
      bodyStack_[i].emplace_back(
          getTriangleBoid(flockStack_[i].getBoid(j), color));
      window_.draw(bodyStack_[i][j]);
    }
  }
}

}  // namespace ev

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////