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



int firstComeFirstServe(struct Process *inProc){
    
    printf("%lu\n", globalTimeTicker);
    int activeProcessesExist = 1;                      //assume at least one live process at init
                                                       //unsigned short int index = 0;                 //start evaluation of processes at row 1
    
    struct Process *queueList;
    queueList = NULL;
    struct Process *activeProcess;             //which process is "executing"
    
    /*update new processes to queue for each timestep*/
    while (activeProcessesExist && globalTimeTicker < 100) {        //check processes left that aren't finished
        struct Process *ipIndex = inProc;
        while (ipIndex != NULL){                       //iterate input data
            
            if (!ipIndex->complete){                    //check if the process is live
                activeProcessesExist = 1;              //any live processes sets flag
                if (ipIndex->arrivalTime == globalTimeTicker){  //check if it's new to the queue
                    appendQ(&queueList, &ipIndex);
                }
            }
            ipIndex = ipIndex->next;                     //go to next link
        }
        
        //printf("%lu\n", globalTimeTicker);
        
        /*
        struct Process * qI = queueList;
        while (qI != NULL){
            printf("pid %d\n", qI->pid);
            qI = qI->Qnext;
            
        }*/
        activeProcess = queueList;
        /*process the queue/currently "executing" process*/
        if (!activeProcess->exeStartTime){       //if this process just began to execute
            activeProcess->exeStartTime = globalTimeTicker;  //record the start time
            
        }
        printf("x %d\n", activeProcess->exeStartTime);
        if ((activeProcess->remExeTime --) == 0){//EXECUTE - decreast time remaining and see if it's 0
            activeProcess->complete = 1;        //if so, mark as complete
            activeProcess->exeDoneTime = globalTimeTicker;
            if (!activeProcess->Qnext){                //if no more in queue
                activeProcessesExist = 0;              //turn off flag
            } else {
                printf("%ld=ticks %d=active ", globalTimeTicker, activeProcessesExist);
                printf("%d=rem %d=activeProcess\n", activeProcess->remExeTime, activeProcess->pid);
                activeProcess = activeProcess->Qnext;                           //move to next process in queue
            }
        }
        
        if (activeProcessesExist == 0){                //if all processes are complete
            return 0;                                  // finish successfully
        }
        globalTimeTicker ++;                       //otherwise, there's more work to do, go to next time step
    }
    return 0;
}
