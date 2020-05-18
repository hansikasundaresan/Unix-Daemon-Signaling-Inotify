#!/usr/bin/make -f
#
# Filename:             Makefile
# Date:                 04/18/2020
# Author:               Hansika Sundaresan
# Email:                hms180008@utdallas.edu
# Version:              1.0
# Copyright:            2020, All Rights Reserved
#
# Description:
#       Builds a quick Makefile for Program 5. This makefile will
#       be in the form of a C++ compiler.

# Flags for the C implicit rules

CC = g++
CCFLAGS = -Wall
CPPFLAGS = -I include -I /home/011/h/hm/hms180008/program5/include

LDFLAGS = -L /home/011/h/hm/hms180008/program5/lib
LDLIBS = -l rudeconfig
STATIC= -static
# PROJECTNAME is a descriptive name used for the backup target

PROJECTNAME = Program5

EXEC = program5

OBJS = program5.o parseCommandLine.o parseConfigFile.o processControl.o loggingFunctions.o signalHandling.o inotifyFunctions.o

# This will create the executable that will link to either the scanner or parser

%o:%cc
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

all: $(EXEC)

# This will clean certain aspects of the file

clean:
	rm -f $(OBJS) $(EXEC) *.d *~ \#*

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDLIBS) $(LDFLAGS) $(STATIC)

# This wifdfsfll be used to create the backup file.

backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

