#ifndef SWITCHBUTTON_HPP
#define SWITCHBUTTON_HPP

#include "structs.hpp"
#include <SFML/Graphics/Color.hpp>
#include <TGUI/TGUI.hpp>
#include <memory>

class SwitchButton : public tgui::Button {
private:
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  // ON OFF SWITCH
  bool isOn_{false};

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  // Initialize Values
  std::string onText_;
  std::string offText_;

  sf::Color onColor_;
  sf::Color offColor_;

  std::function<void()> onAction_;
  std::function<void()> offAction_;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  // INITIALIZE
  void init(const SwitchButtonPar &par);
  void toggle();

public:
  // DEFAULT CONSTRUCTOR
  SwitchButton(const SwitchButtonPar &par);
  // CREATE FUNCTION that returns a SHARED POINTER - Following TGUI conventions.
  static std::shared_ptr<SwitchButton> create(const SwitchButtonPar &par);

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  // SETTER and GETTER for the STATE
  void setState(bool state);
  bool getState() const;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  // SETTERS to implement specific action for a button to perform
  void setOnAction(std::function<void()> &&action);
  void setOffAction(std::function<void()> &&action);
};

#endif // SWITCHBUTTON_HPP
