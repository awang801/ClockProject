/**
*  @author 	Audrey Evans <audreyevans@ku.edu>
*  @version 2.0 &nbsp;
*  @since 2016-03-1
*/


#ifndef CALENDAR_H
#define CALENDAR_H
#include <iostream>
#include <string>

class Calendar
{

public:
  /* @pre none
     @post Calendar defaulted to Jan 1 (Friday)
  */
  Calendar();
  /*@pre destructor
    @post deletes pointers
  */
  ~Calendar();
  /*
    @params int month, int day
    @post day of week calculated
    @return day of week
  */
  std::string setDay(int month,int day);

  /*
    @param number of days incremented
    @post day of week incremented
    @return none
  */
  void ChangeDay(int days);
  /*
    @return day of week
  */
  std::string getdayofweek();

  //Member variables

  int m_value;
  int m_month;
  int m_day;
  int m_months[];
  std::string m_weekday[];
  std::string m_dayofweek;


};
#endif
