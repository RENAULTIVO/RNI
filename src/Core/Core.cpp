#include <iostream>
#include <time.h>
#include "Core.hpp"
#include "../Graphics/TextureManager.cpp"
#include "../Events/EventHandler.cpp"
#include "../UI/UIManager/UIManager.cpp"

Core *Core::instance = nullptr;

Core::Core() {
  
}

Core *Core::getInstance() {

  if (instance == nullptr) {
    instance = new Core();
  }

  return instance;

}

void Core::init(
  std::string name,
  unsigned short int width,
  unsigned short int height
) {

  this->name = name;
  this->width = width;
  this->height = height;

  // SDL_Init returns 0 on success
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Failed to initialize SDL: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // IMG_Init returns 0 on failure
  if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
    printf("Failed to initialize IMG: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  window = SDL_CreateWindow(
    this->name.c_str(),
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    this->width, this->height,
    SDL_WINDOW_RESIZABLE
  );

  if (window == nullptr) {
    printf("Failed to create window: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  if (renderer == nullptr) {
    printf("Failed to create window: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  state.isRunning = true;

  TextureManager::getInstance()->load("tree", "../assets/tree.png");

/*std::string id,
  std::string name,
  float x, float y,
  float width, float height,*/

  SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255);
  SDL_RenderClear(renderer);

}

void Core::events() {
  EventHandler::getInstance()->listen();
}

void Core::quit() {
  SDL_Quit();
  IMG_Quit();
  exit(EXIT_SUCCESS);
}

bool Core::isRunning() {
  return state.isRunning;
}

void Core::onResize(SDL_Event *event) {

  

}

unsigned short int Core::getScreenWidth() {
  return this->width;
}

unsigned short int Core::getScreenHeight() {
  return this->height;
}

// S 000000
// 1000000
// 4.166.163

// 60

void Core::render() {

  /*TextureManager::getInstance()->draw(
    "tree",
    0, 0,
    1100, 823
  );*/

  SDL_RenderPresent(renderer);

  SDL_SetRenderDrawColor(renderer, 22, 22, 22, 255);
  SDL_RenderClear(renderer);

  UIManager::getInstance()->render();

  //uiComponent->render();

}

SDL_Window *Core::getWindow() {
  return window;
}

SDL_Renderer *Core::getRenderer() {
  return renderer;
}
