#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <chrono>
#include <cassert>
#include <functional>
#include "timer.h"

int main()
{
	timer t;
// user needs to have defined set the time before this point
	while(1)
	{
		std::cout << t.getHours()<< ":"<<t.getMinutes()<<":"<<t.getSeconds() <<"\r";
	}
        return(0);
}
/*
user setting time of clock
*/
void Start(timer clk){
 std::cout << "24 hr mode? (y/n)?" << std::endl;
 std::string temp;
 std::cin >> temp;
 bool inputflag;
  do{


    if(temp=="Y"||temp=="y")
    {
      /*set24flag*/
      inputflag=true;
    }else if (temp=="N"||temp=="n") {
      /*set 24 flag false*/
      inputflag=true;
      break;
    }else{
      std::cout << "Invalid input" << std::endl;
      std::cout << "24 hr mode? (y/n)?" << std::endl;
      inputflag=false;
    }

  }while(!(inputflag));
  inputflag=false;

  std::cout << "Set time:: (hh:mm:ss) \n" << std::endl;

  std::cout << "HR: ";
  int hr;
  std::cin >> hr;
  std::cout << "\n MIN: ";
  int min;
  std::cin >> min;
  std::cout << "\n Sec: ";
  int sec;
  std::cin >> sec;

  clk.setHours(hr);
  clk.setMinutes(min);
  clk.setSeconds(sec);
  
  // std::cout << "Set time:: (hh:mm:ss) \n" << std::endl;
  //

  // std::string temptime;
  //
  // if ( temptime.size()!=8|| temptime.at(2)!=':' || temptime.at(5)!=':'){
  //     std::cout << "Invalid input" << std::endl;
  //   }else{
  //
  //
  //   }
  //
  // }









}

