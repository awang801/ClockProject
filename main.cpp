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

/*
*	@pre a clock has been passed in
*	@post  none
*	@return a the time is formatted to a string
*/
std::string gettime(timer* clk);


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

	//Wait for the run thread to end (clock to end) then join so that resources can be deleted and program can terminate
	timerCaller.join();

	delete clk;
  return(0);
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
