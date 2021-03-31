#include "EventHandler.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include "../Input/Input.cpp"
#include "../Graphics/TextureManager.hpp"
#include "../UI/UIManager/UIManager.hpp"

EventHandler *EventHandler::instance = nullptr;

EventHandler *EventHandler::getInstance() {

  if (instance == nullptr) {
    instance = new EventHandler();
  }

  return instance;

}

long double eventCounter = 0;

void EventHandler::listen() {
  
  SDL_Event event;

  while (SDL_PollEvent(&event)) {

    eventCounter++;

    //std::cout<<"MouseMotion = { x: "<<event.motion.x<<", y: "<<event.motion.y<<" }"<<std::endl;
    
    switch (event.type) {
      case SDL_QUIT:
        Core::getInstance()->quit();
        break;
      case SDL_KEYDOWN: {
        Input::getInstance()->keyPressed();
        break;
      }
      case SDL_MOUSEBUTTONDOWN: {
        UIManager::getInstance()->onMouseDown(&event);
        break;
      }
      case SDL_MOUSEBUTTONUP: {
        UIManager::getInstance()->onMouseUp(&event);
        break;
      }
      case SDL_MOUSEMOTION: {
        UIManager::getInstance()->onMouseMove(&event);
        /*
          int x;
          int y;

          SDL_GetMouseState(&x, &y);
          //SDL_GetGlobalMouseState(&x, &y);
          std::cout<<"MouseMotion = { x: "<<x<<", y: "<<y<<" }\n";
        */
        break;
      }
      case SDL_WINDOWEVENT:

        switch (event.window.event) {
          case SDL_WINDOWEVENT_SIZE_CHANGED:
            break;
          default:
            break;
        }

        Core::getInstance()->onResize(&event);
      default:
        break;
    }

  }

}
