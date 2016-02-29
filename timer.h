#include <string>
#include <cmath>
class timer
{
	public:
		/** @pre  None
		*   @post Timer defaulted to current Central time
		*/
		timer();

		/** @pre  hours, minutes, seconds are assumed to be valid numbers for hours, minutes, seconds
		*   @post m_hours, m_minutes, m_seconds are set to user defined inputs
		*/
		timer(int hours, int minutes, int seconds);

		~timer();

		/** @pre  None
		*   @post Variables for time are updated
		*/
		void timing();

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
		int getSeconds();

		/** @pre  None
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
