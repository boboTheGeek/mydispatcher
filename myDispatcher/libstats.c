/*    
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Nov 7, 2018
File Updated: Nov 12, 2018
*/

#include "mydispatcher.h"

void processStatistics(struct Process *node){
    FILE * fp;                                         //create file for output.dat
    FILE * fpsup;                                      //create file for supplimental data for documentation
    
    fp = fopen("output.dat", "w");                   // open the file for writing
    fpsup = fopen("processes.csv", "w");             // open the file for writing
    
    float avgturnaround = 0;                           //init some variables
	float avgnormalizedTurnaround = 0;
	float avgwaiting = 0;
                                                       //prepare headings for supplimental output file
    fprintf(fpsup, "pid, arrival, service, remaining, start, finish, turnaround, wait, normturnaround, complete\n");
    
    while (node != NULL){                             //loop through all elements of the process list

        node->turnaroundTime = node->exeDoneTime - node->arrivalTime;  //calculate turnaround time
        node->waitTime = node->turnaroundTime - node->exeTime;         //calculate wait time
        avgturnaround += node->turnaroundTime;         //add to tally for average turnaround
        avgwaiting += node->waitTime;                  //add to tally for average wait time
        avgnormalizedTurnaround += (float)(node->turnaroundTime / (float)node->exeTime); //add to tally for normalized turnaround time
        
                                                       //print items to output file
        fprintf(fp, "%5d runs %d-%d: A=%d, S=%d, W=%d, F=%d, T=%d\n", \
                node->pid, \
                node->arrivalTime, \
                node->exeDoneTime, \
                node->arrivalTime, \
                node->exeTime, \
                node->waitTime, \
                node->exeDoneTime, \
                node->turnaroundTime);
        fprintf(fpsup, "%d, %d, %d, %d, %d, %d, %d, %d, %0.2f, %d\n", \
                node->pid, \
                node->arrivalTime, \
                node->exeTime, \
                node->remExeTime, \
                node->exeStartTime, \
                node->exeDoneTime, \
                node->turnaroundTime, \
                node->waitTime, \
                (float)(node->turnaroundTime / (float)node->exeTime), \
                node->complete);
        
        node = node->next;                             //switch to next node for while loop
	}
	avgturnaround = (float)avgturnaround / (float)TOTAL_ROWS; //complete calcuation for average turnaround
	avgwaiting = (float)avgwaiting / (float)TOTAL_ROWS;       //complete calcuation for average waiting
	avgnormalizedTurnaround = (float) avgnormalizedTurnaround / (float)TOTAL_ROWS;       //complete calcuation for average normalized turnaround
	printf("\n\nAverage turnaround time = %0.4f \n", avgturnaround);          //print the averages for the user
	printf("Average normalized turnaround time = %0.4f \n", avgnormalizedTurnaround);
	printf("Average waiting time = %0.4f \n", avgwaiting);
    
    fclose(fp);                                        //close the files that we were writing to
    fclose(fpsup);
}
