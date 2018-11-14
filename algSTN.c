/*    
 CSC521 Operating system
 Project:      2 mydispatcher
 Programmer:   Rob Miles
 Professor:    Dr. Lee
 File Created: Oct 15, 2018
 File Updated: Nov 11, 2018
 */
#include <stdlib.h>

#include "mydispatcher.h"



int shortestProcessNext(struct Process *inProc){

    int expiredCounter = 0;                            //number of completed processes
    struct Process *queueList;                         //dispatcher queue
    queueList = NULL;                                  //initialized to nothing, gets first process later
    struct Process *activeProcess;                     //which process is "executing"
    activeProcess = queueList;                         //will keep track of the executing process
    struct Process *previousProcess;                   //holds last process for when we need to remove a process
    previousProcess = NULL;                            //it starts as null
    struct Process *tmpProcess;                        //used for handoff of last process
	tmpProcess = (struct Process*) malloc(sizeof(struct Process));
	tmpProcess->pid = 0;                               //start with NULL, assign later
	tmpProcess->arrivalTime = 0;
	tmpProcess->exeTime = 65534;
	tmpProcess->remExeTime = 65534;                 //set the remaining counter to service time
	tmpProcess->exeStartTime = 0;
	tmpProcess->exeDoneTime = 0;
	tmpProcess->turnaroundTime = 0;
	tmpProcess->waitTime = 0;                            //init to no wait
	tmpProcess->complete = 0;                            //init to incomplete
	tmpProcess->next = NULL;                             //make this the last link
	tmpProcess->Qnext = NULL;                            //make this the last link
	tmpProcess->Qprev = NULL;

    struct Process *processIterator;                   //iterator for process selection
    processIterator = NULL;                            //start with NULL, assign later
	void qprint(){

		if (activeProcess->Qprev)
			printf("prev%d", activeProcess->Qprev->pid);
		else
			printf("HEAD");
		if (activeProcess->pid)
			printf(" pid_%d ", activeProcess->pid);
		else
			printf(" _ ");
		if (activeProcess->Qnext)
			printf("next%d \n", activeProcess->Qnext->pid);
		else
			printf("NULL \n");
	}
    while (1) {                                       //check processes left that aren't finished
        unsigned short sizeComp;                      //for process selection
        struct Process *ipIndex = inProc;              //iterator for queue management, reset to head each loop
        while (ipIndex != NULL){                       //iterate input data
            if (!ipIndex->complete){                    //check if the process is live
                if (ipIndex->arrivalTime == globalTimeTicker){  //check if it's new to the queue
                    appendQ(&queueList, &ipIndex);     //append
                }
            }
            ipIndex = ipIndex->next;                   //go to next item in list
        }
		
        if(activeProcess == NULL && queueList != NULL)                      //if this is the first iteration
            activeProcess = queueList;                 //set the working process to the head of the list
		
        if (activeProcess && !activeProcess->exeStartTime){             //if this process just began to execute
            activeProcess->exeStartTime = globalTimeTicker;  //record the start time
		}
		
		
		if (activeProcess && activeProcess->remExeTime == 0){           //see if reminaing time is 0
			//printf("testpoint2\n");
			if (!activeProcess->complete)               //catch when stalled on empty queue
				expiredCounter++;                      //increase tally for complete processes
			activeProcess->complete = 1;               //if so, mark as complete
			activeProcess->exeDoneTime = globalTimeTicker;

			if (expiredCounter == TOTAL_ROWS){         //if no more in queue
				return 0;
			}
			//qprint();

			if (activeProcess->Qnext == NULL){         //if at end of queue

				if (!activeProcess->Qprev){            //if nothing in que before or after, set que to null
					//printf("warning\n");
					tmpProcess->remExeTime = 65534;
					activeProcess = tmpProcess;
					queueList = NULL;
				}
				else {
					//printf("listend\n");
					activeProcess = activeProcess->Qprev;
					activeProcess->Qnext = NULL;         //drop the expired process
					//activeProcess = queueList;              //go back to start of queue
				}

			}
			else{

				if (activeProcess->Qprev){                  //if there is a previous process
					
					//printf("activeProcess%d\n", activeProcess->Qprev->Qnext->pid);
					activeProcess->Qprev->Qnext = activeProcess->Qnext;//link to jump over active (expired)
					
					activeProcess->Qnext->Qprev = activeProcess->Qprev; //new
					activeProcess->Qnext = NULL;//new
					activeProcess->Qprev = NULL;//new
					//activeProcess = queueList;//new
					
				}
				else{

					queueList = activeProcess->Qnext;  //otherwise, drop the first process, link head to next
					activeProcess->Qnext->Qprev = NULL; //set Qprev to NULL aka HEAD

				}

				activeProcess = activeProcess->Qnext;  //move to the next process
				//tmpProcess->remExeTime = 65534;
				//activeProcess = tmpProcess;
				
			}
			
			
			//if (activeProcess)
			//	qprint(); 
			
			sizeComp = 65535;                         //set large number to compare shorter processes to
			processIterator = queueList;               //set iterator to head of queue
			if (queueList == NULL){
				//printf("testpoint\n");
				activeProcess = NULL;
			}
			
            while (processIterator != NULL){          //loop through queue list
				
				if (processIterator->remExeTime < sizeComp){  //if process remaining is less than compare num
					activeProcess = processIterator;   //set active process to the iterator value
                    sizeComp = processIterator->remExeTime;  //set new comparison value
                    previousProcess = tmpProcess;      //previous process = temp
					//printf("activeProcess%d\n", activeProcess->pid);
					//scanf("%d", &expiredCounter);
                }else{
                    sizeComp = 65535;
                }
                //tmpProcess = processIterator;          //store current iterator as "last" for next iteration
                processIterator = processIterator->Qnext;  //set iterator to next in queue
            }
        }
		if (activeProcess){
            activeProcess->remExeTime --;              //EXECUTE - decreast time remaining
			//printf("time:%6ld   PID:%6d   AT:%4d  ", globalTimeTicker, activeProcess->pid, activeProcess->arrivalTime);
			//printf("remains:%4d   size:%4d   ", activeProcess->remExeTime, activeProcess->exeTime);
			//printf("%d == %d \n", expiredCounter, TOTAL_ROWS);
		}
		globalTimeTicker++;                       //otherwise, there's more work to do, go to next time step
    }
    return 0;
}

