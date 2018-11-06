/*    
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Oct 15, 2018
*/


#include "mydispatcher.h"

int shortestTimeNext(int tPin){

	unsigned short activeProcess = 0;             //which process is "executing"
	int activeProcessesExist = 1;                      //assume at least one live process at init
	unsigned short queuePos = 0;                  //keeps track of the last process queued, ready to "execute"

	int tP = tPin;
	unsigned short expiredCounter = 0;
	int i = 0;

	/*update new processes to queue for each timestep*/
	while (activeProcessesExist) {                    //check processes left that aren't finished
		
		unsigned short sizeComp = 65535;
		
		unsigned short index = 0;                 //start evaluation of processes at row 1
		while (processes[index].pid){                  //iterate input data
			struct Process *ptr = &processes[index];   //assign pointer to the struct
			if (!ptr->complete){                       //check if the process is live
				activeProcessesExist = 1;              //any live processes sets flag
				if (ptr->arrivalTime == globalTimeTicker){  //check if it's new to the queue
					queue[queuePos] = ptr;             //add to queue if just arrived
					queuePos++;                        //move to next free space in array
				}
			}
			index++;                                   //increment to next struct in array
		}

		if (!queue[activeProcess]->exeStartTime)       //if this process just began to execute
			queue[activeProcess]->exeStartTime = globalTimeTicker;  //record the start time
		queue[activeProcess]->totExeTime++;           //increment the time it has run /////// redundant
		
		if ((queue[activeProcess]->remExeTime--) == 0){//decreast time remaining and see if it's 0
			queue[activeProcess]->complete = 1;        //if so, mark as complete
			expiredCounter++;
			
				for (i = 0; i < queuePos; i++){              //scan for next shortest process in queue
					if ((queue[i]->remExeTime < sizeComp) && (!queue[i]->complete)){
						activeProcess = i;
						sizeComp = queue[i]->remExeTime;
						printf("sizeComp = %d pid%d\n", sizeComp, queue[i]->pid);
					}
				}
			}
		
		if (activeProcessesExist == 0){                //if all processes are complete
			return 0;                                  // finish successfully
		}
		else {
			printf("time:%6ld   Q[i]:%6d   PID:%6d   ", globalTimeTicker, activeProcess, queue[activeProcess]->pid);
			printf("remains:%4d\n", queue[activeProcess]->remExeTime);
			globalTimeTicker++;                       //otherwise, there's more work to do, go to next time step
		}

		if (expiredCounter > tP){
			break;
		}

	}

	return 0;
}
