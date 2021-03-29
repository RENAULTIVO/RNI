#ifndef INPUT_HPP
#define INPUT_HPP
#include <iostream>
#include <SDL2/SDL.h>

class Input {

  private:
    Input();
    const u_int8_t *states;
    void onKeyUp();
    void onKeyDown();
    static Input *instance;

  public:
    void keyPressed();
    bool isKeyPressed(SDL_Scancode keyCode);
    static Input *getInstance();

};

#endif