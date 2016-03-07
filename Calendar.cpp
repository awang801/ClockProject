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
	int dayInYear = 0;
  for(int i = 0; i < m_monthValue; i++)
  {
    dayInYear += m_monthsLength[i];
  }
  dayInYear += m_day;
  m_dayofweek = m_weekday[dayInYear % 7];
}

int Calendar::safeRound(int val, int max)
{
	return ((val % max) + max) % max;
}

void Calendar::changeDay(int day)
{
  m_day += day;
  m_monthValue = safeRound(m_monthValue, 12);
  if(m_day > m_monthsLength[m_monthValue])
  {
    addMonth(1);
    m_day = safeRound(m_day, m_monthsLength[m_monthValue]);
  }
  else if(m_day < m_monthsLength[m_monthValue])
  {
    subtractMonth(1);
    m_day = safeRound(m_day, m_monthsLength[m_monthValue]);
  }
  setWeekday();
}

void Calendar::setMonth(int month)
{
	month = safeRound(month, 12);
	m_monthValue = month;
	m_month = month_names[month];
  setWeekday();
}

void Calendar::addMonth(int change)
{
  m_monthValue = safeRound(m_monthValue + change, 12);
	m_month = month_names[m_monthValue];
	setWeekday();
}

void Calendar::subtractMonth(int change)
{
	m_monthValue = safeRound(m_monthValue - change, 12);
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
