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
	
	unsigned short int index = 0;  //start evaluation of processes at row 1
	
	while (processes[index].pid){
		struct Process *ptr = &processes[index];
		if (ptr->complete != 1){
			if (ptr->arrivalTime == globalTimeTicker){
				//struct Process *ptr = &processes[index];
				queue[queuePos] = ptr;
				queue[queuePos]->exeStartTime = globalTimeTicker;
				printf("%d\n", processes[index].remExeTime);
				//queue[queuePos]->remExeTime--;  needs to happen if I'm executing
				printf("process_%d; at_%d; et_%d\n", processes[index].pid, processes[index].remExeTime, processes[index].exeStartTime);
				queuePos++;
			}
			index++;
		}
	}

    return 0;                 //return successfully
}
