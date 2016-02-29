#include "timerCallback.h"

timerCallback::timerCallback(/*timer* target_timer, UNCOMMENT */ int timer_ms)
{
  //m_timer = target_timer; UNCOMMENT
  m_timer_ms = timer_ms;
  std::thread first (timerCallback::callTimer);
}

timerCallback::~timerCallback()
{
  //delete m_timer; UNCOMMENT
}

//http://stackoverflow.com/questions/1120478/capturing-a-time-in-milliseconds
void timerCallback::callTimer()
{
  long int timeTracker;
  while(true)
  {
    //this gets the current timestamp in milliseconds
    timeTracker = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

    //testing
    std::cout<<"Tic \n";

    //m_timer->digitalRun(); UNCOMMENT

    //sleep for the remainder of m_timer_ms (less the time it took to execute digitalRun)
    std::this_thread::sleep_for(std::chrono::milliseconds(timeTracker + (long) m_timer_ms - (long) std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()));
  }
}
