#ifndef TIMER_H
#define TIMER_H
#include <string>
#include <cmath>

enum clkMode { timerMode, stopwatch, regularClock };
enum timerCommands{ enter, stop, start, reset, stopTimer, keepGoing };

class timer
{
	private:
                //Member variables
                //Represents the time in seconds out of the day (always between 0-86399)
                int m_time_seconds;

                long int timerTime;

                //If mode is 12 hour, m_24hour_flag = false. If mode is 24 hour, m_24hour_flag = true
                bool m_24hour_flag;
                clkMode mode;
                bool timerPause;

	public:
		/** @pre  None
		*   @post timer created with start time of midnight and m_24hour_flag set to false
		*/
		timer();

		/**	@pre None
		*		@post timer created with start time at given number of seconds and m_24hour_flag set to false
		*/
		timer(int seconds);

		/** @pre  None
		*   @post timer created with start time at given number of hours, minutes, and seconds and m_24hour_flag set to false
		*/
		timer(int hours, int minutes, int seconds);

		~timer();

		//--------------------------------------
		//Get methods for hours, minutes, seconds
		//--------------------------------------

		/** @pre None
		*   @return number of hours
		*/
		int getHours();

		/** @pre None
		*   @return number of minutes
		*/
		int getMinutes();

		/** @pre    None
		*   @return number of seconds
		*/
		int getSeconds();

		/**
		*		@return m_time_seconds the time in seconds
		*/
		int getTimeInSeconds();

		/**
		*		@returns m_time_seconds the time in se	private:
		//Member variables
		//Represents the time in seconds out of the day (always between 0-86399)
		int m_time_seconds;

		//If mode is 12 hour, m_24hour_flag = false. If mode is 24 hour, m_24hour_flag = true
		bool m_24hour_flag;

		/**
		*   @returns m_24hour_flag
		*/
		bool get24hourmode();


		/** @pre  None
		*   @post Returns string of either am or pm
		*/
		std::string getam_pm();

		//--------------------------------------
		//Set methods
		//--------------------------------------

		/** @pre  seconds_change is an integer
		*   @post Adjusts time by given number of seconds, accounting for rollover.  Updates the day of the week if necessary
		*/
		int addTime(int seconds_change);

		/**
		*		@returns myTime safely rounded off (so that it is definitely in the valid time range)
		*/
		int safeRound(int myTime);

		/**
		*		@post m_time_seconds is set to newTime
		*/
		void setTimeInSeconds(int newTIme);

		/** @pre  None
		*   @post Mode is set to either 24 hour mode or 24 hour mode
		*/
		void set24hourmode(bool mode);

		/** @pre  None
		*   @post Variables for time are updated
		* 	@return dayChange the change in day from adding the second (should be either 0 or 1)
		*/

                int timing();

                void stopWatchRun(timerCommands command);

                void timerRun(timerCommands command);

                void setTimer(int setTime);
                clkMode getTimerMode();

                bool isTimerPaused();
                
                
};
#endif
