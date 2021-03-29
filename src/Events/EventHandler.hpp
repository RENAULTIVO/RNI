#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP
#include <iostream>

class EventHandler {

  private:
    EventHandler() {}
    static EventHandler *instance;

  public:
    void listen();
    static EventHandler *getInstance();

};

#endif