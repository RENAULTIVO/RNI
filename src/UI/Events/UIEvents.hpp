#ifndef UIEVENTS_HPP
#define UIEVENTS_HPP
#include <iostream>

namespace UIEventProperties {

  typedef struct Mouse {
    int x;
    int y;
  };

  typedef struct Keyboard {
    int keyCode;
    std::string key;
    std::string event;
  };
  

};

namespace UIEvents {
  typedef void (*MouseEvent)(UIEventProperties::Mouse*);
};

#endif