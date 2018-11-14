/*
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Nov 3, 2018
*/
#include <stdio.h>
#define TOTAL_ROWS 1500                          //total number of process rows
unsigned long globalTimeTicker;                       //a ticker that will keep track of schedule position

struct Process {
	unsigned short pid;                               //process ID
	unsigned short arrivalTime;                       //process arrival time to queue
	unsigned short exeTime;                           //service time length
	unsigned short remExeTime;                        //amount of remaining cycles to be done
	unsigned short exeStartTime;                      //when process began to be active
	unsigned short exeDoneTime;                       //process finished time
	unsigned short turnaroundTime;                    //turnaround
	unsigned short waitTime;                          //wait time
	char complete;                                     //if completed processing
    struct Process *next;                              //linked list ref for input of all processes
    struct Process *Qnext;                             //linked list ref for process queue
	struct Process *Qprev;                             //linked list ref for process queue
};

int firstComeFirstServe(struct Process *);
int roundRobin(struct Process *);
int shortestProcessNext(struct Process *);
int shortestRemainingTime(struct Process *);
void processStatistics();
void appendQ(struct Process**, struct Process **);
