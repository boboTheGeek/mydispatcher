/*    
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Nov 7, 2018
File Updated: Nov 7, 2018
*/

#include "mydispatcher.h"

void processStatistics(struct Process *node){
    FILE * fp;
    /* open the file for writing*/
    fp = fopen("output.dat", "w");
    
    float avgturnaround = 0;
	float avgnormalizedTurnaround = 0;
	float avgwaiting = 0;
	
    while (node != NULL)
    {
        /*
        printf("P %d   ", node->pid);
        printf("A %d   ", node->arrivalTime);
        printf("S %d   ", node->exeTime);
        printf("R %d   ", node->remExeTime);
        printf("C %d   ", node->complete);
        printf("D %d\n ", node->exeDoneTime);
        */
		node->turnaroundTime = node->exeDoneTime - node->arrivalTime;
		node->waitTime = node->turnaroundTime - node->exeTime;
		avgturnaround += node->turnaroundTime;
		avgwaiting += node->waitTime;
		avgnormalizedTurnaround += (float)(node->turnaroundTime / node->exeTime);
        
        fprintf(fp, "%5d runs %d-%d: A=%d, S=%d, W=%d, F=%d, T=%d\n", \
                node->pid, \
                node->arrivalTime, \
                node->exeDoneTime, \
                node->arrivalTime, \
                node->exeTime, \
                node->waitTime, \
                node->exeDoneTime, \
                node->turnaroundTime);
        
        node = node->next;

	}
	avgturnaround = (float)avgturnaround / TOTAL_ROWS;
	avgwaiting = (float)avgwaiting / TOTAL_ROWS;
	avgnormalizedTurnaround = (float) avgnormalizedTurnaround / TOTAL_ROWS;
	printf("\n\nAverage turnaround time = %0.4f \n", avgturnaround);
	printf("Average normalized turnaround time = %0.4f \n", avgnormalizedTurnaround);
	printf("Average waiting time = %0.4f \n", avgwaiting);
    
    fclose(fp);
}
