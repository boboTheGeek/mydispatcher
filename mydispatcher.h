/*
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Nov 3, 2018
*/
#include <stdio.h>

#define TOTAL_ROWS 10000

unsigned long globalTimeTicker;                       //a ticker that will keep track of schedule position
unsigned short int queuePos;
unsigned short int activeProcess;

struct Process {
	unsigned short pid;
	unsigned short arrivalTime;
	unsigned short exeTime;
	unsigned short remExeTime;
	unsigned short exeStartTime;
	char complete;
};

struct Process processes[TOTAL_ROWS];                  //a list of the process structs
struct Process *queue[TOTAL_ROWS];                     //set the queue to the same size as number of rows, but could be more efficient

int firstComeFirstServe();
int roundRobin();
int shortestTimeNext();
int shortestRemainingTime();
