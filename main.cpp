#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <chrono>
#include <cassert>
#include <functional>
#include "timer.h"

void Start(timer* clk);

int main()
{
	timer* t=new timer();
	Start(t);
// user needs to have defined set the time before this point
	int n=1;
	std::cout<< "reached debug 2\n";
	do
	{
		std::cout<<"reached debug 3 \n";
		std::cout << t->getHours()<< ":"<<t->getMinutes()<<":"<<t->getSeconds() ;
		n++;
	}while(n==1);
	std::cout<< "reached debug 4 \n";
        return(0);
}
/*
user setting time of clock
*/
void Start(timer* clk){
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

  std::cout << "HR: \n";
  int hr;
  std::cin >> hr;
  std::cout << "MIN: \n";
  int min;
  std::cin >> min;
  std::cout << "Sec:\n ";
  int sec;
  std::cin >> sec;

  clk->setHours(hr);
  clk->setMinutes(min);
  clk->setSeconds(sec);

	std::cout << "reached debug 1\n";
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
