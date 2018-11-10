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

void appendQ(struct Process** head_ref, struct Process ** inProc){
    
    struct Process *last = *head_ref;   /* used in step 5*/
    //struct Process *new_node = (struct Process*) malloc(sizeof(struct Process));
    //new_node = inProc;
    
    (*inProc)->Qnext = NULL;                              //make this the last link
    if (*head_ref == NULL){                            //If the Linked List is empty,
        *head_ref = *inProc;                            //then make the new node as head
        return;
    }
    
    while (last->Qnext != NULL)                        //loop till the last node
        last = last->Qnext;
    
    last->Qnext = *inProc;                             //make this the last node
    
    return;
}

void upQwNew(struct Process inputList, struct Process outputQueue){
    
    
}

int firstComeFirstServe(struct Process *inProc){
    
    struct Process *queueList;
    queueList = NULL;
    struct Process *activeProcess;                     //which process is "executing"
    activeProcess = queueList;

    /*update new processes to queue for each timestep*/
    while (1) {                                        //check processes left that aren't finished
        struct Process *ipIndex = inProc;
        while (ipIndex != NULL){                       //iterate input data
            
            if (!ipIndex->complete){                    //check if the process is live
                if (ipIndex->arrivalTime == globalTimeTicker){  //check if it's new to the queue
                    appendQ(&queueList, &ipIndex);
                }
            }
            ipIndex = ipIndex->next;                     //go to next link
        }
        
        upQwNew(*inProc, *queueList);
        
        if(activeProcess == NULL)
            activeProcess = queueList;
                /*process the queue/currently "executing" process*/
        if (!activeProcess->exeStartTime){       //if this process just began to execute
            activeProcess->exeStartTime = globalTimeTicker;  //record the start time
        }

        if ((activeProcess->remExeTime --) == 0){      //EXECUTE - decreast time remaining and see if it's 0
            activeProcess->complete = 1;               //if so, mark as complete
            activeProcess->exeDoneTime = globalTimeTicker;
            
            if (activeProcess->Qnext == NULL){         //if no more in queue
                printf("end\n");
                return 0;
            }
            activeProcess = activeProcess->Qnext;
        }
        printf("%ld=ticks ", globalTimeTicker);
        printf("%d=rem %d=activeProcess\n", activeProcess->remExeTime, activeProcess->pid);

        globalTimeTicker ++;                           //otherwise, there's more work to do, go to next time step
    }
    return 0;
}
