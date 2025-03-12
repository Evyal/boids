#ifndef SWITCHBUTTON_HPP
#define SWITCHBUTTON_HPP

#include "structs.hpp"
#include <SFML/Graphics/Color.hpp>
#include <TGUI/TGUI.hpp>
#include <memory>

class SwitchButton : public tgui::Button {
private:
  bool isOn_{false}; // Internal state
  std::string onText_;
  std::string offText_;

  sf::Color onColor_;
  sf::Color offColor_;

  std::function<void()> onAction_;
  std::function<void()> offAction_;

  void init(const SwitchButtonPar &par);
  void toggle();

public:
  SwitchButton(const SwitchButtonPar &par);
  static std::shared_ptr<SwitchButton> create(const SwitchButtonPar &par);

  void setState(bool state);
  bool getState() const;

  void setOnAction(std::function<void()> &&action);
  void setOffAction(std::function<void()> &&action);
};

#endif // SWITCHBUTTON_HPP
