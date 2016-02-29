//similar to CoolClockTimer.java
//used to take a seconds value and convert into a time format


#include "digital_timer.h"

military_time = true;
afternoon = false;    
    
int* digital_timer::ConvertSeconds(int secs)
{
    int[] time = {0,0,0,0,0,0};
    int hours, mins, seconds;
    total_seconds = secs;
    
    if(military_time)
    {
        hours = total_seconds / 3600;
        time[0] = hours / 10;
        time[1] = hours % 10;
        total_seconds = total_seconds - (hours * 3600);
        mins = total_seconds / 60;
        time[2] = mins / 10;
        time[3] = mins % 10;
        total_seconds = total_seconds - (mins * 60);
        seconds = total_seconds;
        time[4] = seconds / 10;
        time[5] = seconds % 10;
    }
        
    else
    {
        hours = total_seconds / 3600;
        total_seconds = total_seconds - (hours * 3600);
        mins = total_seconds / 60;
        time[2] = mins / 10;
        time[3] = mins % 10;
        total_seconds = total_seconds - (mins * 60);
        seconds = total_seconds;
        time[4] = seconds / 10;
        time[5] = seconds % 10;
        if(hours > 12)
        {
            hours = hours - 12;
            afternoon = true;
        }
        time[0] = hours / 10;
        time[1] = hours % 10;
        if((time[0] == 0) && (time[1] == 0))
        {
            time[0] = 1;
            time[1] = 2;
        }
        
    }      
    for(int i = 0; i < 6; i++)
    {
        cout << time[i];
        if((i == 1) || (i == 3))
        {
            cout << ":";
        }
    }
    return time;
}
    
std::string digital_timer::TwelveHourPm(bool aft)
{
    if(aft)
        return("pm");
    else
        return("am");
}

void digital_timer::addTime(int amt)
{
    total_seconds = (total_seconds+amt)%86400;
}

void digital_timer::togglePause()
{
    pause = !pause;
}

void digital_timer::toggleHourFormat()
{
    military_time = !military_time;
}