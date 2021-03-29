#ifndef UICOMPONENT_HPP
#define UICOMPONENT_HPP
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "../Color/Color.hpp"
#include "../../Input/Mouse/Mouse.hpp"

struct UIComponentProperties {
  float top = 0;
  float left = 0;
  bool offsetChanged = false;
  bool isDraggable = false;
};

class UIComponent {

  private:

    short int zIndex = 0;
    std::string id;
    std::string name;
    Color *borderColor;
    Color *backgroundColor;
    MouseState mouseState;
    SDL_Rect windowRect;
    UIComponent *parent;
    std::vector<UIComponent*> children;
    UIComponentProperties props;

  public:
    int lastX;
    int lastY;

    UIComponent(
      std::string id,
      std::string name,
      float x, float y,
      float width, float height,
      Color *backgroundColor = new Color(22, 22, 22, 255),
      Color *borderColor = new Color(255, 215, 0, 255)
    );

    std::string getID();
    std::string getName();

    void render();
    
    void moveX(float moviment);
    void moveY(float moviment);

    void setZIndex(short int zIndex);

    void setX(float x);
    void setY(float y);

    float getX();
    float getY();

    float getWidth();
    float getHeight();

    bool isMouseDown();
    bool isDraggable();
    bool isMouseHovering();

    void onMouseEnter(SDL_Event *event);
    void onMouseLeave(SDL_Event *event);

    void onWheel(SDL_Event *event);
    void onMouseUp(SDL_Event *event);
    void onMouseMove(SDL_Event *event);
    void onMouseDown(SDL_Event *event);
    void onContextMenu(SDL_Event *event);

    void setParent(UIComponent *parent);
    void addChildren(UIComponent *component);

};

#endif