#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <chrono>
#include <cassert>
#include <fstream>
#include <functional>
#include "timer.h"
#include <limits>
//For int to string conversion
#include <sstream>
//Project 2 includes
#include <thread>

/*
*	@pre a pointer to a timer is passed in
*	@post the time of the clock is Set
*	@return none
*/
void Start(timer* clk);

/*
*	@pre time.txt is changed, a timer that is set is passed in
*	@post
*	@return true if the timer is changed and the user has finished changes
*/
bool Reset(timer* clk);

/*
*	@pre a clock has been passed in
*	@post  none
*	@return a the time is formatted to a string
*/
std::string gettime(timer* clk);

/*
*	Converts an integer to a std::string
*	This is needed because std::to_string (as used in the original implementation) is not supported in every compiler
*	@param num the integer to be converted
*	@returns a std::string representation of the given integer
*/
std::string intToStr(int num);

/*
* This does some set up and then loops on a specified interval in an asynchronous thread
* It updates the time of the specified timer by calling timing() once per loop
* @pre t needs to be initialized with a time
*	@param t the timer object to be updated
*/
void run(timer* clk, int timer_ms);

std::string intToStr(int num){
	std::ostringstream stringConverter;

	stringConverter << num;

	return (stringConverter.str());
}

void run(timer* clk, int timer_ms)
{
	bool time_lord=true;
	// user needs to have defined set the time before this point

	//Used for keepign track of timing using chrono
	long int timeTracker;
	do
	{

		//this gets the current timestamp in milliseconds
    timeTracker = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

		//This prints the time
		std::cout << gettime(clk)<<"\r";

		//This increments the second counter
		clk->timing();

		//TODO: Manage calendar

		//sleep for the remainder of timer_ms (less the time it took to execute digitalRun)
		std::this_thread::sleep_for(std::chrono::milliseconds(timeTracker + (long) timer_ms - (long) std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()));

	}while(time_lord);
}

int main()
{
	timer* clk=new timer();

	Start(clk);

	std::thread timerCaller (run, clk, 300);  // spawn new thread

  std::cout << "It's working!!1!\n";
	timerCaller.join();

	delete clk;
  return(0);
}

/*
user setting time of clock
*/

void Start(timer* clk)
{

}
std::string gettime(timer * clk)
{
	//TODO: update this
	std::string t;


	int temp=clk->getHours();
	if (temp>=10) {
		t=intToStr(temp);
	}
	else {
		t="0"+intToStr(temp);
	}
	temp=clk->getMinutes();
	if (temp>=10) {
		t=t+":"+intToStr(temp);
	}
	else {
		t=t+":0"+intToStr(temp);
	}
	temp=clk->getSeconds();
	if (temp>=10) {
		t=t+":"+intToStr(temp);
	}else {
		t=t+":0"+intToStr(temp);
	}
	if(!(clk->get24hourmode())){
		t=t+clk->getam_pm();
	}
 return t;
}

bool Reset(timer* clk){
	int i=1;
	while(i==1){
		std::cout << "Clock menu \n" << "============ \n"<<"what do want to change(insert number) \n";
		std::cout << "1) change clock mode " << std::endl;
		std::cout << "2) change time" << std::endl;
		std::cout << "3) end the clock" << std::endl;
		std::string am_pm;

		int input;
		std::cin >> input;


		if (input==1) {
			clk->set24hourmode(!(clk->get24hourmode()));
		}
		else if (input==2) {

			if(!(clk->get24hourmode())){
		      std::cout << "Am or PM?" << std::endl;

		 			std::cin >> am_pm;
		 			do {
		 				if (am_pm=="am"||am_pm=="AM"||am_pm=="aM"||am_pm=="Am"||am_pm=="a.m.")
		 				{

		 					break;
		 				} else if (am_pm=="pm"||am_pm=="PM"||am_pm=="pM"||am_pm=="Pm"||am_pm=="p.m.") {
		 					am_pm=="pm"; //need am_pm to equal this later

		 					break;
		 				} else
		 				{
		 					std::cout << "Invalid input" << std::endl;

		 					std::cout << "Am or PM?" << std::endl;
		 					std::cin >> am_pm;
		 				}
		 			} while(true);
				}
				std::cout << "HR: \n";
			  int hr;
			  std::cin >> hr;
				while(std::cin.fail()) {  //learned how to
			    std::cin.clear();
			    std::cin.ignore(std::numeric_limits<int>::max(),'\n');
			    std::cout << "Bad entry.  Enter a NUMBER: ";
			    std::cin >> hr;
			}

				hr=hr%24;


			  std::cout << "MIN: \n";
			  int min;
			  std::cin >> min;
				while(std::cin.fail()) {
			    std::cin.clear();
			    std::cin.ignore(std::numeric_limits<int>::max(),'\n');
			    std::cout << "Bad entry.  Enter a NUMBER: ";
			    std::cin >> min;
			}
				min=min%60;

			  std::cout << "Sec:\n ";
			  int sec;
			  std::cin >> sec;
				while(std::cin.fail()) {
			    std::cin.clear();
			    std::cin.ignore(std::numeric_limits<int>::max(),'\n');
			    std::cout << "Bad entry.  Enter a NUMBER: ";
			    std::cin >> sec;
			}
				sec=sec%60;

				if(clk->get24hourmode()==false)
				{
					if (am_pm=="pm") {
						hr=hr%12;
						hr=hr+12;
					}
					else if(hr==12) {
						hr=0;
					}


				}
				  clk->setHours(hr);
				  clk->setMinutes(min);
				  clk->setSeconds(sec);


		}
		else if(input==3) {
			return(false);
		}else{
			std::cout << "invalid input" << std::endl;
		}
			std::cout << "would you like change anything else? (y/n)" << std::endl;
				char x;
				std::cin >> x;
			if (x=='n'||x=='N') {

				//write the file here
				return(true);
			}
	}
	return (true);
}
