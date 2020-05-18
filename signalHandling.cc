/*
 *
 *
 * Filename:            signalHandling.cc
 * Date:                04/18/2019
 * Author:              Hansika Sundaresan
 * Email:               hms180008@utdallas.edu
 * Version:             1.0
 * Copyright:           2019, All Rights Reserved
 *
 * Description:
 *
 *      handles signals sent through kill command
 */
#include "program5.h"
#include <signal.h>
#include <csignal>
#include <iostream>
#include <stdio.h>

using namespace std;

void signalHandling(int signum){
	//printf("checker in signalHandling functions");
        if(signum == SIGINT || signum == SIGTERM){
        writeToLog("Daemon interrupted with command. Killing Daemon");
        removePid();
        closeFile();
	exit(signum);
        }
        else if (signum == SIGHUP){
                writeToLog("Re-reading contents of Conf file.");
                parseConfigFile();
                writeToLog("Configurations re-read and updated");
        }
}

void sigHand(){
//	cout<<"first part"<<endl;
	signal(SIGINT, signalHandling);
	sleep(1);
//	raise(SIGINT);
//cout<<"done with signint"<<endl;
	signal(SIGTERM, signalHandling);
	sleep(1);
//	raise(SIGTERM);
//cout<<"done with sigterm"<<endl;
	signal(SIGHUP, signalHandling);
	sleep(1);
//	raise(SIGHUP);
//	cout<<"done with sighup"<<endl;
}
