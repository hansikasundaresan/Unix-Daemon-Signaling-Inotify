/*
 *
 *
 * Filename:            parseCommandLine.cc
 * Date:                04/18/2019
 * Author:              Hansika Sundaresan
 * Email:               hms180008@utdallas.edu
 * Version:             1.0
 * Copyright:           2019, All Rights Reserved
 *
 * Description:
 *
 *      uses tclap to parse through command line arguments
 */

#include <map>
#include <iostream>
#include "tclap/CmdLine.h"
#include "program5.h"
using namespace std;


void commandLine(int argc,char **argv){


	try{

		//This is the command line variable

		TCLAP::CmdLine cmd("CS", ' ', "1.0");

		TCLAP::SwitchArg daemon("d", "daemon", "Run in daemon mode", cmd, false);


		TCLAP::UnlabeledValueArg<string> configFileArg("configfile", "config filename", false, "cs3377dirmond.conf", "config filename");
		cmd.add(configFileArg);

		cmd.parse(argc,argv);


		bool dFlag = daemon.getValue();


		if(dFlag){
			myMap[DAEMONMODE] = "true";
		}


		else{
			myMap[DAEMONMODE] = "false";
		}


		myMap[CONFIGFILENAME] = configFileArg.getValue();

	}

	//This is the catch statement that will print out the following statements if there are errors in the code

	catch(TCLAP::ArgException &e){
		cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
	}

	return;

}
