/*    
CSC521 Operating system
Project:      2 mydispatcher
Programmer:   Rob Miles
Professor:    Dr. Lee
File Created: Oct 15, 2018
File Updated: Oct 15, 2018
*/


#include "mydispatcher.h"

int roundRobin(unsigned short int sliceSizeIn){
	
    unsigned short activeProcess = 0;             //which process is "executing"
    int activeProcessesExist = 1;                      //assume at least one live process at init
    unsigned short queuePos = 0;                  //keeps track of the last process queued, ready to "execute"
    unsigned short slicePosition = 1;             //how far through the time slice we are
    unsigned short sliceSize = sliceSizeIn;
	int tP = 1500; 
	int expiredCounter = 0;
	
    /*update new processes to queue for each timestep*/
    while (activeProcessesExist) {                    //check processes left that aren't finished
        unsigned short int index = 0;                 //start evaluation of processes at row 1
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
        queue[activeProcess]->totExeTime ++;           //increment the time it has run /////// redundant
        if ((queue[activeProcess]->remExeTime --) == 0){//decreast time remaining and see if it's 0
            queue[activeProcess]->complete = 1;        //if so, mark as complete
            activeProcess++;                           //move to next process in queue
			activeProcess = activeProcess % tP;
			slicePosition = 1-1;
			expiredCounter++;
            
            
            if (!queue[activeProcess]){                //if no more in queue
                activeProcessesExist = 0;              //turn off flag
                activeProcess = 0;
                while(queue[activeProcess]->pid){     //if you've just arrived at a completed process in the queue
                    if (queue[activeProcess]->complete == 0){
                        activeProcessesExist = 1;      //check if there's still incomplete processes in queue
                    }
                    activeProcess ++;                          //skip to a live process
                }
				
            }
        }
        
        /*process the queue/currently "executing" process*/
        if (slicePosition == sliceSize){
            activeProcess++;
            if(!queue[activeProcess]){
                activeProcess = 0;
            }
            slicePosition = 1;
        } else {
            slicePosition ++;
        }
        
        while(queue[activeProcess]->complete == 1){     //if you've just arrived at a completed process in the queue
            activeProcess ++;                          //skip to a live process
        }
        
        if (activeProcessesExist == 0){                //if all processes are complete
            return 0;                                  // finish successfully
        } else {
			printf("time:%6ld   Q[i]:%6d   PID:%6d   ", globalTimeTicker, activeProcess, queue[activeProcess]->pid);
			printf("remains:%4d   sliceloc:%4d\n", queue[activeProcess]->remExeTime, slicePosition);
            globalTimeTicker ++;                       //otherwise, there's more work to do, go to next time step
        }
        
		if (expiredCounter > tP){
			break;
		}

    }
    
    return 0;
}
