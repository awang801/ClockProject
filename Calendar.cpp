#include "Calendar.h"

#include <iostream>

int m_monthsLength[] = {31,29,31,30,31,30,31,31,30,31,30,31};
std::string m_weekday[] = {"Fri","Sat","Sun","Mon","Tues","Wed","Thurs"};
std::string month_names[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

Calendar::Calendar()
{
	m_dayofweek = m_weekday[0];
}

Calendar::~Calendar()
{
}

//sets m_dayofweek one of 7 days in m_weekday array
void Calendar::setWeekday()
{
	int m_value = 0;

	for(int i=0; i<(m_monthValue-1); i++)
	{
		m_value += m_monthsLength[i];
	}
	m_value += m_day;
	m_value = (m_value%7);

	if((m_value) == 0)
	{
		m_dayofweek = m_weekday[6];
	}

	m_dayofweek = m_weekday[m_value-1];
}

void Calendar::changeDay(int days)
{
	m_dayofweek = m_weekday[m_value];
}

void Calendar::setMonth(int month)
{
	month += 1;
	month = (month % 12);
	m_monthValue = month;
	m_month = month_names[month];
}

void Calendar::addMonth(int change)
{
	m_monthValue += change;
	m_monthValue %= 12;
	m_month = month_names[m_monthValue];
	setWeekday();
}

void Calendar::subtractMonth(int change)
{
	m_monthValue -= change;
	m_monthValue %= 12;
	m_month = month_names[m_monthValue];
	setWeekday();
}

std::string Calendar::getMonth()
{
	return m_month;
}

int Calendar::getDate()
{
	return m_day;
}

std::string Calendar::getDayOfWeek()
{
	return m_dayofweek;
}
