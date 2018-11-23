/*    
 CSC521 Operating system
 Project:      2 mydispatcher
 Programmer:   Rob Miles
 Professor:    Dr. Lee
 File Created: Oct 15, 2018
 File Updated: Oct 15, 2018
 */

#include "mydispatcher.h"

int roundRobin(struct Process *inProc){
    
    unsigned short slicePosition = 0;                 //how far through the time slice we are
    unsigned short sliceSize = 4;                     //default quantum size
    //unsigned short sliceIn = 1;                      //init quantum input size
    int expiredCounter = 0;                            //number of completed processes
  
    struct Process *queueList;                         //dispatcher queue
    queueList = NULL;                                  //initialized to nothing, gets first process later
    struct Process *activeProcess;                     //which process is "executing"
    activeProcess = queueList;                         //will keep track of the executing process
    struct Process *nextProcess;                       //holds last process for when we need to remove a process
    nextProcess = NULL;                                //it starts as null
    
    while (1) {
        
        struct Process *ipIndex;
        ipIndex = inProc;                              //iterator for queue management, reset to head each loop
        while (ipIndex != NULL){                      //iterate input data
            if (!ipIndex->complete){                   //check if the process is live
                if (ipIndex->arrivalTime == globalTimeTicker){  //check if it's new to the queue
                    appendQ(&queueList, &ipIndex);     //append
                }
            }
            ipIndex = ipIndex->next;                   //go to next item in list
        }
        /*print queue for troublehsooting
        struct Process *tmpQ = queueList;
        while(tmpQ){
            printf("%d, ", tmpQ->pid);
            tmpQ = tmpQ->Qnext;
        }
        printf("\n");*/
		if (activeProcess == NULL && queueList != NULL) //if this is the first iteration
            activeProcess = queueList;                  //set the working process to the head of the list

		if (activeProcess && !activeProcess->exeStartTime){  //if this process just began to execute
            activeProcess->exeStartTime = globalTimeTicker;  //record the start time
        }

		if (activeProcess->remExeTime == 0){            //see if reminaing time is 0
            if(!activeProcess->complete)                //catch when stalled on empty queue
                expiredCounter++;                       //increase tally for complete processes
            activeProcess->complete = 1;                //if so, mark as complete
            activeProcess->exeDoneTime = globalTimeTicker; //capture when it finishes
            slicePosition = 1;                          //reset quantum counter

            if (expiredCounter == TOTAL_ROWS){          //if no more in queue
                return 0;
            }
			
            if (activeProcess->Qnext == NULL){          //if at end of queue
                activeProcess->Qprev->Qnext = NULL;     //drop the expired process ?????
					activeProcess = queueList;          //loop to beginning
					if (queueList == NULL){             //if queue list is empty
						activeProcess = NULL;           //set active process to NULL
					}
            } else {
                nextProcess = activeProcess->Qnext;
				
                if (activeProcess->Qprev){                              //if there is a previous process
					activeProcess->Qprev->Qnext = activeProcess->Qnext; //link to jump over active (expired)
					activeProcess->Qnext->Qprev = activeProcess->Qprev; //link to jump reverse over expired
					activeProcess->Qnext = NULL;                        //housekeeping expired links
					activeProcess->Qprev = NULL;                        //housekeeping expired links
				} else {
					queueList = activeProcess->Qnext;  //otherwise, drop the first process, link head to next
					activeProcess->Qnext->Qprev = NULL;//set Qprev to NULL aka HEAD
				}
				activeProcess = nextProcess;  //move to the next process
			            
            }

        } else if (slicePosition == sliceSize){        //check if quantum is up

            if (activeProcess->Qnext == NULL){         //if there is no process there
                activeProcess = queueList;             //go back to start of queue
            
            } else {
                queueList->Qnext->Qprev = NULL;        //prep 2nd node to be first
                queueList = queueList->Qnext;          //make 2nd node first
                struct Process *i = queueList;         //temp iterator
                while(i->Qnext){                       //go to end of queue
                    i = i->Qnext;
                }
                i->Qnext = activeProcess;              //add active process to end of queue
                activeProcess->Qprev = i;              //set it's reverse link
                activeProcess->Qnext = NULL;           //make it the end
                activeProcess = queueList;             //move active process to start of queue
            }
            slicePosition = 1;                         //reset quantum position
        
        } else {
            slicePosition ++;                          //increment quantum position
        }
		         
		if (activeProcess){
			if (activeProcess->remExeTime > 0){        //if process is still live
				activeProcess->remExeTime--;           //EXECUTE - decreast time remaining
				
				//printf("time:%6ld   PID:%6d   AT:%4d  ", globalTimeTicker, activeProcess->pid, activeProcess->arrivalTime);
				//printf("remains:%4d   sliceloc:%4d   ", activeProcess->remExeTime, slicePosition);
				//printf("%d == %d \n", expiredCounter, TOTAL_ROWS);
			}
		}
		globalTimeTicker++;                              //otherwise, there's more work to do, go to next time step
    }
    return 0;
}
