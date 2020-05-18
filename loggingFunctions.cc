/*
 *
 *
 * Filename:            loggingFunctions.cc
 * Date:                04/18/2019
 * Author:              Hansika Sundaresan
 * Email:               hms180008@utdallas.edu
 * Version:             1.0
 * Copyright:           2019, All Rights Reserved
 *
 * Description:
 *
 *      logging what occurs with Daemon
 */
#include "program5.h"

ofstream log;

void createLog(){
	log.open(myMap[LOGFILE].c_str());
	if(!log.is_open()){
		cout << "Error: log file could not be created or opened" << endl;
	}
	else{
		if(myMap[DAEMONMODE] == "true"){
			if(myMap[VERBOSE] == "true"){
				log << "Currently: log file made, Daemon started" << endl;
			}
		}
		else{
			if(myMap[VERBOSE] == "true"){
				log << "Currently: log file made, running without daemon" << endl;
			}
		}
	}


}

void writeToLog(string message){
	log << message << endl;
}

void closeFile(){
	log.close();
}
