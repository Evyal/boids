#include "switchbutton.hpp"

#include "structs.hpp"

namespace ev {

////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR

SwitchButton::SwitchButton(const SwitchButtonPar &par) : isOn_(false) {
  init(par);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// CREATE

std::shared_ptr<SwitchButton> SwitchButton::create(const SwitchButtonPar &par) {
  return std::make_shared<SwitchButton>(par);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// INITIALIZE

void SwitchButton::init(const SwitchButtonPar &par) {
  setPosition(par.posX, par.posY);
  setSize(par.width, par.height);

  onText_ = par.onText;
  offText_ = par.offText;
  onColor_ = par.onColor;
  offColor_ = par.offColor;

  setText(offText_);
  getRenderer()->setBackgroundColor(offColor_);
  getRenderer()->setBackgroundColorHover(offColor_);
  getRenderer()->setBackgroundColorDown(offColor_);

  onPress([this]() -> void { toggle(); });
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION of TOGGLE FUNTIONALITY

void SwitchButton::toggle() {
  isOn_ = !isOn_;

  if (isOn_) {
    setText(onText_);
    if (onAction_) {
      onAction_();
    }
    getRenderer()->setBackgroundColor(onColor_);
    getRenderer()->setBackgroundColorHover(onColor_);
    getRenderer()->setBackgroundColorDown(onColor_);
  } else {
    setText(offText_);
    if (offAction_) {
      offAction_();
    }
    getRenderer()->setBackgroundColor(offColor_);
    getRenderer()->setBackgroundColorHover(offColor_);
    getRenderer()->setBackgroundColorDown(offColor_);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void SwitchButton::setState(bool state) {
  if (isOn_ != state) toggle();
}
bool SwitchButton::getState() const { return isOn_; }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Add further functionality when switched to ON

void SwitchButton::setOnAction(std::function<void()> &&action) {
  onAction_ = action;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Add further functionality when switched to OFF

void SwitchButton::setOffAction(std::function<void()> &&action) {
  offAction_ = action;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace ev