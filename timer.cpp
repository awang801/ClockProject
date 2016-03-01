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

void timer::timing()
{
	return addTime(1);
}

std::string timer::getam_pm()
{
	if(m_hours<12){
		return("am");
	}else{return("pm");}
}

int timer::getHours()
{
	//fix
	if(m_24hour_flag)
	{
	}
	return (((m_time_seconds - 60 * getMinutes() - getSeconds()) / 3600) % 12);
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

int addTime(int seconds_change)
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
		m_time_seconds = ((m_time_seconds % 86400) + 86400) % 86400;
		return dayChange * (-1);
	}
	return 0;
}

void timer::set24hourmode(bool mode)
{
	m_24hour_flag = mode;
}
