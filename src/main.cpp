#include <iostream>
#include "./Engine/Engine.cpp"

int main(int argc, char **argv) {

  Engine::getInstance()->init("Game Engine", 1280, 800);
  
  while (Engine::getInstance()->isRunning()) {
    Engine::getInstance()->events();
    Engine::getInstance()->render();
  }

  return 0;

}