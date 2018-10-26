/*
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Oct 15, 2018
*/

int globalTimeTicker;        //a ticker that will keep track of schedule position
#define TOTAL_ROWS 10000

struct Process {                   //move me later
	unsigned short int pid;
	unsigned short int arrivalTime;
	unsigned short int exeTime;
	unsigned short int totExeTime;
	unsigned short int remExeTime;
	unsigned short int exeStartTime;
};

struct Process processes[TOTAL_ROWS];  //a list of the process structs
struct Process *queue[TOTAL_ROWS];     //set the queue to the same size as number of rows, but could be more efficient
unsigned short int queuePos;

int firstComeFirstServe();
int roundRobin();
int shortestTimeNext();
int shortestRemainingTime();