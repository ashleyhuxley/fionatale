#ifndef FTLOG_H
#define FTLOG_H

#include <string>
#include <fstream>
#include <iostream>
#include "game.h"

using namespace std;

extern inline void Log(string line)
{
	ofstream logFile("logs/" + Game::current.player.getName(), ofstream::out | ofstream::app);

	if (logFile.is_open())
	{
		logFile << line << "\n";
	}
	else
	{
		cout << "Something went wrong with opening the file!\n";
		cout << line << "\n";
	}

	logFile.close();
}

extern inline void Dbg(string line)
{
	ofstream logFile("dbg.txt", ofstream::out | ofstream::app);

	if (logFile.is_open())
	{
		logFile << line << "\n";
	}
	else
	{
		cout << "Something went wrong with opening the file!";
	}

	logFile.close();
}

#endif
