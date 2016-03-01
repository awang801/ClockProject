#include <string>
#include <cmath>
class timer
{
	public:
		/** @pre  None
		*   @post timer created with start time at midnight
		*/
		timer();

		/**	@pre None
		*		@post timer created with start time at given number of seconds
		*/
		timer(int seconds);

		/** @pre  None
		*   @post timer created with start time at given number of hours, minutes, and seconds
		*/
		timer(int hours, int minutes, int seconds);

		~timer();

		/** @pre  None
		*   @post Variables for time are updated
		* 	@return dayChange the change in day from adding the second (should be either 0 or 1)
		*/
		int timing();

		//--------------------------------------
		//Get methods for hours, minutes, seconds
		//--------------------------------------

		/** @pre None
		*   @return Returns number of hours
		*/
		int getHours();

		/** @pre None
		*   @return Returns number of minutes
		*/
		int getMinutes();

		/** @pre    None
		*   @return Returns number of seconds
		*/
		int getSeconds();void
		*   @post Returns mode of clock
		*/
		bool get24hourmode();


		/** @pre  None
		*   @post Returns string of either am or pm
		*/
		std::string getam_pm();

		//--------------------------------------
		//Set methods for hours, minutes, seconds
		//--------------------------------------

		/** @pre  seconds_change is an integer
		*   @post Adjusts time by given number of seconds, accounting for rollover.  Updates the day of the week if necessary
		*/
		void addTime(int seconds_change);

		/** @pre  None
		*   @post Mode is set to either 24 hour mode or 24 hour mode
		*/
		void set24hourmode(bool mode);




		//Member variables


	private:
		int m_time_seconds;
		//might need a flag to help with this

		//If mode is 12 hour, m_24hour_flag = false. If mode is 24 hour, m_24hour_flag = true
		bool m_24hour_flag;
};
