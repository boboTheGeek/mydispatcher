/*    
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Nov 7, 2018
File Updated: Nov 7, 2018
*/

#include "mydispatcher.h"

void processStatistics(){
	float avgturnaround = 0;
	float avgnormalizedTurnaround = 0;
	float avgwaiting = 0;
	
	for (int i = 0; i < TOTAL_ROWS; i++){
		processes[i].turnaroundTime = processes[i].exeDoneTime - processes[i].arrivalTime;
		processes[i].waitTime = processes[i].turnaroundTime - processes[i].exeTime;
		avgturnaround += processes[i].turnaroundTime;
		avgwaiting += processes[i].waitTime;
		avgnormalizedTurnaround += (float)(processes[i].turnaroundTime / processes[i].exeTime);
	}
	avgturnaround = (float)avgturnaround / TOTAL_ROWS;
	avgwaiting = (float)avgwaiting / TOTAL_ROWS;
	avgnormalizedTurnaround = (float) avgnormalizedTurnaround / TOTAL_ROWS;
	printf("Average turnaround time = %0.4f \n", avgturnaround);
	printf("Average normalized turnaround time = %0.4f \n", avgnormalizedTurnaround);
	printf("Average waiting time = %0.4f \n", avgwaiting);
}