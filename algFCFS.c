/*    
 CSC521 Operating system
 Project:      2 mydispatcher
 Programmer:   Rob Miles
 Professor:    Dr. Lee
 File Created: Oct 15, 2018
 File Updated: Nov 7, 2018
 */
#include <stdlib.h>

#include "mydispatcher.h"


int firstComeFirstServe(struct Process *inProc){
    int expiredCounter = 0;                            //number of completed processes
    struct Process *queueList;
    queueList = NULL;
    struct Process *activeProcess;                     //which process is "executing"
    activeProcess = queueList;

    while (1) {                                        //check processes left that aren't finished
        struct Process *ipIndex;
        ipIndex = inProc;                              //iterator for queue management, reset to head each loop
        while (ipIndex != NULL){                      //iterate input data
            if (!ipIndex->complete){                   //check if the process is live
                if (ipIndex->arrivalTime == globalTimeTicker){  //check if it's new to the queue
                    appendQ(&queueList, &ipIndex);     //append
                }
            }
            ipIndex = ipIndex->next;                    //go to next link
        }
      
        if(activeProcess == NULL)                      //if this is the first iteration
            activeProcess = queueList;                 //set the working process to the head of the list

        if (!activeProcess->exeStartTime){             //if this process just began to execute
            activeProcess->exeStartTime = globalTimeTicker;  //record the start time
        }

        if (activeProcess->remExeTime == 0){           //EXECUTE - decreast time remaining and see if it's 0
            if(!activeProcess->complete)               //catch when stalled on empty queue
                expiredCounter++;                      //increase tally for complete processes
            activeProcess->complete = 1;               //if so, mark as complete
            activeProcess->exeDoneTime = globalTimeTicker;
            
            if (expiredCounter == TOTAL_ROWS){         //if no more in queue exit function
                return 0;
            }
            if(activeProcess->Qnext)                   //jump to Qnext if there is one
                activeProcess = activeProcess->Qnext;
        }
        if(!activeProcess->complete)                   //do work if activeProcess is live
            activeProcess->remExeTime --;
        //printf("%ld=ticks ", globalTimeTicker);
        //printf("%d=rem %d=activeProcess  ", activeProcess->remExeTime, activeProcess->pid);
        //printf("%d=expiredCounter\n", expiredCounter);
        globalTimeTicker ++;                           //otherwise, there's more work to do, go to next time step
    }
    return 0;
}
