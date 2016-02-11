#include "timer.h"
#include <time.h>

timer::timer()
{
	m_hours = 0;
	m_minutes = 0;
	m_seconds = 0;
	m_24hour_flag = false;
}

timer::timer(int hours, int minutes, int seconds)
{
	m_hours = hours;
	m_minutes = minutes;
	m_seconds = seconds;
	m_seconds_1970 = time(0);
	m_24hour_flag = false;
	m_am_pm="am";
}

timer::~timer()
{
}

void timer::timing()
{
	//Temp storage for prior timing
	int temp = m_seconds_1970;

	//Updating timing
	m_seconds_1970 = time(0);

	//Computing seconds since last timing
	int difference = m_seconds_1970 - temp;

	//Updating m_seconds, and keeping track of how many minutes need to be updated
	m_seconds = m_seconds + difference;

	int minutes_to_add = 0;
	//If m_seconds is over 60, make it so it is less than 60
	while (m_seconds > 60)
	{
		m_seconds = m_seconds - 60;
		minutes_to_add++;
	}

	//Updating m_minutes, and keeping track of how many (if any) hours to add
	m_minutes = m_minutes + minutes_to_add;
	int hours_to_add = 0;
	while (m_minutes > 60)
	{
		m_minutes = m_minutes - 60;
		hours_to_add++;
	}

	//Updating m_hours, and making sure if the hour count goes over 24 it goes back to 0, and increments from there
	m_hours = m_hours + hours_to_add;
	while (m_hours >= 24)
	{
		m_hours = m_hours - 24;
	}

}

int timer::getHours()
{
	if (m_24hour_flag = false)
	{
		if (m_hours > 12)
		{
			return(m_hours - 12);
		}
		else
		{
			return(m_hours);
		}
	}
	else
	{
		return(m_hours);
	}

}

std::string timer::getam_pm()
{
	if(m_hours<12){
		return("am");
	}else{return("pm")}
}

int timer::getMinutes()
{
	return(m_minutes);
}
int

int timer::getSeconds()
{
	return(m_seconds);
}

bool get24hourmode()
{
	return m_24hour_flag;
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

void timer::set24hourmode(bool mode)
{
	m_24mode_flag = mode;
}
 void timer::setam_pm(std:string s) {
	m_am_pm=s;
	return;
 }
