/*
 *
 *
 * Filename:            inotidyFunctions.cc
 * Date:                04/18/2019
 * Author:              Hansika Sundaresan
 * Email:               hms180008@utdallas.edu
 * Version:             1.0
 * Copyright:           2019, All Rights Reserved
 *
 * Description:
 *
 *      utilizes inotify to watch changes made to files
 */
#include "program5.h"
#include <linux/limits.h>
#include <string>
#include <sstream>
using namespace std;

void inotifyStart()
{
    //declare variables
    size_t buffsize = sizeof(struct inotify_event) + PATH_MAX + 1;
    struct inotify_event *event = (struct inotify_event *) malloc(buffsize);
    int length, watchDir;
    int fileDesc= inotify_init();
    int acc = 0;

    //if file descriptor returns error print it
    if(fileDesc < 0)
    {
        cerr << "INOTIFY ERROR: file descriptor error" << endl;
        return;
    }

    //start watching the user inputted directory and begin reading
    watchDir = inotify_add_watch(fileDesc, myMap[WATCHDIR].c_str(), IN_MODIFY | IN_CREATE | IN_DELETE);
    length = read(fileDesc, event, buffsize);

    //if there is an error reading then print and error and exit
    if(length < 0)
    {
        cerr << "INOTIFY ERROR: read error" << endl;
        return;
    }
	time_t ttime = time(0);
	tm *local_time = localtime(&ttime);
    //this function is run every time an event happens
    while(acc < length)
    {
    	//while the event has a length
        if(event->len){	
		string fileName = event->name;
		int year = 1900 + local_time->tm_year;
		int month = 1+ local_time->tm_mon;
		int day = local_time->tm_mday;
		int hour = local_time->tm_hour;
		int min = 1+local_time->tm_min;
		int sec = 1+local_time->tm_sec;
		
		stringstream ss;
		
		ss<<year;
		string year1;
		ss>>year1;
	
		ss.clear();
		ss.str("");
		ss<<month;
		string month1;
		ss>>month1;
		
		ss.clear();
		ss.str("");
		ss<<day;
		string day1;
		ss>>day1;

		ss.clear();
		ss.str("");
		ss<<hour;
		string hour1;
		ss>>hour1;
		
		ss.clear();
		ss.str("");
		ss<<min;
		string min1;
		ss>>min1;
		
		ss.clear();
		ss.str("");
		ss<<sec;
		string sec1;
		ss>>sec1;

		string folder = "cp ./" +fileName+" "+myMap[WATCHDIR] +"/.versions";
		string move = "mv ./.versions/"+fileName+" "+"./.versions/"+fileName+"."+year1+"."+month1+"."+day1+"-"+hour1+":"+min1+":"+sec1;
            
	    if(event->mask & IN_CREATE){
	    	fileName = fileName+" has been created";	
                writeToLog(fileName);
		system(folder.c_str());
		system(move.c_str());
            }
            if(event->mask & IN_DELETE){
	    	fileName = fileName+" has been deleted";
		writeToLog(fileName);
		system(folder.c_str());
            	system(move.c_str());
	    }
            if(event->mask & IN_MODIFY){
	    	fileName = fileName+" has been modified";
	    	writeToLog(fileName);
		system(folder.c_str());
            	system(move.c_str());
	    }
        }
        acc += sizeof(struct inotify_event) + event->len;
    }
	
    inotify_rm_watch(fileDesc, watchDir);
    close(fileDesc);
    free(event);
    return;
}

