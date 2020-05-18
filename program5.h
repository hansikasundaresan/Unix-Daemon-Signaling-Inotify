
#ifndef __PROGRAM5_H__
#define __PROGRAM5_H__
/*
 *
 *
 * Filename:            program5.h
 * Date:                04/18/2019
 * Author:              Hansika Sundaresan
 * Email:               hms180008@utdallas.edu
 * Version:             1.0
 * Copyright:           2019, All Rights Reserved
 *
 * Description:
 *
 *     header file with declaration of sub functions in project
 */
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <fstream>
#include <iostream>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>

using namespace std;


enum _mapKeys{CONFIGFILENAME, DAEMONMODE, VERBOSE, LOGFILE, PASSWORD, NUMVERSION, WATCHDIR};


extern map<int, string> myMap;


void commandLine(int, char**);
void parseConfigFile();

int processControl();
bool FileExists(const string& name);
void removePid();
void createPidFile(int);

void createLog();
void writeToLog(string message);
void closeFile();

void sigHand();
void signalHandling(int signum);

void inotifyStart();
#endif /*program5.h*/
 
