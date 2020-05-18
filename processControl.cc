/*
 *
 *
 * Filename:            processControl.cc
 * Date:                04/18/2019
 * Author:              Hansika Sundaresan
 * Email:               hms180008@utdallas.edu
 * Version:             1.0
 * Copyright:           2019, All Rights Reserved
 *
 * Description:
 *
 *      uses fork call to create child process for daemon
 */
#include "program5.h"

using namespace std;

bool FileExists(const std::string& name){
        struct stat buffer;
        return (stat(name.c_str(), &buffer) == 0);
}

int processControl(){
        writeToLog("In processControl() to fork for Daemon");
        pid_t pid = fork();

        if (pid<0){
                cout<<"Fork failed." <<endl;
                exit(1);
        }

	if (pid>0){
		if(myMap[VERBOSE] == "true"){
			writeToLog("Parent exited.");
		}
		exit(1);
	}
	

        if(pid == 0){
		writeToLog("Kid created from fork, only this process running");	
		return getpid();
        }
        return 0;
}

void createPidFile(int pidIdNum){
	if(FileExists("cs3377dirmond.pid")){ 
          	writeToLog( "Daemon is already running");
	        exit(1);
	}

	else{
		ofstream pidFile("cs3377dirmond.pid");
		pidFile <<pidIdNum <<endl;
		pidFile.close();
		if(myMap[VERBOSE] == "true"){
			writeToLog("pid file created and closed with pidID of child process");
		}
	}
	return;
}

void removePid(){	
	if(myMap[VERBOSE] == "true"){
		writeToLog("Removing pid file, process killed");
	}
        remove("cs3377dirmond.pid");
        return;
}
