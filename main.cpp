#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <locale>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <cassert>
#include <functional>
#include "timer.h"
#include "Calendar.h"
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
std::string intToString(int var);

/*
* This does some set up and then loops on a specified interval in an asynchronous thread
* It updates the time of the specified timer by calling timing() once per loop
* @pre t needs to be initialized with a time
*	@param t the timer object to be updated
*/
void timerCaller(timer* clk, int timer_ms, Calendar* coolCalendar);

/*
*	@pre a clock has been passed in
*	@post  none
*	@return a the time is formatted to a string
*/
std::string gettime(timer* clk);

//true if display is zoomed
bool zoom = false;

//used to control the loops in the thread, exits when this is set to false
bool loopControl = true;

//true if paused
bool paused  = false;

//true if display is on
bool display = true;


std::string asciiDigits[10][5] = {{"X X X ", "X   X ", "X   X ", "X   X ", "X X X "}, //0
																	{"X X   ", "  X   ", "  X   ", "  X   ", "X X X "}, //1
																	{"X X X ", "    X ", "X X X ", "X     ", "X X X "}, //2
																	{"X X X ", "    X ", "X X X ", "    X ", "X X X "}, //3
																	{"X   X ", "X   X ", "X X X ", "    X ", "    X "}, //4
																	{"X X X ", "X     ", "X X X ", "    X ", "X X X "}, //5
																	{"X X X ", "X     ", "X X X ", "X   X ", "X X X "}, //6
																	{"X X X ", "    X ", "    X ", "    X ", "    X "}, //7
																	{"X X X ", "X   X ", "X X X ", "X   X ", "X X X "}, //8
																	{"X X X ", "X   X ", "X X X ", "    X ", "X X X "}  //9
																	};

int stringToInt( std::string str )
{
	std::istringstream stringToInt(str);
	int hourSet;

	if ( !(stringToInt >> hourSet) )
	{
		//uh oh
		hourSet = -1;
	}
	return hourSet;
}

std::string intToString(int var)
{
	std::ostringstream intToString;

	intToString << var;

	return intToString.str();
}

std::vector<int> divide(std::string command)
{
	char delim = ' ';
	std::string next;
	std::vector<std::string> raw;

	for ( std::string::const_iterator iter = command.begin(); iter != command.end(); iter++ )
	{
		if ( *iter == delim )
		{
			if ( !next.empty() )
			{
				raw.push_back(next);
				next.clear();
			}
		}
		else
		{
			// Accumulate the next character into the sequence
			next += *iter;
		}
	}
	if ( !next.empty() )
	{
		raw.push_back( next );
	}

	std::vector<int> commands;
	if( raw.size() == 0 )
	{
		return commands;
	}

	commands.push_back(stringToInt(raw[0]));
	if(raw.size() > 1)
	{
		commands.push_back(stringToInt(raw[1]));
	}

	return commands;
}

void sendCommand( std::string command )
{
	bool success = false;
	while( !success )
	{
		try
		{
			std::ofstream outfile("ui.conf");
			outfile << command;
			outfile.close();
			success = true;
		}
		catch(...)
		{
			success =  false;
		}
	}
}

void execCommand(int command, int arg, timer* clk, Calendar* coolCalendar)
{
	int hours = (clk -> getHours()) * 3600;
	int minutes = (clk -> getMinutes()) * 60;
	int seconds = clk -> getSeconds();

	switch(command)
	{
		case 0: //exit
			std::cout << "exit\n";
			loopControl = false;
			break;
		case 1: //stop
			std::cout << "stop\n";
			paused = true;
			break;
		case 2: //start
			std::cout << "start\n";
			paused = false;
			break;
		case 3: //timeformat:24
			std::cout << "timeformat: 24\n";
			clk -> set24hourmode(true);
			break;
		case 4: //timeformat:12
			std::cout << "timeformat: 12\n";
			clk -> set24hourmode(false);
			break;
		case 5: //display:on
			std::cout << "display: on\n";
			display = true;
			break;
		case 6: //display:off
			std::cout << "display: off\n";
			display = false;
			break;
		case 7: //zoom
			std::cout << "zoom\n";
			zoom = !zoom;
			break;
		case 51: //hour add
			std::cout << "hour add " << arg << "\n";
			if(clk -> getTimerMode() == 2)
			{
				clk -> addTime(arg * 3600);
			}
			else if(clk -> getTimerMode() == timerMode)
			{
				clk -> addTimerTime(arg * 3600);
			}
			break;
		case 52: //hour sub
			std::cout << "hour sub " << arg << "\n";
			if(clk -> getTimerMode() == 2)
			{
				clk -> addTime(arg * 3600 * (-1));
			}
			else if(clk -> getTimerMode() == timerMode)
			{
				clk -> addTimerTime(arg * 3600 * (-1));
			}
			break;
		case 53: //hour set
			std::cout << "hour set " << arg << "\n";
			if(clk -> getTimerMode() == 2)
			{
			clk -> setTimeInSeconds((arg * 3600) + minutes + seconds);
			}
			else if(clk -> getTimerMode() == timerMode)
			{
				clk -> setTimerTime((arg * 3600) + minutes + seconds);
			}
			break;
		case 61: //minute add
			std::cout << "minute add " << arg << "\n";
			if(clk -> getTimerMode() == 2)
			{
				clk -> addTime(arg * 60);
			}
			else if(clk -> getTimerMode() == timerMode)
			{
				clk -> addTimerTime(arg * 60);
			}
			break;
		case 62: //minute sub
			std::cout << "minute sub " << arg << "\n";
			if(clk -> getTimerMode() == 2)
			{
				clk -> addTime(arg * 60 * (-1));
			}
			else if(clk -> getTimerMode() == timerMode)
			{
				clk -> addTimerTime(arg * 60 * (-1));
			}
			break;
		case 63: //minute set
			std::cout << "minute set " << arg << "\n";
			if(clk -> getTimerMode() == 2)
			{
				clk -> setTimeInSeconds(hours + (arg * 60) + seconds);
			}
			else if(clk -> getTimerMode() == timerMode)
			{
				clk -> setTimerTime(hours + (arg * 60) + seconds);
			}
			break;
		case 71: //second add
			std::cout << "second add " << arg << "\n";
			if(clk -> getTimerMode() == 2)
			{
				clk -> addTime(arg);
			}
			else if(clk -> getTimerMode() == timerMode)
			{
				clk -> addTimerTime(arg);
			}
			break;
		case 72: //second sub
			std::cout << "second sub " << arg << "\n";
			if(clk -> getTimerMode() == 2)
			{
				clk -> addTime(arg * (-1));
			}
			else if(clk -> getTimerMode() == timerMode)
			{
				clk -> addTimerTime(arg * (-1));
			}
			break;
		case 73: //second set
			std::cout << "second set " << arg << "\n";
			clk -> setTimeInSeconds(hours + minutes + arg);
			if(clk -> getTimerMode() == 2)
			{
				clk -> setTimeInSeconds(hours + minutes + arg);
			}
			else if(clk -> getTimerMode() == timerMode)
			{
				clk -> setTimerTime(hours + minutes + arg);
			}
			break;
		case 81: //month add
			std::cout << "month add " << arg << "\n";
			coolCalendar -> addMonth(arg);
			break;
		case 82: //month sub
			std::cout << "month sub " << arg << "\n";
			coolCalendar -> subtractMonth(arg);
			break;
		case 83: //month set
			std::cout << "month set " << arg << "\n";
			coolCalendar -> setMonth(arg);
			break;
		case 91: //day add
			std::cout << "day add " << arg << "\n";
			coolCalendar -> changeDay(arg);
			break;
		case 92: //day sub
			std::cout << "day sub " << arg << "\n";
			coolCalendar -> changeDay(arg * (-1));
			break;
		case 149: //stopwatch enter
			std::cout << "stopwatch\n";
			clk->stopWatchRun(enter);
			break;
		case 101: //stopwatch stop
			std::cout << "stopwatch stop\n";
			clk->stopWatchRun(stop);
			break;
		case 102: //stopwatch start
			std::cout << "stopwatch start\n";
			clk->stopWatchRun(start);
			break;
		case 199: //stopwatch reset
			std::cout << "stopwatch reset\n";
			clk->stopWatchRun(reset);
			break;
		case 100: //stopwatch exit
			std::cout << "stopwatch exit\n";
			clk->stopWatchRun(stopTimer);
			break;
		case 249: //timer enter
			std::cout << "timer enter\n";
			clk->timerRun(enter);
			//clk->setTimer(setTime); //need to put in user input here
			break;
		case 201: //timer stop
			std::cout << "timer stop\n";
			clk->timerRun(stop);
			break;
		case 202: //timer start
			std::cout << "timer start\n";
			clk->timerRun(start);
			break;
		case 200: //timer exit
			clk->timerRun(stopTimer);
			std::cout << "timer exit\n";
			break;
		case 299: //timer reset
			clk->timerRun(reset);
			std::cout<< "timer reset\n";
			break;
	}
}

void timerCaller(timer* clk, int timer_ms, Calendar* coolCalendar)
{

	//Used for keepign track of timing using chrono
	long int timeTracker;
	while(loopControl)
	{

		//this gets the current timestamp in milliseconds
		timeTracker = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

		system("clear");

		if(display)
		{
			//This prints the time
			std::cout << gettime(clk) << " " << coolCalendar -> getDayOfWeek() <<"\n";
		}

		if(!paused)
		{

			if(clk->getTimerMode() == timerMode && !clk->isTimerPaused())
			{
				clk->timerRun(keepGoing);
			}
			if (clk->getTimerMode() == stopwatch && !clk->isTimerPaused())
			{
				clk->stopWatchRun(keepGoing);
			}

			//This increments the second counter
			int dayChange = clk->timing();

		}

		//sleep for the remainder of timer_ms (less the time it took to execute digitalRun)
		std::this_thread::sleep_for(std::chrono::milliseconds(timeTracker + (long) timer_ms - (long) std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()));

	}
}

void uiListener(timer* clk, Calendar* coolCalendar)
{
	sendCommand(" ");

	bool loopControl = true;
	while(loopControl)
	{
		//create ifstream for the input file and take in size
		std::ifstream ui("ui.conf");

		std::string codeStr;

		std::getline(ui, codeStr);

		std::vector<int> commands = divide( codeStr );

		if( commands.size() != 0 )
		{
			int command = commands[0];
			int arg = 0;
			if(commands.size() > 1)
			{
				arg = commands[1];
			}

						execCommand(command, arg, clk, coolCalendar);
		}

		sendCommand(" ");

		ui.close();

		//sleep for the remainder of timer_ms (less the time it took to execute digitalRun)
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	sendCommand(" ");
}

int main()
{
	timer* clk=new timer();
	Calendar* coolCalendar = new Calendar();

	std::thread timerCallerThread (timerCaller, clk, 1000, coolCalendar);  // spawn new thread
	std::thread uiListenerThread (uiListener, clk, coolCalendar);  // spawn new thread

	//Wait for the run thread to end (clock to end) then join so that resources can be deleted and program can terminate
	uiListenerThread.join();
	timerCallerThread.join();


	delete clk;
  return(0);
}

std::string gettime(timer * clk)
{
	std::string t = "";
	if(!zoom)
	{
		int temp=clk->getHours();
		if (temp>=10) {
			t=intToString(temp);
		}
		else {
			t="0"+intToString(temp);
		}
		temp=clk->getMinutes();
		if (temp>=10) {
			t=t+":"+intToString(temp);
		}
		else {
			t=t+":0"+intToString(temp);
		}
		temp=clk->getSeconds();
		if (temp>=10) {
			t=t+":"+intToString(temp);
		}else {
			t=t+":0"+intToString(temp);
		}
		if(!(clk->get24hourmode())){
			t=t+clk->getam_pm();
		}
	}
	else
	{
		int hours = clk->getHours();
		int minutes = clk->getMinutes();
		int seconds = clk->getSeconds();
		int digits[6];
		digits[0] = ((hours - hours % 10) / 10);
		digits[1] = (hours % 10);
		digits[2] = ((minutes - minutes % 10) / 10);
		digits[3] =	(minutes % 10);
		digits[4] = (seconds - seconds % 10) / 10;
		digits[5] =	(seconds % 10);

		for(int row = 0; row < 5; row ++)
		{
			for(int digit = 0; digit <6; digit++)
			{
				if(digit == 2 || digit == 4)
				{
					//add a colon
					if(row == 1 || row == 3)
					{
						t += " o ";
					}
					else
					{
						t+= "   ";
					}
				}
				if(digit != 0 && digit % 2 == 0)
				{
					//add a colon
				}
				t += "  " + asciiDigits[digits[digit]][row];
			}
			t += "\n";
		}
	}
 return t;
}
