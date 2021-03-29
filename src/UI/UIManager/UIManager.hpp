#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP
#include <iostream>
#include <vector>
#include "../UIComponent/UIComponent.cpp"

class UIManager {

  private:
    UIManager();
    std::vector<UIComponent*> components;
    static UIManager *instance;

  public:
    void addComponent(UIComponent *component);
    void render();

    void onMouseUp(SDL_Event *event);
    void onMouseMove(SDL_Event *event);
    void onMouseDown(SDL_Event *event);

    static UIManager *getInstance();

};

#endif