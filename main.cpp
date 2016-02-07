#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <cassert>
#include <functional>
int main()
{

        return(0);
}


/*
 *  *
 *   *
 *   template<typename T>
 *   double Sorts<T>::sortTimer(std::function<void(T[],int)> sort, T arr[], int size)
 *   {
 *
 *           //declartations---------------------
 *                   std::chrono::system_clock::time_point start;
 *                           std::chrono::system_clock::time_point end;
 *                                   std::chrono::duration<double> elapsed;
 *                                           //
 *                                                   //timine something--------------
 *                                                           start = std::chrono::system_clock::now();       //starts the timer
 *                                                                   std::cout << "\n calling sort in sortTimer \n";
 *                                                                           sort(arr, size);                                //performs the sort
 *                                                                                   end = std::chrono::system_clock::now();         //ends the timer
 *                                                                                           elapsed = (end-start);                          //computes the total time
 *                                                                                                   std::cout << "Sort completed in " << elapsed.count() << " seconds \n";
 *                                                                                                           return(elapsed.count());
 *                                                                                                           }
 *
