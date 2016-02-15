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


int main()
{
	timer* t=new timer();

	Start(t);
	bool time_lord=true;
// user needs to have defined set the time before this point
	std::cout <<"orignal time:"<< gettime(t);
	std::cout <<"\n";
	

	int startSecs = time(0);
	int curSecs = startSecs;
	
	std::ifstream time_reader("time.txt");
	char readchar= time_reader.get();
	time_reader.close();
	
	do
	{

		std::cout << gettime(t)<<"\r";
		t->timing();
		curSecs=time(0);

		if(curSecs >= startSecs+5) //open file, check if its a y, if it is a 'n' break the loop and return to the menu, else
		{
			startSecs=curSecs;
			time_reader.open("time.txt");
			char c=time_reader.get();

			std::cout << c << std::endl;



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

		}



	}while(time_lord);
				delete t;
        return(0);
}
/*
user setting time of clock
*/
void Start(timer* clk)
{
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
		t=std::to_string(temp);
	}
	else {
		t="0"+std::to_string(temp);
	}
	temp=clk->getMinutes();
	if (temp>=10) {
		t=t+":"+std::to_string(temp);
	}
	else {
		t=t+":0"+std::to_string(temp);
	}
	temp=clk->getSeconds();
	if (temp>=10) {
		t=t+":"+std::to_string(temp);
	}else {
		t=t+":0"+std::to_string(temp);
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
