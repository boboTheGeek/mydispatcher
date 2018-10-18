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

#include "mydispatcher.h"

int main(int argc, char *argv[]){
	FILE *fp;
	int arrivalTime, executionTime, pid = 1;
	
	if (!(fp = fopen(argv[1], "rb"))){
		perror("sorry, .dat file import problem\n");
	}
	
	while (fscanf(fp, "%d %d", &arrivalTime, &executionTime) != EOF) {
		printf("%d %d %d\n", pid, arrivalTime, executionTime );
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
    return 0;                                //finish successfully
}




