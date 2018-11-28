    
#CSC521 Operating system
#Project:      2 mydispatcher
#Programmer:   Rob Miles
#Professor:    Dr. Lee
#File Created: Oct 15, 2018
#File Updated: Oct 15, 2018

SOURCES = mydispatcher.c algFCFS.c algRR.c algSTN.c algSRT.c libstats.c libQmgr.c
OBJECTS = mydispatcher.o algFCFS.o algRR.o algSTN.o algSRT.o libstats.o libQmgr.o
HEADERS = mydispatcher.h
CC = gcc
CFLAGS = -g -Wall

all: mydispatcher

mydispatcher:$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o mydispatcher

clean:
	rm -f *o mydispatcher;
