/*    
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Nov 3, 2018
*/

#include <string.h>
#include <time.h>

#include "mydispatcher.h"

unsigned long globalTimeTicker = 0;

void printArray(){
    printf("index: pid: arrivalTime: ");
    printf("exeTime: remExeTime: exeDoneTime  turnaroundTime\n");
	for (int i = 0; i < TOTAL_ROWS; i++){
        printf("%5d %5d %7d ", i, processes[i].pid, processes[i].arrivalTime);
        printf("%10d %10d %10d %10d\n",processes[i].exeTime, processes[i].remExeTime, processes[i].exeDoneTime, processes[i].turnaroundTime);

    }
}

void writeToFile(){
	FILE * fp;
	/* open the file for writing*/
	fp = fopen("output.dat", "w");
	for (int i = 0; i < TOTAL_ROWS; i++){
		fprintf(fp, "%5d runs %d-%d: A=%d, S=%d, W=%d, F=%d, T=%d\n", \
			processes[i].pid, processes[i].arrivalTime, processes[i].exeDoneTime, \
			processes[i].arrivalTime, processes[i].exeTime, processes[i].waitTime, \
			processes[i].exeDoneTime, processes[i].turnaroundTime);
	}

	fclose(fp);
}

int main(int argc, char *argv[]){
	FILE *fp;                                          //pointer for a file
	int arrivalTime_in, exeTime_in, pid = 1;           //
	 
    clock_t start, end;                                //setup for execution timer
    double cpu_time_used;                              //
    start = clock();                                   //

	if (!(fp = fopen(argv[1], "rb"))){
		perror("sorry, .dat file import problem\n");
		printf("provide the .dat file as first argument, should be in the same folder as executible\n");
	}

	while (fscanf(fp, "%d %d", &arrivalTime_in, &exeTime_in) != EOF) { //grab col 1 and 2 from file if it's not the end
		processes[pid-1].pid = pid;                    //set struct pid to counter value
		processes[pid-1].arrivalTime = arrivalTime_in; //grab arrival time from first column in file
		processes[pid-1].exeTime = exeTime_in;         //grab service time from second column in file
		processes[pid-1].remExeTime = exeTime_in;      //set the remaining time counter to service time as well
		processes[pid-1].complete = 0;                 //initialize to incomplete
		processes[pid-1].exeDoneTime = 0;
		pid++;                                         //increase the counter index
	}
	
	if (argc != 3){                                    //if you don't have 2 input params
		printf("Input parameters should be input.dat and <ALGORITHM> to run.\n");
		return 1;                                     //end unsuccessfully
	}
	else if (strcmp(argv[2], "FCFS") == 0){           //check for and run FCFS algorithm request
        firstComeFirstServe(pid);
	}
	else if (strcmp(argv[2], "RR") == 0){             //check for and run RR algorithm request
		roundRobin(pid);
	}
	else if (strcmp(argv[2], "STN") == 0){            //check for and run STN algorithm request
        shortestTimeNext(pid);
    }
	else if (strcmp(argv[2], "SRT") == 0){            //check for and run SRT algorithm request
        shortestRemainingTime(pid);
	}
	else{                                              //if the input parameter string wasn't found, warn and remind what is OK
		printf("Make sure you're <ALGORITHM> parameter is one of the following [in all caps]:\n");
		printf("FCFS, RR, STN, SRT\n");
		return 1;                                     //end unsuccessfully
	}
    
	processStatistics();
	writeToFile();
	//printArray();

    end = clock();                                     //finish clock and print exectution timer
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  //
    printf("programExecutionTime: %f\n", cpu_time_used);      //
    
	return 0;                                          //finish successfully
}




