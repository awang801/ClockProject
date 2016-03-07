#include "timer.h"

timer::timer()
{
        m_time_seconds = 0;
        m_24hour_flag = false;
        timerTime = 0;
        mode = regularClock;
        timerPause = true;
}

timer::timer(int seconds)
{
        m_time_seconds = seconds;
        m_24hour_flag = false;
        timerTime = 0;
        mode = regularClock;
        timerPause = true;
}

timer::timer(int hours, int minutes, int seconds)
{
        m_time_seconds = hours * 3600 + minutes * 60 + seconds;
        m_time_seconds = ((m_time_seconds % 86400) + 86400) % 86400;
        timerTime = hours * 3600 + minutes * 60 + seconds;
        m_24hour_flag = false;
        mode = regularClock;
        timerPause = true;
}

timer::~timer()
{
}

std::string timer::getam_pm()
{
        if(m_time_seconds<43200)
        {
                return("am");
        }
        else
        {
                return("pm");
        }
}

int timer::getHours()
{
        int rawHours;
        switch(mode)
        {
        case regularClock:
            rawHours = ((m_time_seconds - 60 * getMinutes() - getSeconds()) / 3600);
            if(m_24hour_flag)
            {
                    int addTime(int seconds_change);
            }

            return (rawHours == 0) ? 12 : rawHours % 12;
            break;
        case timerMode:
            rawHours = ((timerTime - 60 * getMinutes() - getSeconds()) / 3600);

            return (rawHours == 0) ? 12 : rawHours % 12;
            break;
        case stopwatch:
            rawHours = ((timerTime - 60 * getMinutes() - getSeconds()) / 3600);

            return (rawHours == 0) ? 12 : rawHours % 12;
            break;
        default:
            return 0;
            break;

        }
}

int timer::getMinutes()
{
        switch(mode)
        {
        case regularClock:
            return ((m_time_seconds % 3600 - getSeconds()) / 60);
            break;
        case timerMode:
            return ((timerTime %3600 - getSeconds())/60);
            break;
        case stopwatch:
            return ((timerTime %3600 - getSeconds())/60);
            break;
        default:
            return 0;
            break;
        }
}

int timer::getSeconds()
{
        switch(mode)
        {\
            case regularClock:
                return (m_time_seconds % 60);
                break;
            case timerMode:
                return(timerTime % 60);
                break;
            case stopwatch:
                return(timerTime % 60);
                break;
            default: 
                return 0;
                break;
       }
}

int timer::getTimeInSeconds()
{
        return m_time_seconds;
}

bool timer::get24hourmode()
{
        return (m_24hour_flag);
}

int timer::addTime(int seconds_change)
{

        if (mode == regularClock)
        {
        m_time_seconds += seconds_change;
        if(m_time_seconds>=86400)
        {
                int dayChange = (m_time_seconds - (m_time_seconds % 86400)) / 86400;
                m_time_seconds = m_time_seconds % 86400;
                return dayChange;
        }
        else if(m_time_seconds<0)
        {
                int dayChange = 1 + ((abs(m_time_seconds) - (abs(m_time_seconds) % 86400)) / 86400);
                m_time_seconds = safeRound(m_time_seconds);
                return dayChange * (-1);
        }
        return 0;
        }
        else
        {
            timerTime += seconds_change;
            safeRound(timerTime);
            return 0;
        }
}

int timer::safeRound(int myTime)
{
        return ((myTime % 86400) + 86400) % 86400;
}

void timer::setTimeInSeconds(int newTime)
{
        m_time_seconds = newTime;
}

void timer::set24hourmode(bool mode)
{
        m_24hour_flag = mode;
}

int timer::timing()
{
        return addTime(1);
}

void timer::stopWatchRun(timerCommands command)
{
    switch(command)
    {
        case keepGoing:
            timerTime ++;
        case enter:
            mode = stopwatch;
            break;
        case start:
            timerPause = true;
            break;
        case stop:
            timerPause = false;
            break;
        case reset:
            timerTime = 0;
            break;
        case stopTimer:
            mode = regularClock;
            timerTime = 0;
            break;

    }
}

clkMode timer::getTimerMode()
{
    return mode;
}

void timer::setTimer(int setTime)
{
    timerTime = setTime;
}

bool timer::isTimerPaused()
{
    return timerPause;
}

void timer::timerRun(timerCommands command)
{
    switch(command)
    {
        case keepGoing:
            if (timerTime == 0)
            {
                timerPause = false;
            }

            else
            {
                timerTime --;
            }
        case enter:
            mode = timerMode;
            break;
        case start:
            timerPause = true;
            break;
        case stop:
            timerPause = false;
            break;
        case reset:
            timerTime = 0;
            break;
        case stopTimer:
            mode = regularClock;
            timerTime = 0;
            break;
    }

}

