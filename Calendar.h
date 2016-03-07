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

  /*
    @params int month, int day
    @post day of week calculated
    @return nothing
  */
  void setWeekday();

  /*
    @param number of days incremented
    @post day of week incremented
    @return none
  */
  void changeDay(int day);

  /*
    @return day of week
  */
  std::string getDayOfWeek();

  /*
   * @post sets calendar day number regradless of month
   */
  void setDay(int day);

  /*
   * @pre needs integer. anything greater than 12 is mod by 12, then used.
   * @post sets month based on number 1-12
   */
  void setMonth(int month);

  /*
   * @pre requires integer
   * @post adds x months to current month value
   */
  void addMonth(int change);

  /*
   * @post subtracts x months from current month value
   */
  void subtractMonth(int change);

  // returns m_month
  std::string getMonth();

  //returns m_day
  int getDate();

  //Member variables

  int m_value; //used in change weekdat function
  int m_monthValue = 0; //0-11 keeps track of number of month
  std::string m_month = "January"; //name of current month
  int m_day = 1; //keeps track of number of day in current month
  int m_monthsLength[]; //12 cell array with length of ea month in days
  std::string m_weekday[]; //7 cell array with day of week names
  std::string m_dayofweek = "Friday"; //keeps track of current day of the week
  std::string month_names[]; //12 cell array with month names
};
#endif
