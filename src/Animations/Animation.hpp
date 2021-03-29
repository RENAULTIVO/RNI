#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "../UI/UIComponent/UIComponent.hpp"

namespace Animation {
  typedef int milliseconds;
  typedef void (*loop)(float);
  typedef void (*eventListener)(UIComponent*, float);
};

#endif