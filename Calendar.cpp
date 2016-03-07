#include "Calendar.h"

#include <iostream>
#include <string>



Calendar::Calendar()
{
	m_dayInYear = 0;
}

Calendar::~Calendar()
{
}

int Calendar::safeRound(int val, int max)
{
	return ((val % max) + max) % max;
}

std::string Calendar::getDayOfWeek()
{
  return m_weekday[m_dayInYear%7];
}

void Calendar::changeDay(int change)
{
  m_dayInYear = safeRound(m_dayInYear+change, 366);
}

int Calendar::getMonth()
{
  int temp = m_dayInYear;
  int month;
  for(int month=0; month<12 && temp>0; month++)
  {
    temp -= m_monthsLength[month];

  }
  return month;
}

void Calendar::changeMonth(int change)
{
  if(change > 0)
  {
    for(int i = 0; i < change; i++)
    {
      m_dayInYear += m_monthsLength[safeRound(i, 12)];
    }
  }
  else
  {
    change = change * -1;
    for(int i = 0; i < change; i++)
    {
      m_dayInYear -= m_monthsLength[safeRound(i, 12)];
    }
  }
  m_dayInYear = safeRound(m_dayInYear, 366);
}
