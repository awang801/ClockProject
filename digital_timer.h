#include <string>
#include <time.h>
#include <iostream>

#ifndef "DIGITAL_H"
#define "DIGITAL_H"

class timer
{
    public:
    
        static int* ConvertSeconds (int seconds);
        
        void togglePause();
        
        void toggleHourFormat();
        
        void addTime(int amt);
        
        static std::string TwelveHourPm(bool aft);
        
        bool military_time;
        
        static bool pause;
        
        static bool afternoon;
        
        int total_seconds;
    
};

#endif