#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct EngineState {
  bool isRunning;
};

class Core {

  private:
    Core();
    static Core *instance;

    EngineState state;

    std::string name;
    unsigned short int width;
    unsigned short int height;

    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer *renderer;

  public:

    void init(
      std::string name,
      unsigned short int width,
      unsigned short int height
    );

    void render();
    void quit();
    void events();
    void update();
    bool isRunning();
    void onResize(SDL_Event *event);

    unsigned short int getScreenWidth();
    unsigned short int getScreenHeight();

    SDL_Window *getWindow();
    SDL_Renderer *getRenderer();

    static Core *getInstance();
};

#endif