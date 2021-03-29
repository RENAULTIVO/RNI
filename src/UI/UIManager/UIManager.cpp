#include "UIManager.hpp"

UIManager *UIManager::instance = nullptr;

UIManager::UIManager() {
  
}

UIManager *UIManager::getInstance() {

  if (instance == nullptr) {
    instance = new UIManager();
  }

  return instance;

}

void UIManager::addComponent(UIComponent *component) {
  components.push_back(component);
}


void UIManager::render() {

  for (unsigned short int i=0; i<components.size(); i++) {
    components[i]->render();
  }

}


void UIManager::onMouseMove(SDL_Event *event) {

  unsigned short int x = event->motion.x;
  unsigned short int y = event->motion.y;

  for (unsigned short int i=0; i<components.size(); i++) {

    if (x > components[i]->getX()
    && x < (components[i]->getX() + components[i]->getWidth())
    && y > components[i]->getY()
    && y < (components[i]->getY() + components[i]->getHeight())) {

      if (!components[i]->isMouseHovering()) {
        components[i]->onMouseEnter(event);
      }

      components[i]->onMouseMove(event);
    
    } else if (components[i]->isMouseHovering()) {
      components[i]->onMouseLeave(event);
    }

    if (components[i]->isMouseDown()
      && components[i]->isDraggable()) {

        components[i]->setX(
          components[i]->getX() - (components[i]->lastX - event->motion.x)
        );

        components[i]->setY(
          components[i]->getY() - (components[i]->lastY - event->motion.y)
        );
        
        components[i]->lastX = event->motion.x;
        components[i]->lastY = event->motion.y;

      }

  }

  //std::cout<<"UIManager::onMouseMove: { x: "<<x<<", y: "<<y<<"}"<<std::endl;

}

void UIManager::onMouseDown(SDL_Event *event) {

  unsigned short int x = event->motion.x;
  unsigned short int y = event->motion.y;

  for (int i=components.size()-1; i>=0; i--) {

    if (x > components[i]->getX()
      && x < (components[i]->getX() + components[i]->getWidth())
      && y > components[i]->getY()
      && y < (components[i]->getY() + components[i]->getHeight())) {

      components[i]->onMouseDown(event);

      UIComponent *temp = components[i];

        for (int z=i; z<components.size()-1; z++) {
          components[z] = components[z+1];
        }

        components[components.size()-1] = temp;

      break;

    }

  }

  //std::cout<<"UIManager::onMouseDown: { x: "<<x<<", y: "<<y<<"}"<<std::endl;

}

void UIManager::onMouseUp(SDL_Event *event) {

  unsigned short int x = event->motion.x;
  unsigned short int y = event->motion.y;

  for (unsigned short int i=0; i<components.size(); i++) {

    if (x > components[i]->getX()
      && x < (components[i]->getX() + components[i]->getWidth())
      && y > components[i]->getY()
      && y < (components[i]->getY() + components[i]->getHeight())) {
      components[i]->onMouseUp(event);
    }

  }

  //std::cout<<"UIManager::onMouseUp: { x: "<<x<<", y: "<<y<<"}"<<std::endl;

}


