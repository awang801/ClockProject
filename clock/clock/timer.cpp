#include "stdafx.h"
#include "timer.h"


timer::timer()
{
	m_hours = 0;
	m_minutes = 0;
	m_seconds = 0;
}

timer::~timer()
{
}

void timer::timing()
{

}

int timer::getHours()
{
	return(m_hours);
}

int timer::getMinutes()
{
	return(m_minutes);
}

int timer::getSeconds()
{
	return(m_seconds);
}

void timer::setHours(int hours)
{
	m_hours = hours;
}

void timer::setMinutes(int minutes)
{
	m_minutes = minutes;
}

void timer::setSeconds(int seconds)
{
	m_seconds = seconds;
}
