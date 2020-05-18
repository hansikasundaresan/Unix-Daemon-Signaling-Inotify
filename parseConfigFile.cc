/*
 *
 *
 * Filename:            parseConfigFile.cc
 * Date:                04/18/2019
 * Author:              Hansika Sundaresan
 * Email:               hms180008@utdallas.edu
 * Version:             1.0
 * Copyright:           2019, All Rights Reserved
 *
 * Description:
 *
 *      uses RudeConfig to parse through conf file
 */
#include "program5.h"
#include "src/config.h"
#include <iostream>
using namespace rude;

void parseConfigFile(){
	const char *inputFile = myMap[CONFIGFILENAME].c_str();
	Config myconfig;


	if(myconfig.load(inputFile)){
		if(myconfig.setSection("Parameters",false)){
		if(myconfig.exists("Verbose")){
			myMap[VERBOSE] = myconfig.getStringValue("Verbose");
		}
		else{
			cout << "Missing verbose definition" << endl;
		}
		if(myconfig.exists("LogFile")){
			myMap[LOGFILE] = myconfig.getStringValue("LogFile");
		}
		else{
			cout << "Missing LogFile definition" << endl;
		}
		
		if(myconfig.exists("Password")){
			if(myMap[PASSWORD].empty()){
				myMap[PASSWORD] = myconfig.getStringValue("Password");
			}
			else{
				string s = myconfig.getStringValue("Password");
				if(s.compare(myMap[PASSWORD])!=0){
					if(myMap[DAEMONMODE] == "true"){
						writeToLog("ERROR: Password has been changed and should not be");
						closeFile();
						exit(1);
					}
					else{
						cout << "error in parseConfigFile: Password changed" << endl;
					}
				}
			}
		}
		else{
			cout << "Missing password definition" << endl;
		}
		if(myconfig.exists("NumVersions")){
			myMap[NUMVERSION] = myconfig.getStringValue("NumVersions");
		}
		else{
			cout << "Missing NumVersions definition" << endl;
		}
		if(myconfig.exists("WatchDir"))
		{
			if(myMap[WATCHDIR].empty()){
		
				myMap[WATCHDIR] = myconfig.getStringValue("WatchDir");
			}
			else{
				string s = myconfig.getStringValue("WatchDir");
				if(s.compare(myMap[WATCHDIR])){
					 if(myMap[DAEMONMODE] == "true"){
                                               writeToLog("ERROR: Password has been changed and should not have");
						 closeFile();										                       exit(1);
		 											                                         }
				
				else{
					cout<<"error in paseConfigFile: watch dir changed"<<endl;
				}
				}

			}
		}
		else{
			cout << "Missing WatchDir definition" << endl;
		}
		}	
	}
	else{
		cout << "Error loading input file." << endl;
	}
}
