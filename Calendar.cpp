#include "Calendar.h"

#include <iostream>

int m_months[] = {31,29,31,30,31,30,31,31,30,31,30,31};
std::string m_weekday[] = {"Fri","Sat","Sun","Mon","Tues","Wed","Thurs"};

Calendar::Calendar()
{
  //int m_months[] = {31,29,31,30,31,30,31,31,30,31,30,31};
	//std::string m_weekday[] = {"Fri","Sat","Sun","Mon","Tues","Wed","Thurs"};
  m_dayofweek = m_weekday[0];

}
Calendar::~Calendar()
{
  delete [] m_months;
  delete [] m_weekday;

}
std::string Calendar::setDay(int month, int day)
{
	int m_value = 0;


	for(int i=0;i<month-1;i++)
	{
		m_value += m_months[i];
	}
	m_value += day;
	m_value = (m_value%7);



	if((m_value) == 0)
	{
    m_dayofweek = m_weekday[6];
		return(m_weekday[6]);
  }

  m_dayofweek = m_weekday[m_value-1];
	return (m_weekday[m_value-1]);
}

void Calendar::ChangeDay(int days)
{
  m_dayofweek = m_weekday[m_value];
}
std::string Calendar::getdayofweek()
{
  return m_dayofweek;
}
