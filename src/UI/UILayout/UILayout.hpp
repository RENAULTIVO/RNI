#ifndef UILAYOUT_HPP
#define UILAYOUT_HPP

namespace UIDisplay {
  static const int BLOCK = 0;
  static const int NONE = 1;
  static const int FLEX = 2;
};

namespace UISize {
  static const int AUTO = -1;
};

typedef struct UIMargin {
  int top = 0;
  int left = 0;
  int right = 0;
  int bottom = 0;
} UIMargin;

typedef struct UIPadding {
  int top = 0;
  int left = 0;
  int right = 0;
  int bottom = 0;
} UIPadding;

typedef struct UIScroll {
  bool vertical = true;
  bool horizontal = true;
} UIScroll;

class UILayout {

  public:


};

#endif