#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <locale>

bool stopwatchMode = false;
bool timerMode = false;

std::string validCommands[17] = {"exit", "help", "stop", "start", "timeFormat", "display", "zoom", "stopwatch", "timer", "hour", "minute", "second", "month", "day", "add", "sub", "set"};

std::string helpString = "***************\nCLOCKSHELL HELP\n***************\nexit - Exit the program.\nhelp - Display this help message.\nstop - Stop the clock, timer, or stopwatch.\nstart - Start the clock, timer, or stopwatch.\ntimeFormat - Change the time format.  Valid syntax is \"timeFormat 24\" or \"timeFormat 12\" to specify 24 or 12 hour time.\ndisplay - Turn the display on or off.  Valid syntax is \"display off\" or \"display on\" to specify turning the display on or off.\nzoom - Toggle the display zoom.\nstopwatch - Used to give commands to the stopwatch.\n			To enter stopwatch mode, enter \"stopwatch\"\n            To start the stopwatch, enter \"stopwatch start\", and to stop enter \"stopwatch stop\"\n            To reset the stopwatch, enter \"stopwatch reset\"\n            To exit stopwatch mode, enter \"stopwatch exit\"\ntimer - Enter timer mode\n            To enter timer mode enter \"timer\".\n            To set the the time of the timer, enter timer mode and then just use \"<hour|minute|second>\" \"<add|sub|set> <valid_integer_argument>\" as normal\n            To start the timer enter \"timer start\", and to stop the timer enter \"timer stop\"\n            To exit timer mode enter \"timer exit\"\nhour - Specify a change in the number of hours using add, sub, or set commands.\nminute - Specify a change in the number of minutes using add, sub, or set commands.\nsecond - Specify a change in the number of seconds using add, sub, or set commands.\nmonth - Specify a change in the month using add, sub, or set commands.\nday - Specify a change in the day using add or sub commands.  Set is not an available command for day.\nadd - Secondary command used to add to the number of hours, minutes, seconds, months, or days.  This command accepts an integer as an argument (ex: hour add 3)\nsub - Secondary command used to subtract from the number of hours, minutes, seconds, months, or days.  This command accepts an integer as an argument (ex: hour sub 5)\nset - Secondary command used to set the number of hours, minutes, seconds, months, or days.  This command accepts an integer as an argument (ex: month set 3).  Note: the integer argument must be within the valid range.";

//this page was referenced in creating this function http://stackoverflow.com/questions/890164/how-can-i-split-a-string-by-a-delimiter-into-an-array
std::vector<std::string> divide(std::string command)
{
	char delim = ' ';
    std::string next;
    std::vector<std::string> result;

    for ( std::string::const_iterator iter = command.begin(); iter != command.end(); iter++ )
    {
        if ( *iter == delim )
        {
            if ( !next.empty() )
            {
                result.push_back(next);
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
         result.push_back( next );
    }
    return result;
}

int getCommandCode(std::string command)
{
	for( int i = 0; i < 17; i++ )
	{
		if( command == validCommands[i] )
		{
			return i;
		}
	}
	return -1;
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
	        //std::cout << std::current_exception().what(); //For debugging TODO: remove this when finished
	        success =  false;
		}
	}
}

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

std::string stringToLowercase(std::string str)
{
	std::locale myLocale;
	std::string lowerString = "";

	for (int i = 0; i < str.length(); i++)
	{
		lowerString += std::tolower( str[i], myLocale );
	}

	return lowerString;
}

bool isStringInteger(std::string str)
{
	std::istringstream ss(str);
	int test;
	if ( !( ss >> test ) )
	{
		return false;
	}
	return true;
}

int main( int argc, char* argv[] )
{
	std::cout << "Welcome to the clock shell\n";

	bool loopControl = true;

	while( loopControl )
	{
		std::string command;

		std::cout << "ClockShell";
		if(stopwatchMode) std::cout << "[stopwatch]";
		else if(timerMode) std::cout << "[timer]";
		std::cout << ">> ";

		std::getline( std::cin, command );
		if( command != "" )
		{
			std::vector<std::string> commands = divide( command );

			std::string primary = commands[0];

			switch( getCommandCode( primary ) )
			{
				case 0: //exit
					std::cout << "Exiting...\n";
					sendCommand( "000" );
					loopControl = false;
					break;
				case 1: //help
					std::cout << helpString;
					break;
				case 2: //stop
					sendCommand( "001" );
					break;
				case 3: //start
					sendCommand( "002" );
					break;
				case 4:	//timeFormat
					if( commands.size() < 2 )
					{
						std::cout << "Error: timeFormat requires an integer argument (valid values are 12 and 24)\n";
					}
					else if( commands[1] == "24" )
					{
						sendCommand( "003" );
					}
					else if(commands[1] == "12" )
					{
						sendCommand( "004" );
					}
					else
					{
						std::cout << "Error: invalid argument.  Valid arguments are 12 and 24\n";
					}
					break;
				case 5: //display
					if( commands.size() < 2 )
					{
						std::cout << "Error: display requires a second string argument (valid argumentss are on and off)\n";
					}
					else if( stringToLowercase( commands[1] ) == "on")
					{
						sendCommand( "005" );
					}
					else if( stringToLowercase( commands[1] ) == "off" )
					{
						sendCommand( "006" );
					}
					else
					{
						std::cout << "Error: invalid argument (valid arguments are on and off)\n";
					}
					break;
				case 6: //zoom
					sendCommand("007");
					break;
				case 7: //stopwatch
					if( timerMode )
					{
						std::cout << "Error: you cannot start the stopwatch while in timer mode\n";
					}
					else if( commands.size() > 2 )
					{
						std::cout << "Error: stopwatch commands cannot have more than 2 arguments (ex: stopwatch <command>)\n";
					}
					else if( commands.size() == 1)
					{
						if(!stopwatchMode)
						{
							stopwatchMode = true;
							std::cout << "Entering stopwatch mode...\n";
							sendCommand("149");
						}
						else
						{
							std::cout << "Error: you are already in stopwatch mode\n";
						}
					}
					else if( !stopwatchMode )
					{
						std::cout << "Error: you must enter stopwatch mode to control the stopwatch (enter \"stopwatch\" to start stopwatch mode)\n";
					}
					else if( stringToLowercase( commands[1] ) == "stop")
					{
						sendCommand("101");
					}
					else if( stringToLowercase( commands[1] ) == "start")
					{
						sendCommand("102");
					}
					else if( stringToLowercase( commands[1] ) == "reset")
					{
						sendCommand("149");
					}
					else if( stringToLowercase( commands[1] ) == "exit")
					{
						stopwatchMode = false;
						std::cout << "Exiting stopwatch mode...\n";
						sendCommand("100");
					}
					else
					{
						std::cout << "Error: unrecognized stopwatch command\n";
					}
					break;
				case 8:	//timer
					if( stopwatchMode )
					{
						std::cout << "Error: you cannot start the timer while in stopwatch mode\n";
					}
					else if( commands.size() > 2 )
					{
						std::cout << "Error: timer commands cannot have more than 2 arguments (ex: timer command)\n";
					}
					else if( commands.size() == 1)
					{
						if(!timerMode)
						{
							timerMode = true;
							std::cout << "Entering timer mode...\n";
							sendCommand("249");
						}
						else
						{
							std::cout << "Error: you are already in timer mode\n";
						}
					}
					else if( !timerMode )
					{
						std::cout << "Error: you must enter timer mode to control the timer (enter \"timer\" to start timer mode)\n";
					}
					else if( stringToLowercase( commands[1] ) == "stop")
					{
						sendCommand("201");
					}
					else if( stringToLowercase( commands[1] ) == "start")
					{
						sendCommand("202");
					}
					else if( stringToLowercase( commands[1] ) == "exit")
					{
						timerMode = false;
						std::cout << "Exiting timer mode...\n";
						sendCommand("200");
					}
					else
					{
						std::cout << "Error: unrecognized timer command\nNote: To set the the time of the timer, enter timer mode and then just use <hour|minute|second> <add|sub|set> <valid_integer_argument> as normal\n";
					}
					break;
				case 9:	//hour
					if( stopwatchMode )
					{
						std::cout << "Error: you cannot change the hour while in stopwatch mode\n";
					}
					else if( commands.size() < 3 )
					{
						std::cout << "Error: hour requires a second command (add, sub, or set) and a valid integer argument (must be from 0-23 if using set)\n";
					}
					else if( !isStringInteger( commands[2] ) )
					{
						std::cout << "Error: you did not enter an integer for the argument\n";
					}
					else if( stringToLowercase( commands[1] ) == "add" )
					{
						sendCommand( "051 " + intToString(stringToInt( commands[2] )) );
					}
					else if( stringToLowercase( commands[1] ) == "sub" )
					{
						sendCommand( "052 " + intToString(stringToInt( commands[2] )) );
					}
					else if( stringToLowercase( commands[1] ) == "set" )
					{
						int hourSet = stringToInt( commands[2] );
						if( hourSet < 0 || hourSet > 23 )
						{
							std::cout << "Error: you did not enter a valid hour range (0-23)\n";
						}
						else
						{
							sendCommand( "053 " + intToString( hourSet ) );
						}
					}
					else
					{
						std::cout << "Error: unrecognized command (valid secondary commands are add, sub, and set)\n";
					}
					break;
				case 10: //minute
					if( stopwatchMode )
					{
						std::cout << "Error: you cannot change the minute while in stopwatch mode\n";
					}
					else if( commands.size() < 3 )
					{
						std::cout << "Error: minute requires a second command (add, sub, or set) and a valid integer argument (must be from 0-59 if using set)\n";
					}
					else if( !isStringInteger( commands[2] ) )
					{
						std::cout << "Error: you did not enter an integer for the argument\n";
					}
					else if( stringToLowercase( commands[1] ) == "add" )
					{
						sendCommand( "061 " + intToString(stringToInt( commands[2] )) );
					}
					else if( stringToLowercase( commands[1] ) == "sub" )
					{
						sendCommand( "062 " + intToString(stringToInt( commands[2] )) );
					}
					else if( stringToLowercase( commands[1] ) == "set" )
					{
						int minuteSet = stringToInt( commands[2] );
						if( minuteSet < 0 || minuteSet > 23 )
						{
							std::cout << "Error: you did not enter a valid minute range (0-59)\n";
						}
						else
						{
							sendCommand( "063 " + intToString( minuteSet ) );
						}
					}
					else
					{
						std::cout << "Error: unrecognized command (valid secondary commands are add, sub, and set)\n";
					}
					break;
				case 11: //second
					if( stopwatchMode )
					{
						std::cout << "Error: you cannot change the seconds while in stopwatch mode\n";
					}
					else if( commands.size() < 3 )
					{
						std::cout << "Error: second requires a second command (add, sub, or set) and a valid integer argument (must be from 0-59 if using set)\n";
					}
					else if( !isStringInteger( commands[2] ) )
					{
						std::cout << "Error: you did not enter an integer for the argument\n";
					}
					else if( stringToLowercase( commands[1] ) == "add" )
					{
						sendCommand( "071 " + intToString(stringToInt( commands[2] )) );
					}
					else if( stringToLowercase( commands[1] ) == "sub" )
					{
						sendCommand( "072 " + intToString(stringToInt( commands[2] )) );
					}
					else if( stringToLowercase( commands[1] ) == "set" )
					{
						int secondSet = stringToInt( commands[2] );
						if( secondSet < 0 || secondSet > 59 )
						{
							std::cout << "Error: you did not enter a valid second range (0-59)\n";
						}
						else
						{
							sendCommand( "073 " + intToString( secondSet ) );
						}
					}
					else
					{
						std::cout << "Error: unrecognized command (valid secondary commands are add, sub, and set)\n";
					}
					break;
				case 12: //month
					if( stopwatchMode )
					{
						std::cout << "Error: you cannot change the month while in stopwatch mode\n";
					}
					else if( timerMode )
					{
						std::cout << "Error: you cannot change the month while in timer mode\n";
					}
					else if( commands.size() < 3 )
					{
						std::cout << "Error: month requires a month command (add, sub, or set) and a valid integer argument (must be from 1-12 if using set)\n";
					}
					else if( !isStringInteger( commands[2] ) )
					{
						std::cout << "Error: you did not enter an integer for the argument\n";
					}
					else if( stringToLowercase( commands[1] ) == "add" )
					{
						sendCommand( "081 " + intToString(stringToInt( commands[2] )) );
					}
					else if( stringToLowercase( commands[1] ) == "sub" )
					{
						sendCommand( "082 " + intToString(stringToInt( commands[2] )) );
					}
					else if( stringToLowercase( commands[1] ) == "set" )
					{
						int monthSet = stringToInt( commands[2] );
						if( monthSet < 1 || monthSet > 12 )
						{
							std::cout << "Error: you did not enter a valid month range (1-12)\n";
						}
						else
						{
							sendCommand( "083 " + intToString( monthSet ) );
						}
					}
					else
					{
						std::cout << "Error: unrecognized command (valid secondary commands are add, sub, and set)\n";
					}
					break;
				case 13: //day
					if( stopwatchMode )
					{
						std::cout << "Error: you cannot change the day while in stopwatch mode\n";
					}
					else if( timerMode )
					{
						std::cout << "Error: you cannot change the day while in timer mode\n";
					}
					else if( commands.size() < 3 )
					{
						std::cout << "Error: day requires a day command (add or sub) and a valid integer argument\n";
					}
					else if( !isStringInteger( commands[2] ) )
					{
						std::cout << "Error: you did not enter an integer for the argument\n";
					}
					else if( stringToLowercase( commands[1] ) == "add" )
					{
						sendCommand( "091 " + intToString(stringToInt( commands[2] )) );
					}
					else if( stringToLowercase( commands[1] ) == "sub" )
					{
						sendCommand( "092 " + intToString(stringToInt( commands[2] )) );
					}
					else if( stringToLowercase( commands[1] ) == "set" )
					{
						std::cout << "Error: the set command is not supported for day\n";
					}
					else
					{
						std::cout << "Error: unrecognized command (valid secondary commands are add and sub)\n";
					}
					break;
				case 14: //add
					std::cout << "Error: add cannot be a primary command\n";
					break;
				case 15: //sub
					std::cout << "Error: sub cannot be a primary command\n";
					break;
				case 16: //set
					std::cout << "Error: set cannot be a primary command\n";
					break;
				default:
					std::cout << "Error: unrecognized command \"" << primary <<"\"\n";
					break;
			}
		}
	}
	return 0;
}
