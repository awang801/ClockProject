#include "timer.h"
#include <time.h>

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
	m_24hour_flag = false;

}

timer::~timer()
{
}

void timer::timing()
{
	//TODO: Redo this
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
	while (m_seconds >= 60)
	{
		m_seconds = m_seconds - 60;
		minutes_to_add++;
	}int daysAdded = (m_time_seconds - (m_time_seconds % 86400)) / 86400;
		m_time_seconds = m_time_seconds % 86400; // of how many (if any) hours to add
	m_minutes = m_minutes + minutes_to_add;
	int hours_to_add = 0;
	while (m_minutes >= 60)
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

std::string timer::getam_pm()
{
	if(m_hours<12){
		return("am");
	}else{return("pm");}
}

int timer::getHours()
{
	if(m_24hour_flag)
	{
	}
	return (((m_time_seconds - 60 * getMinutes() - getSeconds()) / 3600) % 12 + 1);
}

int timer::getMinutes()
{
	return ((m_time_seconds % 3600 - getSeconds()) / 60);
}

int timer::getSeconds()
{
	return (m_time_seconds % 60);
}

bool timer::get24hourmode()
{
	return (m_24hour_flag);
}

void addTime(int seconds_change)
{
	m_time_seconds += seconds_change;
	if(m_time_seconds>=86400)
	{
		int daysAdded = (m_time_seconds - (m_time_seconds % 86400)) / 86400;
		m_time_seconds = m_time_seconds % 86400;
		//add daysAdded days to the calendar
	}
	else if(m_time_seconds<0)
	{
		int daysSubtracted = 1 + ((abs(m_time_seconds) - (abs(m_time_seconds) % 86400)) / 86400);
		m_time_seconds = ((m_time_seconds % 86400) + 86400) % 86400;

		//subtract daysSubtracted from the calendar
	}
}

void timer::set24hourmode(bool mode)
{
	m_24hour_flag = mode;
}
