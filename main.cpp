#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <chrono>
#include <cassert>
#include <functional>
#include "timer.h"

void Start(timer* clk);
void Reset(timer* clk);
std::string gettime(timer* clk);


int main()
{
	timer* t=new timer();
	Start(t);
// user needs to have defined set the time before this point
	std::cout <<"orignal time:" gettime(t);
	std::cout <<"\n";
	do
	{
		std::cout << gettime(t)<<"\r";
		t->timing();
	}while(1);
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
					std::cout << "Invalid input" << std::endl;
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
	hr=hr%24;
	std::cout << hr << std::endl;


  std::cout << "MIN: \n";
  int min;
  std::cin >> min;
	//min=min%60;

  std::cout << "Sec:\n ";
  int sec;
  std::cin >> sec;
	//sec=sec%60;


if(clk->get24hourmode()==false && am_pm=="pm")
{
	hr=hr%12;
	hr=hr+12;

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

//
// bool Reset(Timer* clk){
// 		int i=1;
// 		while(i==1){
// 			std::cout << "Clock menu \n" << "============ \n"<<"what do want to change(insert number) \n";
// 			std::cout << "1) change clock mode " << std::endl;
// 			std::cout << "2) change time" << std::endl;
// 			std::cout << "3) end the clock" << std::endl;
//
//
// 			int input;
// 			std::cin >> input;
//
//
// 			if (input==1) {
// 				clk->set24hourmode(!(clk->get24hourmode()));
// 			}
// 			else if (input==2) {
// 				/* code */
// 			}
// 			else if(input==3) {
// 				/* code */
// 			}else{
// 				std::cout << "invalid input" << std::endl;
// 			}
// 				std::cout << "would you like change anything else? (y/n)" << std::endl;
// 					char x;
//
// 		}
