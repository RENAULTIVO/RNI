#ifndef TRANSITION_HPP
#define TRANSITION_HPP
#include "../Animation.hpp"
#include "../../UI/UIComponent/UIComponent.hpp"
#include <thread>

typedef struct TransitionProps {
  float initialValue = 0;
  float targetValue = 0;
  float currentValue = 0;
  Animation::milliseconds currentTime = 0;
  Animation::milliseconds duration = 0;
} TransitionProps;

class Transition {

  private:
    Animation::milliseconds currentTime;
    Animation::milliseconds duration;
    TransitionProps props;
    std::thread *loopThread;
    UIComponent *targetComponent;
    Animation::eventListener onChangeListener;
    Animation::eventListener onCompleteListener;

  public:
    
    Transition(
      UIComponent *targetComponent,
      float initialValue = 0,
      float targetValue = 0,
      Animation::milliseconds duration = 0
    );

    void start();
    void cancel();
    static void loop(UIComponent *targetComponent, TransitionProps props, Animation::eventListener eventListener);
    void setDuration(Animation::milliseconds duration);
    void setTargetValue(float initialValue);
    void setInitialValue(float initialValue);
    void setOnChangeListener(Animation::eventListener onChangeListener);
    void setOnCompleteListener(Animation::eventListener onCompleteListener);


};

#endif