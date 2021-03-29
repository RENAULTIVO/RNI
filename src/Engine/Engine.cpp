#include <iostream>
#include <time.h>
#include "Engine.hpp"
#include "../Graphics/TextureManager.cpp"
#include "../Events/EventHandler.cpp"
#include "../UI/UIManager/UIManager.cpp"

Engine *Engine::instance = nullptr;

Engine::Engine() {
  
}

Engine *Engine::getInstance() {

  if (instance == nullptr) {
    instance = new Engine();
  }

  return instance;

}

void Engine::init(
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
    0
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

  UIManager::getInstance()->addComponent(new UIComponent(
    "topLeft",
    "My Component",
    0, 0,
    250, 200
  ));

  UIComponent *rightMenu = new UIComponent(
    "rightMenu",
    "My Component",
    this->getScreenWidth() - 250, 0,
    250, height
  );

  rightMenu->addChildren(new UIComponent(
    "topButton",
    "Top Button",
    10, 10,
    100, 100,
    new Color(255, 255, 255)
  ));

  UIManager::getInstance()->addComponent(rightMenu);

  UIManager::getInstance()->addComponent(new UIComponent(
    "bottomLeft",
    "My Component",
    0, this->getScreenHeight() - 200,
    250, 200
  ));

  SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255);
  SDL_RenderClear(renderer);

}

void Engine::events() {
  EventHandler::getInstance()->listen();
}

void Engine::quit() {
  SDL_Quit();
  IMG_Quit();
  exit(EXIT_SUCCESS);
}

bool Engine::isRunning() {
  return state.isRunning;
}

unsigned short int Engine::getScreenWidth() {
  return this->width;
}

unsigned short int Engine::getScreenHeight() {
  return this->height;
}

// S 000000
// 1000000
// 4.166.163

// 60

void Engine::render() {

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

SDL_Window *Engine::getWindow() {
  return window;
}

SDL_Renderer *Engine::getRenderer() {
  return renderer;
}
