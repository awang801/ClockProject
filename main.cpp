/**
*  @author	John McCain <johnm.freestate@gmail.com>
*  @author 	Audrey Evans <audreyevans@ku.edu>
*  @author Hari Ramanan <hramanan@ku.edu>
*  @author	Alan Wang <ultimate801@gmail.com>
*  @version 2.0 &nbsp;
*  @since 2016-02-14
*/



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
int monthtemp;
int daytemp;

/*
*	Converts an integer to a std::string
*	This is needed because std::to_string (as used in the original implementation) is not supported in every compiler
*	@param num the integer to be converted
*	@returns a std::string representation of the given integer
*/
std::string intToStr(int num);

std::string intToStr(int num){
	std::ostringstream stringConverter;

	stringConverter << num;

	return (stringConverter.str());
}

/*
This function returns the day of the weekday
@param int month, int day
@return string day of week
*/
std::string Calendar(int month, int day)
{
	int m_value = 0;
	int months[] = {31,29,31,30,31,30,31,31,30,31,30,31};
	std::string weekday[] = {"Fri","Sat","Sun","Mon","Tues","Wed","Thurs"};

	for(int i=0;i<month-1;i++)
	{
		m_value += months[i];
	}
	m_value += day;
	m_value = (m_value%7);



	if((m_value) == 0)
	{
		return(weekday[6]);
	}
	return (weekday[m_value-1]);
}


void run(timer* t, int timer_ms)
{
	bool time_lord=true;
	// user needs to have defined set the time before this point

	int startSecs = time(0);
	int curSecs = startSecs;

	std::ifstream time_reader("time.txt");
	char readchar= time_reader.get();
	time_reader.close();

	long int timeTracker;
	do
	{

		//this gets the current timestamp in milliseconds
    timeTracker = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

		std::cout << gettime(t)<<"\r";


		t->timing();
		curSecs=time(0);

		if(curSecs >= startSecs+5) //open file, check if its a y, if it is a 'n' break the loop and return to the menu, else
		{
			startSecs=curSecs;
			time_reader.open("time.txt");
			char c=time_reader.get();

			std::cout << c << "\r";



			if(c != readchar)
			{
				time_lord=Reset(t);
				time_reader.close();
				time_reader.open("time.txt");
				if(time_reader.good()){
				readchar=time_reader.get();
			}
			}

			time_reader.close();

			//sleep for the remainder of timer_ms (less the time it took to execute digitalRun)
	    std::this_thread::sleep_for(std::chrono::milliseconds(timeTracker + (long) timer_ms - (long) std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()));
		}
	}while(time_lord);
}

int main()
{
	timer* t=new timer();

	Start(t);

	std::thread timerCaller (run, t, 300);  // spawn new thread

  std::cout << "It's working!!1!\n";
	std::string weekday = Calendar(monthtemp,daytemp);
	std::cout<< weekday+"\n";
	timerCaller.join();

	delete t;
  return(0);
}


/*
user setting time of clock
*/
void Start(timer* clk)
{
	std::cout<<"Month?"<<std::endl;

	std::cin>>monthtemp;
	std::cout<<"Day?"<<std::endl;
	std::cin>>daytemp;

	 std::cout << "24 hr mode? (y/n)?" << std::endl;
	 char temp;
	 std::string am_pm="";
	 std::cin >> temp;
	 bool inputflag;
 do{

    if(temp=='Y'||temp=='y')
    {
      clk->set24hourmode(true);
      inputflag=true;
    }else if (temp=='N'||temp=='n')
	{
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
					std::cout << "Invalid input"<<am_pm << std::endl;
					std::cout << "Am or PM?" << std::endl;
					std::cin >> am_pm;
				}
			} while(true);

      	inputflag=true;
    	break;
    	}else
	{
     		std::cout << "Invalid input" << std::endl;
      		std::cout << "24 hr mode? (y/n)?" << std::endl;
		std::cin >> temp;
      		inputflag=false;
    	}

  }while(!(inputflag));
  inputflag=false;

  std::cout << "Set time:: (hh:mm:ss) \n" << std::endl;

  std::cout << "HR: \n";
  int hr;
  std::cin >> hr;
	while(std::cin.fail()) {
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
		else if (hr==12) {
			hr=0;
		}
	}
  clk->setHours(hr);
  clk->setMinutes(min);
  clk->setSeconds(sec);
}
std::string gettime(timer * clk)
{
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
