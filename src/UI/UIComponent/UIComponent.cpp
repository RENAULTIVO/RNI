#include "UIComponent.hpp"
#include "../../Core/Core.hpp"
#include "../../Animations/Transition/Transition.cpp"

UIComponent::UIComponent(
  std::string id,
  std::string name,
  float x, float y,
  float width, float height,
  Color *backgroundColor,
  Color *borderColor
) {

  this->id = id;
  this->name = name;
  this->backgroundColor = backgroundColor;
  this->borderColor = borderColor;

  if (width >= 0) {
    this->props.isWidthAuto = false;
    this->props.width = width;
  }

  if (height >= 0) {
    this->props.isHeightAuto = false;
    this->props.height = height;
  }

  windowRect.x = x;
  windowRect.y = y;
  windowRect.w = width;
  windowRect.h = height;

  if (x > 0) {
    this->props.offsetTop = x;
  }

  if (y > 0) {
  this->props.offsetLeft = y;
  }

  this->props.offsetChanged = true;
  
}

std::string UIComponent::getID() {
  return this->id;
}

std::string UIComponent::getName() {
  return this->name;
}

void UIComponent::render() {
  
  if (this->props.isWidthAuto) {

    this->windowRect.w = 0;

    for (int i=0; i<children.size(); i++) {
      UIMargin *childMargins = children[i]->getMargins();
      this->windowRect.w += children[i]->getWidth() + childMargins->left + childMargins->right;
    }

  }
  
  if (this->props.isHeightAuto) {

    this->windowRect.h = 0;

    for (int i=0; i<children.size(); i++) {
      this->windowRect.h += children[i]->getHeight();
    }

  }

  SDL_SetRenderDrawColor(
    Core::getInstance()->getRenderer(),
    this->backgroundColor->red,
    this->backgroundColor->green,
    this->backgroundColor->blue,
    this->backgroundColor->alpha
  );

  SDL_RenderFillRect(Core::getInstance()->getRenderer(), &windowRect);

  SDL_SetRenderDrawColor(
    Core::getInstance()->getRenderer(),
    this->borderColor->red,
    this->borderColor->green,
    this->borderColor->blue,
    this->borderColor->alpha
  );

  SDL_RenderDrawRect(Core::getInstance()->getRenderer(), &windowRect);

  for (int i=0; i<children.size(); i++) {
    children[i]->render();
  }

}

// TODO
void UIComponent::moveX(float moviment) {
  std::cout<<"TODO: UIComponent::moveX(float moviment);"<<std::endl;
  exit(EXIT_FAILURE);
}

// TODO
void UIComponent::moveY(float moviment) {
  std::cout<<"TODO: UIComponent::moveY(float moviment);"<<std::endl;
  exit(EXIT_FAILURE);
}

void UIComponent::setX(float x) {

  this->windowRect.x = x;

  for (int i=0; i<children.size(); i++) {
    children[i]->onParentOffsetChange();
  }

}

void UIComponent::setY(float y) {
  
  this->windowRect.y = y;

  for (int i=0; i<children.size(); i++) {
    children[i]->onParentOffsetChange();
  }

}

float UIComponent::getX() {
  return this->windowRect.x;
}

float UIComponent::getY() {
  return this->windowRect.y;
}

float UIComponent::getWidth() {
  return this->props.width;
}

float UIComponent::getHeight() {
  return this->props.height;
}

float UIComponent::getOffsetWidth() {
  return this->windowRect.w;
}

float UIComponent::getOffsetHeight() {
  return this->windowRect.h;
}

void UIComponent::setMaxWidth(float maxWidth) {
  this->props.maxWidth = maxWidth;
}

void UIComponent::setMargin(float margin) {
  this->props.margin.top = margin;
  this->props.margin.left = margin;
  this->props.margin.right = margin;
  this->props.margin.bottom = margin;
}

void UIComponent::setMargin(float vertical, float horizontal) {
  this->props.margin.top = vertical;
  this->props.margin.left = horizontal;
  this->props.margin.right = horizontal;
  this->props.margin.bottom = vertical;
}

void UIComponent::setMargin(float top, float right, float bottom, float left) {
  this->props.margin.top = top;
  this->props.margin.left = left;
  this->props.margin.right = right;
  this->props.margin.bottom = bottom;
}

UIMargin *UIComponent::getMargins() {
  return &this->props.margin;
}

bool UIComponent::isMouseDown() {
  return this->mouseState.isDown;
}

bool UIComponent::isDraggable() {
  return this->props.isDraggable;
}

bool UIComponent::isMouseHovering() {
  return this->mouseState.isHovering;
}

void UIComponent::setAsDraggable(bool draggable) {
  this->props.isDraggable = draggable;
}

void UIComponent::onMouseUp(SDL_Event *event) {
  this->mouseState.isDown = false;

  for (int i=children.size()-1; i>=0; i--) {
    children[i]->onMouseUp(event);
  }

}

void UIComponent::onMouseMove(SDL_Event *event) {
  
  unsigned short int x = event->motion.x;
  unsigned short int y = event->motion.y;

  for (int i=children.size()-1; i>=0; i--) {

    if (x > children[i]->getX()
    && x < (children[i]->getX() + children[i]->getWidth())
    && y > children[i]->getY()
    && y < (children[i]->getY() + children[i]->getHeight())) {

      if (!children[i]->isMouseHovering()) {
        children[i]->onMouseEnter(event);
      }

      children[i]->onMouseMove(event);

    } else if (children[i]->isMouseHovering()) {
      children[i]->onMouseLeave(event);
    }

    if (children[i]->isMouseDown()
      && children[i]->isDraggable()) {

      children[i]->setX(
        children[i]->getX() - (children[i]->props.lastX - event->motion.x)
      );

      children[i]->setY(
        children[i]->getY() - (children[i]->props.lastY - event->motion.y)
      );
      
      children[i]->props.lastX = event->motion.x;
      children[i]->props.lastY = event->motion.y;

    }

  }

}

void UIComponent::onMouseDown(SDL_Event *event) {
  this->mouseState.isDown = true;
  this->props.lastX = event->motion.x;
  this->props.lastY = event->motion.y;
  
  unsigned short int x = event->motion.x;
  unsigned short int y = event->motion.y;
  
  for (int i=children.size()-1; i>=0; i--) {

    if (x > children[i]->getX()
    && x < (children[i]->getX() + children[i]->getWidth())
    && y > children[i]->getY()
    && y < (children[i]->getY() + children[i]->getHeight())) {
      children[i]->onMouseDown(event);
      break;
    }

  }


}

void UIComponent::onMouseEnter(SDL_Event *event) {
  this->mouseState.isHovering = true;
  std::cout<<"Mouse enter event on: "<<this->name<<std::endl;

  this->backgroundColor->blue = 100;

}

void UIComponent::onMouseLeave(SDL_Event *event) {

  if (this->mouseState.isDown
  && this->props.isDraggable) {
    return;
  }

  this->mouseState.isDown = false;
  this->mouseState.isHovering = false;
  std::cout<<"Mouse leave event on: "<<this->name<<std::endl;

  this->backgroundColor->blue = 0;

  /*Transition *transtion = new Transition(this);
  transtion->setInitialValue(this->getX());
  transtion->setTargetValue(Engine::getInstance()->getScreenWidth()-20);
  transtion->setOnChangeListener([](UIComponent *component, float currentValue) {
    std::cout<<"Running Animation... CurrentValue: "<<currentValue<<std::endl;
    component->setX(currentValue);
  });
  transtion->setDuration(10);
  transtion->start();*/

}


void UIComponent::onParentOffsetChange(float x, float y) {

  this->setX(x);
  this->setY(y);

  for (int i=0; i<children.size(); i++) {
    children[i]->onParentOffsetChange();
  }
  
}

void UIComponent::onParentOffsetChange() {

  this->setX(this->props.offsetTop + this->parent->getX() + this->props.margin.left);
  this->setY(this->props.offsetLeft + this->parent->getY() + this->props.margin.top);

  for (int i=0; i<children.size(); i++) {
    children[i]->onParentOffsetChange();
  }

}

void UIComponent::setParent(UIComponent *parent) {
  this->parent = parent;
  this->windowRect.x = this->windowRect.x + parent->getX() + this->props.margin.left;
  this->windowRect.y = this->windowRect.y + parent->getY() + this->props.margin.top;

  for (int i=0; i<children.size(); i++) {
    children[i]->onParentOffsetChange();
  }

}

UIComponent *UIComponent::appendChild(UIComponent *component) {
  component->setParent(this);
  this->children.push_back(component);
  return this;
}

UIComponent *UIComponent::appendChild(std::vector<UIComponent*> componentList) {
  
  for (int i=0; i<componentList.size(); i++) {
    componentList[i]->setParent(this);
    this->children.push_back(componentList[i]);
  }

  return this;

}
