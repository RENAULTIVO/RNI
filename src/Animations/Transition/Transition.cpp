#include "Transition.hpp"
#include "../../Core/Core.hpp"

Transition::Transition(
  UIComponent *targetComponent,
  float initialValue,
  float targetValue,
  Animation::milliseconds duration
) {

  std::cout<<"Transition created"<<std::endl;
  //this->instance = this;
  this->targetComponent = targetComponent;

  this->props.duration = duration;
  this->props.currentValue = initialValue;
  this->props.targetValue = targetValue;

  this->onChangeListener = nullptr;
  this->onCompleteListener = nullptr;

}

void Transition::loop(
  UIComponent *targetComponent,
  TransitionProps props,
  Animation::eventListener eventListener) {

  std::cout<<"Loop started"<<std::endl;

  props.currentValue = props.initialValue;

  float valueIncreasePerIteration = -(props.initialValue - props.targetValue) / props.duration;
  
  for (props.currentTime = 0; props.currentTime < props.duration; props.currentTime++) {
    props.currentValue += valueIncreasePerIteration;
    eventListener(targetComponent, props.currentValue);
    Core::getInstance()->render();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

/*
  instance.currentValue = instance.initialValue;

  float valueIncreasePerIteration = -(instance.initialValue - instance.targetValue) / instance.duration;

  for (instance.currentTime = 0; instance.currentTime < instance.duration; instance.currentTime++) {
    instance.currentValue += valueIncreasePerIteration;
    instance.onChangeListener(instance.targetComponent, instance.currentValue);
    Engine::getInstance()->render();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  if (instance.onCompleteListener != nullptr) {
    instance.onCompleteListener(instance.targetComponent, instance.currentValue);
  }*/

}

void animationLoop() {
  std::cout<<"Loop started"<<std::endl;
}

void Transition::start() {
  std::cout<<"Should have started loop"<<std::endl;
  loopThread = new std::thread(Transition::loop, std::ref(this->targetComponent), std::ref(this->props), std::ref(this->onChangeListener));
  loopThread->join();
  //t.join();
}

void Transition::cancel() {

}

void Transition::setDuration(Animation::milliseconds duration) {
  this->props.duration = duration;
}

void Transition::setTargetValue(float targetValue) {
  this->props.targetValue = targetValue;
}

void Transition::setInitialValue(float initialValue) {
  this->props.initialValue = initialValue;
}

void Transition::setOnChangeListener(Animation::eventListener onChangeListener) {
  this->onChangeListener = onChangeListener;
}

void Transition::setOnCompleteListener(Animation::eventListener onCompleteListener) {
  this->onCompleteListener = onCompleteListener;
}


