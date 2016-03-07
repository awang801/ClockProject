/**
*  @author 	Audrey Evans <audreyevans@ku.edu>
*               hari ramanan <hramanan@ku.edu>
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
  *   Performs the modulus operation as val mod max, but guarantees that the value is positive
  *   @pre max is positive
  *   @post returned value is between zero and max
  *   @returns the 'safe' modulus of val mod max
  */
  int safeRound(int val, int max);


  int getMonth();

  /*
  *   @return day of the week as a string
  */
  std::string getDayOfWeek();

  /*
  *   @post the day is changed by the given number
  */
  void changeDay(int change);

  /*
  *   @post the day is changed by the given number of months
  */
  void changeMonth(int change);

  int m_monthsLength[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
  std::string m_weekday[7] = {"Fri","Sat","Sun","Mon","Tues","Wed","Thurs"};
  std::string month_names[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
  int m_dayInYear;
};

#endif
