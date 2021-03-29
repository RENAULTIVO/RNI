#include "Input.hpp"
#include "../Engine/Engine.hpp"

Input *Input::instance = nullptr;

Input::Input () {
  
}

Input *Input::getInstance() {

  if (instance == nullptr) {
    instance = new Input();
  }

  return instance;

}

void Input::keyPressed() {
  states = SDL_GetKeyboardState(nullptr);
}

bool isKeyPressed(SDL_Scancode keyCode) {
  return false;
}
