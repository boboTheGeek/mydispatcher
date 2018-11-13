/*    
 CSC521 Operating system
 Project:      2 mydispatcher
 Programmer:   Rob Miles
 Professor:    Dr. Lee
 File Created: Oct 15, 2018
 File Updated: Nov 11, 2018
 */

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
    tmpProcess = NULL;                                 //start with NULL, assign later
    struct Process *processIterator;                   //iterator for process selection
    processIterator = NULL;                            //start with NULL, assign later
    
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
        
        if(activeProcess == NULL)                      //if this is the first iteration
            activeProcess = queueList;                 //set the working process to the head of the list
        
        if (!activeProcess->exeStartTime){             //if this process just began to execute
            activeProcess->exeStartTime = globalTimeTicker;  //record the start time
        }
        
        if (activeProcess->remExeTime == 0){           //see if reminaing time is 0
            if(!activeProcess->complete)               //catch when stalled on empty queue
                expiredCounter++;                      //increase tally for complete processes
            activeProcess->complete = 1;               //if so, mark as complete
            activeProcess->exeDoneTime = globalTimeTicker;
            
            if (expiredCounter == TOTAL_ROWS){         //if no more in queue
                printf("end\n");
                return 0;
            }
            
            if (activeProcess->Qnext == NULL){         //if at end of queue
                activeProcess = queueList;              //go back to start of queue
                previousProcess->Qnext = NULL;         //drop the expired process
            }else{
                if (previousProcess){                  //if there is a previous process
                    
                    previousProcess->Qnext = activeProcess->Qnext;//link to jump over active (expired)
                }else{
                    queueList = activeProcess->Qnext;  //otherwise, drop the first process, link head to next
                }
                activeProcess = activeProcess->Qnext;  //move to the next process
            }
            
            sizeComp = 65535;                         //set large number to compare shorter processes to
            processIterator = queueList;               //set iterator to head of queue
            while (processIterator != NULL){          //loop through queue list
                if (processIterator->remExeTime < sizeComp){  //if process remaining is less than compare num
                    activeProcess = processIterator;   //set active process to the iterator value
                    sizeComp = processIterator->remExeTime;  //set new comparison value
                    previousProcess = tmpProcess;      //previous process = temp
                }else{
                    sizeComp = 65535;
                }
                tmpProcess = processIterator;          //store current iterator as "last" for next iteration
                processIterator = processIterator->Qnext;  //set iterator to next in queue
            }
        }
        
        //if (expiredCounter == TOTAL_ROWS){             //if all of the processes are complete
        //    break;                                     //break the loop
        //} else {
            activeProcess->remExeTime --;              //EXECUTE - decreast time remaining
            globalTimeTicker ++;                       //otherwise, there's more work to do, go to next time step
            printf("time:%6ld   PID:%6d   AT:%4d  ", globalTimeTicker, activeProcess->pid, activeProcess->arrivalTime);
            printf("remains:%4d   size:%4d   ", activeProcess->remExeTime, activeProcess->exeTime);
        //}
         printf("%d == %d \n", expiredCounter, TOTAL_ROWS);
    }
    return 0;
}
