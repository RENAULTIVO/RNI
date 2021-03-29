#include "UIComponent.hpp"
#include "../../Engine/Engine.hpp"
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

  windowRect.x = x;
  windowRect.y = y;
  windowRect.w = width;
  windowRect.h = height;

  this->props.top = y;
  this->props.left = y;
  this->props.offsetChanged = true;
  
}

std::string UIComponent::getID() {
  return this->id;
}

std::string UIComponent::getName() {
  return this->name;
}

void UIComponent::render() {
  
  SDL_SetRenderDrawColor(
    Engine::getInstance()->getRenderer(),
    this->backgroundColor->red,
    this->backgroundColor->green,
    this->backgroundColor->blue,
    this->backgroundColor->alpha
  );

  SDL_RenderFillRect(Engine::getInstance()->getRenderer(), &windowRect);

  SDL_SetRenderDrawColor(
    Engine::getInstance()->getRenderer(),
    this->borderColor->red,
    this->borderColor->green,
    this->borderColor->blue,
    this->borderColor->alpha
  );

  SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &windowRect);

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

void UIComponent::setZIndex(short int zIndex) {
  this->zIndex = zIndex;
}

void UIComponent::setX(float x) {
  this->windowRect.x = x + parent->getX();
}

void UIComponent::setY(float y) {
  this->windowRect.y = y + parent->getY();
}

float UIComponent::getX() {
  return this->windowRect.x;
}

float UIComponent::getY() {
  return this->windowRect.y;
}

float UIComponent::getWidth() {
  return this->windowRect.w;
}

float UIComponent::getHeight() {
  return this->windowRect.h;
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

void UIComponent::onMouseUp(SDL_Event *event) {
  this->mouseState.isDown = false;
}

void UIComponent::onMouseMove(SDL_Event *event) {
  
  if (this->mouseState.isDown) {
    
    /*this->windowRect.x -= (lastX - event->motion.x);
    this->windowRect.y -= (lastY - event->motion.y);

    this->lastX = event->motion.x;
    this->lastY = event->motion.y;*/

  }

}


void UIComponent::onMouseDown(SDL_Event *event) {
  this->mouseState.isDown = true;
  this->lastX = event->motion.x;
  this->lastY = event->motion.y;
}

void UIComponent::onMouseEnter(SDL_Event *event) {
  this->mouseState.isHovering = true;
}

void UIComponent::onMouseLeave(SDL_Event *event) {
  this->mouseState.isDown = false;
  this->mouseState.isHovering = false;

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

void UIComponent::setParent(UIComponent *parent) {
  this->parent = parent;
  this->windowRect.x = this->windowRect.x + parent->getX();
  this->windowRect.y = this->windowRect.y + parent->getY();
}

void UIComponent::addChildren(UIComponent *component) {
  component->setParent(this);
  this->children.push_back(component);
}
