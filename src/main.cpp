#include <iostream>
#include "./Core/Core.cpp"

int main(int argc, char **argv) {

  Core::getInstance()->init("RenaultivoNI", 1280, 800);

  UIComponent *rightMenu = new UIComponent(
    "rightMenu",
    "My Component",
    Core::getInstance()->getScreenWidth() - 250, 0
  );

  UIComponent *leftButton =  new UIComponent(
    "leftButton",
    "Left Button",
    0, 0,
    100, 100
  );

  leftButton->setMargin(10);

  UIComponent *insideLeftButton = new UIComponent(
    "insideRightButton",
    "Inside Right Button",
    0, 0,
    50, 50
  );

  insideLeftButton->setMargin(20);

  UIComponent *insideLeftButtonChild = new UIComponent(
    "insideLeftButtonChild",
    "Inside Right Button child",
    0, 0,
    20, 20
  );

  insideLeftButtonChild->setMargin(20);

  insideLeftButton->appendChild(insideLeftButtonChild);
  leftButton->appendChild(insideLeftButton);

  rightMenu->appendChild({
   leftButton,
    new UIComponent(
      "rightButton",
      "Right Button",
      100, 0,
      100, 100
    )
  });

  UIManager::getInstance()->addComponent(rightMenu);

  while (Core::getInstance()->isRunning()) {
    Core::getInstance()->events();
    Core::getInstance()->render();
  }

  return 0;

}