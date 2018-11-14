/*    
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Nov 8, 2018
*/

#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "mydispatcher.h"

unsigned long globalTimeTicker = 0;

                                                       //reference (pointer to pointer) to the head
                                                       //params are data from input.dat
void append(struct Process** head_ref, int arrivalTime_in, int exeTime_in, int pid_in){
                                                       // allocate node
    struct Process* new_node = (struct Process*) malloc(sizeof(struct Process));
    struct Process *last = *head_ref;   /* used in step 5*/
    
    new_node->pid = pid_in;
    new_node->arrivalTime = arrivalTime_in;
    new_node->exeTime = exeTime_in;
    new_node->remExeTime = exeTime_in;                 //set the remaining counter to service time
    new_node->exeStartTime = 0;
    new_node->exeDoneTime = 0;
    new_node->turnaroundTime = 0;
    new_node->waitTime = 0;                            //init to no wait
    new_node->complete = 0;                            //init to incomplete
    new_node->next = NULL;                             //make this the last link
    new_node->Qnext = NULL;                            //make this the last link
	new_node->Qprev = NULL;                            //make this the last link

    if (*head_ref == NULL){                            //If the Linked List is empty,
        *head_ref = new_node;                          //then make the new node as head
        return;
    }
    
    while (last->next != NULL)                        //loop till the last node
        last = last->next;
    
    last->next = new_node;                             //change the next of last node
    return;
}

int main(int argc, char *argv[]){
	FILE *fp;                                          //pointer for a file
	int arrivalTime_in, exeTime_in, pid;               //init vars for later
    struct Process *inputProcesses;                    //init linked list of input processes
    inputProcesses = NULL;                             //and set it to null for now
    
    clock_t start, end;                                //setup for execution timer - not part of main project
    double cpu_time_used;                             //init timer var  - not part of main project
    start = clock();                                   //start clock - not part of main project

	if (!(fp = fopen(argv[1], "rb"))){                //open the input file for reading
		printf("provide the .dat file as first argument, should be in the same folder as executible\n"); //complain if it didn't work
	}
    
    pid = 1;
    while (fscanf(fp, "%d %d", &arrivalTime_in, &exeTime_in) != EOF) { //grab col 1 and 2 from file if it's not the end
        append(&inputProcesses, arrivalTime_in, exeTime_in, pid);  //add row as process item to linked list
        pid++;                                         //increase pid counter for next process
    }
    
	
	if (argc != 3){                                    //if you don't have 2 input params
		printf("Input parameters should be input.dat and <ALGORITHM> to run.\n");
		return 1;                                     //end unsuccessfully
	} else if (strcmp(argv[2], "FCFS") == 0){           //check for and run FCFS algorithm request
        firstComeFirstServe(inputProcesses);
	} else if (strcmp(argv[2], "RR") == 0){             //check for and run RR algorithm request
		roundRobin(inputProcesses);
	} else if (strcmp(argv[2], "SPN") == 0){            //check for and run STN algorithm request
        shortestProcessNext(inputProcesses);
    } else if (strcmp(argv[2], "SRT") == 0){            //check for and run SRT algorithm request
        shortestRemainingTime(inputProcesses);
	} else {                                              //if the input parameter string wasn't found, warn and remind what is OK
		printf("Make sure you're <ALGORITHM> parameter is one of the following [in all caps]:\n");
		printf("FCFS, RR, SPN, SRT\n");
		return 1;                                     //end unsuccessfully
	}
    
	processStatistics(inputProcesses);

    
    
    
    
    
    end = clock();                                     //finish clock and print exectution timer
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  //
    printf("programExecutionTime: %f\n", cpu_time_used);      //
    
	return 0;                                          //finish successfully
}




