/*
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Nov 3, 2018
*/
#include <stdio.h>
#define TOTAL_ROWS 1500
unsigned long globalTimeTicker;                       //a ticker that will keep track of schedule position

struct Process {
	unsigned short pid;
	unsigned short arrivalTime;
	unsigned short exeTime;
	unsigned short remExeTime;
	unsigned short exeStartTime;
	unsigned short exeDoneTime;
	unsigned short turnaroundTime;
	unsigned short waitTime;
	char complete;
    struct Process *next;
    struct Process *Qnext;
};

struct Process processes[TOTAL_ROWS];                  //a list of the process structs
                                                       //set the queue to the same size as number of rows, but could be more efficient

int firstComeFirstServe(struct Process *);
int roundRobin(unsigned short);
int shortestTimeNext(unsigned short);
int shortestRemainingTime(unsigned short);
void processStatistics();
void updateQ();
