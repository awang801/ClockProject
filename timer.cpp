#include "timer.h"

timer::timer()
{
	m_time_seconds = 0;
	m_24hour_flag = false;
}

timer::timer(int seconds)
{
	m_time_seconds = seconds;
	m_24hour_flag = false;
}

timer::timer(int hours, int minutes, int seconds)
{
	m_time_seconds = hours * 3600 + minutes * 60 + seconds;
	m_time_seconds = ((m_time_seconds % 86400) + 86400) % 86400;
	m_24hour_flag = false;
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
	int rawHours = ((m_time_seconds - 60 * getMinutes() - getSeconds()) / 3600);
	if(m_24hour_flag)
	{
		int addTime(int seconds_change);
	}

	return (rawHours == 0) ? 12 : rawHours % 12;
}

int timer::getMinutes()
{
	return ((m_time_seconds % 3600 - getSeconds()) / 60);
}

int timer::getSeconds()
{
	return (m_time_seconds % 60);
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

int timer::timerSetting(int origTimerTime)
{
    int timerTime = 0;
    timerTime = origTimerTime;
    timerTime--;
    
    return timerTime;
}

int timer::stopWatchSetting(int origStopwatchTime)
{
    int stopWatchTime = 0;
    stopWatchTime = origStopwatchTime;
    stopWatchTime++;
    
    return stopWatchTime;    
}
