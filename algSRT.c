/*    
 CSC521 Operating system
 Project:      2 mydispatcher
 Programmer:   Rob Miles
 Professor:    Dr. Lee
 File Created: Oct 15, 2018
 File Updated: Nov 13, 2018
 */

#include "mydispatcher.h"

int shortestRemainingTime(struct Process *inProc){

	int expiredCounter = 0;                            //number of completed processes
	struct Process *queueList;                         //dispatcher queue
	queueList = NULL;                                  //initialized to nothing, gets first process later
	struct Process *activeProcess;                     //which process is "executing"
	activeProcess = queueList;                         //will keep track of the executing process
	struct Process *processIterator;                   //iterator for process selection
	processIterator = NULL;                            //start with NULL, assign later
    struct Process *nextProcess;                       //holds last process for when we need to remove a process
    nextProcess = NULL;                                //it starts as null
	unsigned short sizeComp;                          //for process selection
    char flag = 0;                                     //incidcates if condtender is smaller

	while (1) {                                               //check processes left that aren't finished
		
		struct Process *ipIndex = inProc;                     //iterator for queue management, reset to head each loop
		while (ipIndex != NULL){                              //iterate input data
			if (!ipIndex->complete){                          //check if the process is live
				if (ipIndex->arrivalTime == globalTimeTicker){//check if it's new to the queue
					appendQ(&queueList, &ipIndex);            //append
					if(activeProcess){                        
						if (ipIndex->exeTime < activeProcess->exeTime){//if new process is smaller than activeprocess
							sizeComp = ipIndex->exeTime;      //set size comparison variable
							nextProcess = ipIndex;          //switch to it
                            flag = 1;
                            printf("aP %d, ", activeProcess->pid);
                            printf("testpoint\n");

						}
					}
				
				}
			}
			ipIndex = ipIndex->next;                          //iterate loop
		}

		if (activeProcess == NULL && queueList != NULL)       //if this is the first iteration
			activeProcess = queueList;                        //set the working process to the head of the list

		if (activeProcess && !activeProcess->exeStartTime){   //if this process just began to execute
			activeProcess->exeStartTime = globalTimeTicker;   //record the start time
		}
        //print queue for troublehsooting
         struct Process *tmpQ = queueList;
         while(tmpQ){
             printf("%d-%d ", tmpQ->pid, tmpQ->remExeTime);
         tmpQ = tmpQ->Qnext;
         }
         printf("__");
        if (activeProcess && activeProcess->remExeTime == 0){ //if active process reminaing time is 0
			if (!activeProcess->complete)                     //catch when stalled on empty queue
				expiredCounter++;                             //increase tally for complete processes
			activeProcess->complete = 1;                      //if so, mark as complete
			activeProcess->exeDoneTime = globalTimeTicker;

			if (expiredCounter == TOTAL_ROWS){                //if no more in queue end the algorithm!
				return 0;
			}

			if (activeProcess->Qnext == NULL){                //if at end of queue
				if (!activeProcess->Qprev){                   //if nothing in que before or after, set que to null
					queueList = NULL;
				}
				else {
					activeProcess = activeProcess->Qprev;     //move to next process
					sizeComp = activeProcess->remExeTime;     //set size comparison variable to current process remaining
					activeProcess->Qnext = NULL;              //drop the expired process
				}
			}
			else {
                //nextProcess = activeProcess->Qnext;
				if (activeProcess->Qprev){                              //if there is a previous process
					activeProcess->Qprev->Qnext = activeProcess->Qnext; //link to jump over active (expired)
					activeProcess->Qnext->Qprev = activeProcess->Qprev; //link to jump reverse over expired
					activeProcess->Qnext = NULL;                        //housekeeping expired links
					activeProcess->Qprev = NULL;                        //housekeeping expired links
				}
				else {
                    
					queueList = activeProcess->Qnext;         //otherwise, drop the first process, link head to next
					activeProcess->Qnext->Qprev = NULL;       //set Qprev to NULL aka HEAD
				}
				//activeProcess = nextProcess;                  //move to the next process

            }

			sizeComp = 65535;                                 //set large number to compare shorter processes to
			processIterator = queueList;                      //set iterator to head of queue
			if (queueList == NULL){                           //disable active process if nothing in queue
				activeProcess = NULL;
			}
			while (processIterator != NULL){                  //loop through queue list
				if (processIterator->remExeTime < sizeComp
                    && processIterator->remExeTime != 0){  //if process remaining is less than compare num
					activeProcess = processIterator;          //set active process to the iterator value
					sizeComp = processIterator->remExeTime;   //set new comparison value
				}

				processIterator = processIterator->Qnext;     //set iterator to next in queue
			}

		}
        if(flag){
            activeProcess = nextProcess;
            flag = 0;
        }
		if (activeProcess){
			if (activeProcess->remExeTime>0){                 //keep old processes where they are timing wise
				activeProcess->remExeTime--;                  //EXECUTE - decreast time remaining
			}
			printf("time:%6ld   PID:%6d   AT:%4d  ", globalTimeTicker, activeProcess->pid, activeProcess->arrivalTime);
			printf("remains:%4d   size:%4d   ", activeProcess->remExeTime, activeProcess->exeTime);
			printf("%d == %d \n", expiredCounter, TOTAL_ROWS);
		}
		globalTimeTicker++;                                   //there's more work to do, increment timer
	}
	return 0;
}




