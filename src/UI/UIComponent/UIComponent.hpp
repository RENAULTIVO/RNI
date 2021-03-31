#ifndef UICOMPONENT_HPP
#define UICOMPONENT_HPP
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "../UILayout/UILayout.hpp"
#include "../Color/Color.hpp"
#include "../../Input/Mouse/Mouse.hpp"

struct UIComponentProperties {
  int lastX = 0;
  int lastY = 0;
  int zIndex = 0;
  int scrollX = 0;
  int scrollY = 0;
  int width = UISize::AUTO;
  int height = UISize::AUTO;
  int maxWidth = UISize::AUTO;
  int maxHeight = UISize::AUTO;
  bool isWidthAuto = true;
  bool isHeightAuto = true;
  UIMargin margin;
  UIPadding padding;
  float offsetTop = 0;
  float offsetLeft = 0;
  bool offsetChanged = false;
  bool isDraggable = false;
};

class UIComponent {

  private:
    std::string id;
    std::string name;
    Color *borderColor;
    Color *backgroundColor;
    MouseState mouseState;
    SDL_Rect windowRect;
    UIComponent *parent;
    std::vector<UIComponent*> children;

  public:

    UIComponent(
      std::string id,
      std::string name,
      float x, float y,
      float width = UISize::AUTO, float height = UISize::AUTO,
      Color *backgroundColor = new Color(22, 22, 22, 255),
      Color *borderColor = new Color(255, 215, 0, 255)
    );

    UIComponentProperties props;

    std::string getID();
    std::string getName();

    void render();
    
    void moveX(float moviment);
    void moveY(float moviment);

    void setX(float x);
    void setY(float y);

    float getX();
    float getY();

    float getWidth();
    float getHeight();

    float getOffsetWidth();
    float getOffsetHeight();

    void setMaxWidth(float maxWidth);

    void setMargin(float margin);
    void setMargin(float vertical, float horizontal);
    void setMargin(float top, float right, float bottom, float left);

    UIMargin *getMargins();

    bool isMouseDown();
    bool isDraggable();
    bool isMouseHovering();

    void setAsDraggable(bool draggable);

    void onMouseEnter(SDL_Event *event);
    void onMouseLeave(SDL_Event *event);

    void onWheel(SDL_Event *event);
    void onMouseUp(SDL_Event *event);
    void onMouseMove(SDL_Event *event);
    void onMouseDown(SDL_Event *event);
    void onContextMenu(SDL_Event *event);

    void onParentOffsetChange();
    void onParentOffsetChange(float x, float y);

    void setParent(UIComponent *parent);
    UIComponent *appendChild(UIComponent *component);
    UIComponent *appendChild(std::vector<UIComponent*> componentList);

};

#endif