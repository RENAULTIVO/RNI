#ifndef FLEXBOX_HPP
#define FLEXBOX_HPP
#include <iostream>
#include <vector>
#include "../../UIComponent/UIComponent.hpp"

namespace FlexBoxProperties {
  static const short int END = 2;
  static const short int START = 1;
  static const short int CENTER = 0;
  static const short int WRAP = 0;
};

class FlexBox {

  public:
    FlexBox();
    int alignItems = FlexBoxProperties::CENTER;
    int justifyContent = FlexBoxProperties::CENTER;

    void applyRules(
      UIComponent *parent,
      std::vector<UIComponent *> children
    );

};

#endif