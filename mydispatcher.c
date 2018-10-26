/*    
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Oct 15, 2018
*/

#include <stdio.h>
#include<string.h>
#include <time.h>

#include "mydispatcher.h"

int globalTimeTicker = 0;  
unsigned short int queuePos = 0;       //keeps track of the last process queued, ready to "execute"
unsigned short int activeProcess = 0;  //keeps track of which process is "executing"


int main(int argc, char *argv[]){
	FILE *fp;
	int arrivalTime_in, exeTime_in, pid = 1;
	 
     
    clock_t start, end;
    double cpu_time_used;
    start = clock();

	char testmode = 0;

	if (strcmp(argv[1], "-t")==0) {
		testmode = 1;
		if (!(fp = fopen("test.dat", "rb"))){
			perror("test .dat open filed\n");
		}
		printf("Struct \nindex: pid: arrivalTime: ");
		printf("exeTime: totExeTime: remExeTime: exeStartTime\n");
		argv[2] = "FCFS";
		argc = 3;
	}
	else {
		if (!(fp = fopen(argv[1], "rb"))){
			perror("sorry, .dat file import problem\n");
			printf("provide the .dat file as first argument, should be in the same folder as executible\n");
		}
	}

	while (fscanf(fp, "%d %d", &arrivalTime_in, &exeTime_in) != EOF) {
		//printf("            p: %d            aT: %d         eT: %d\n", pid, arrivalTime_in, exeTime_in);
		processes[pid-1].pid = pid;
		processes[pid-1].arrivalTime = arrivalTime_in;
		processes[pid-1].exeTime = exeTime_in;
		processes[pid-1].totExeTime = 0;
		processes[pid-1].remExeTime = exeTime_in;
		processes[pid-1].complete = 0;     //initialize to invalid number for additional info
		if(testmode == 1){
			printf("%5d %5d %7d ", pid-1, processes[pid-1].pid, processes[pid-1].arrivalTime);
			printf("%10d %10d %10d %10d\n",processes[pid-1].exeTime, processes[pid-1].totExeTime, processes[pid-1].remExeTime, processes[pid-1].exeStartTime);
		}
		pid++;
	}
	
	if (argc != 3){                          //if you don't have 2 input params
		printf("Input parameters should be input.dat and <ALGORITHM> to run.\n");
		return 1;                            //end unsuccessfully
	}
	else if (strcmp(argv[2], "FCFS") == 0){  //check for and run FCFS algorithm request
		firstComeFirstServe();
	}
	else if (strcmp(argv[2], "RR") == 0){    //check for and run RR algorithm request
		roundRobin();
	}
	else if (strcmp(argv[2], "STN") == 0){   //check for and run STN algorithm request
		shortestTimeNext();
	}
	else if (strcmp(argv[2], "SRT") == 0){   //check for and run SRT algorithm request
		shortestRemainingTime();
	}
	else{                                    //if the input parameter string wasn't found, warn and remind what is OK
		printf("Make sure you're <ALGORITHM> parameter is one of the following [in all caps]:\n");
		printf("FCFS, RR, STN, SRT\n");
		return 1;                            //end unsuccessfully
	}


    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("programExecutionTime: %f", cpu_time_used);
    return 0;                                //finish successfully
}




