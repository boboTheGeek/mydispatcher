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
    unsigned short sliceSize = 3;                     //default quantum size
                                                       //unsigned short sliceIn = 1;                       //init quantum input size
    int expiredCounter = 0;                            //number of completed processes
    
    struct Process *queueList;                         //dispatcher queue
    queueList = NULL;                                  //initialized to nothing, gets first process later
    struct Process *activeProcess;                     //which process is "executing"
    activeProcess = queueList;                         //will keep track of the executing process
    struct Process *previousProcess;                   //holds last process for when we need to remove a process
    previousProcess = NULL;                            //it starts as null
    
    while (1) {
        struct Process *ipIndex;
        ipIndex = inProc;              //iterator for queue management, reset to head each loop
        while (ipIndex != NULL){                       //iterate input data
            if (!ipIndex->complete){                    //check if the process is live
                if (ipIndex->arrivalTime == globalTimeTicker){  //check if it's new to the queue
                    printf(" pid %d\n", ipIndex->pid);
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
            activeProcess->exeDoneTime = globalTimeTicker; //capture when it finishes
            slicePosition = 1;                         //reset quantum counter
            
            if (expiredCounter == TOTAL_ROWS){         //if no more in queue
                return 0;
            }
            
            if (activeProcess->Qnext == NULL){         //if at end of queue
                activeProcess = queueList;              //go back to start of queue
                //what if this was the last
                if(previousProcess)
                    previousProcess->Qnext = NULL;     //drop the expired process

            } else {
                if (previousProcess){                  //if there is a previous process
                    previousProcess->Qnext = activeProcess->Qnext;//link to jump over active (expired)
                } else {
                    queueList = activeProcess->Qnext;  //otherwise, drop the first process, link head to next
                }
                activeProcess = activeProcess->Qnext;  //move to the next process
            }
        } else if (slicePosition == sliceSize){       //check if quantum is up
            if (activeProcess->Qnext == NULL){         //if there is no process there
                activeProcess = queueList;             //go back to start of queue
            } else {
                previousProcess = activeProcess;       //track last active process
                activeProcess = activeProcess->Qnext;  //if so, move to next in queue
            }
            slicePosition = 1;                         //reset quantum position
        } else {
            slicePosition ++;                          //increment quantum position
        }
        
        if(activeProcess->remExeTime>0 )               //if process is still live
            activeProcess->remExeTime --;              //EXECUTE - decreast time remaining
        globalTimeTicker ++;                           //otherwise, there's more work to do, go to next time step
            
        printf("time:%6ld   PID:%6d   AT:%4d  ", globalTimeTicker, activeProcess->pid, activeProcess->arrivalTime);
        printf("remains:%4d   sliceloc:%4d   ", activeProcess->remExeTime, slicePosition);
        printf("%d == %d \n", expiredCounter, TOTAL_ROWS);
    }
    return 0;
}
