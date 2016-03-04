#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <vector>
#include <chrono>
#include <thread>

int stoi( std::string str )
{
	std::istringstream stoi(str); 
	int hourSet;

	if ( !(stoi >> hourSet) )
	{
		//uh oh
		hourSet = -1;
	}
	return hourSet;
}

std::string itos(int var)
{
	std::ostringstream itos;

	itos << var;

	return itos.str();
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

	commands.push_back(stoi(raw[0]));
	if(raw.size() > 1)
	{
		commands.push_back(stoi(raw[1]));
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
			std::ofstream outfile("ui.txt");
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

void execCommand(int command, int arg)
{
	switch(command)
	{
		case 0: //exit
			std::cout << "exit\n";
			break;
		case 1: //stop
			std::cout << "stop\n";
			break;
		case 2: //start
			std::cout << "start\n";
			break;
		case 3: //timeformat:24
			std::cout << "timeformat: 24\n";
			break;
		case 4: //timeformat:12
			std::cout << "timeformat: 12\n";
			break;
		case 5: //display:on
			std::cout << "display: on\n";
			break;
		case 6: //display:off
			std::cout << "display: off\n";
			break;
		case 7: //zoom
			std::cout << "zoom\n";
			break;
		case 51: //hour add
			std::cout << "hour add " << arg << "\n";
			break;
		case 52: //hour sub
			std::cout << "hour sub " << arg << "\n";
			break;
		case 53: //hour set
			std::cout << "hour set " << arg << "\n";
			break;
		case 61: //minute add
			std::cout << "minute add " << arg << "\n";
			break;
		case 62: //minute sub
			std::cout << "minute sub " << arg << "\n";
			break;
		case 63: //minute set
			std::cout << "minute set " << arg << "\n";
			break;
		case 71: //second add
			std::cout << "second add " << arg << "\n";
			break;
		case 72: //second sub
			std::cout << "second sub " << arg << "\n";
			break;
		case 73: //second set
			std::cout << "second set " << arg << "\n";
			break;
		case 81: //month add
			std::cout << "month add " << arg << "\n";
			break;
		case 82: //month sub
			std::cout << "month sub " << arg << "\n";
			break;
		case 83: //month set
			std::cout << "month set " << arg << "\n";
			break;
		case 91: //day add
			std::cout << "day add " << arg << "\n";
			break;
		case 92: //day sub
			std::cout << "day sub " << arg << "\n";
			break;
		case 149: //stopwatch enter
			std::cout << "stopwatch\n";
			break;
		case 101: //stopwatch stop
			std::cout << "stopwatch stop\n";
			break;
		case 102: //stopwatch start
			std::cout << "stopwatch start\n";
			break;
		case 199: //stopwatch reset
			std::cout << "stopwatch reset\n";
			break;
		case 100: //stopwatch exit
			std::cout << "stopwatch exit\n";
			break;
		case 249: //timer enter
			std::cout << "timer enter\n";
			break;
		case 201: //timer stop
			std::cout << "timer stop\n";
			break;
		case 202: //timer start
			std::cout << "timer start\n";
			break;
		case 200: //timer exit
			std::cout << "timer exit\n";
			break;
		default:
			//uh oh
			std::cout << "Error: Unrecognized command code\n";
			break;
	}
}

int main( int argc, char* argv[] )
{

	bool loopControl = true;
	
	while( loopControl )
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

			execCommand(command, arg);
		}

		sendCommand("");

		ui.close();

		std::string str;

		std::cin >> str; //replaces a thread sleep bc windows threading suxx
	}
	return 0;
}