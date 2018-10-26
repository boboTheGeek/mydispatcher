/*    
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Oct 15, 2018
*/
#include <stdio.h>
#include "mydispatcher.h"

int firstComeFirstServe(){
	
	unsigned short int index = 0;
	
	while (processes[index].pid){
		if (processes[index].arrivalTime == globalTimeTicker){
			struct Process *ptr = &processes[index];
			queue[queuePos] = ptr;
			queue[queuePos]->exeStartTime = globalTimeTicker;
			printf("%d\n", processes[index].remExeTime);
			queue[queuePos]->remExeTime--;
			printf("process_%d; at_%d; et_%d\n", processes[index].pid, processes[index].remExeTime, processes[index].exeStartTime);
			queuePos++;
		}
		index++;
	}


	printf("fcfs\n");
    return 0;                 //return successfully
}
