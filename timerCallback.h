#ifndef TIMERCALLBACK_H
#define TIMERCALLBACK_H

#include <iostream>

#include <time.h>
#include <thread>
#include <chrono>

class timerCallback
{

  public:

    timerCallback(/*timer* target_timer, UNCOMMENT */ int timer_ms);

    ~timerCallback();

  private:

    //timer* m_timer; UNCOMMENT

    int m_timer_ms;

    void callTimer();

};

#endif
