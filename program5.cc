/*
 *
 *
 * Filename:            program5.cc
 * Date:                04/18/2019
 * Author:              Hansika Sundaresan
 * Email:               hms180008@utdallas.edu
 * Version:             1.0
 * Copyright:           2019, All Rights Reserved
 *
 * Description:
 *
 *      main routine with sub functions
 */
#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>
#include "program5.h"
#include <sys/stat.h>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <linux/limits.h>
using namespace std;

map<int,string> myMap;

int main(int argc,char **argv){

int wd, fd;
int pidId;
commandLine(argc,argv);
parseConfigFile();
createLog();


 if(myMap[VERBOSE] == "true"){
    writeToLog("Starting program in verbose mode, created log file");
  }


    if(FileExists("cs3377dirmond.pid")){
      writeToLog("Daemon is already running");
      exit(1);
    }
    else{
      if(myMap[VERBOSE] == "true"){
      	writeToLog("creating ./versions subfolder");
      }
      	string subfolder = "mkdir -p " + myMap[WATCHDIR] + "/.versions"; 
	system(subfolder.c_str());

      //create pid file and handle fork()
     if(myMap[DAEMONMODE]=="true"){
     	pidId= processControl();
	 if(myMap[VERBOSE] == "true"){
	            writeToLog("Moving to process control to call fork function");
		}
     }
	createPidFile(pidId);
	sigHand();
    //signal(<signalnam>,<name of signal handling function>)
     if(myMap[DAEMONMODE] =="false"){
    	writeToLog("Running without daemon");
	}
//wd = inotify_add_watch(fd, myMap[WATCHDIR].c_str(), IN_MODIFY | IN_CREATE | IN_DELETE);
 //	removePid();
//	closerFile;

     while(1)
     {
     	inotifyStart();
     }
     if(myMap[DAEMONMODE] == "false")
     {
     	removePid();
	closeFile();
     }
   //  inotify_rm_watch(fd, wd);
    // close(fd);
   }
  return 0;
}
