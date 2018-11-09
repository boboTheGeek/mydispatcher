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
    struct Process* new_node = (struct Process*) malloc(sizeof(struct Process));
    new_node = *inProc;
    new_node->Qnext = NULL;                             //make this the last link
    if (*head_ref == NULL){                            //If the Linked List is empty,
        *head_ref = new_node;                          //then make the new node as head
        return;
    }
    
    while (last->Qnext != NULL)                        //loop till the last node
        last = last->Qnext;
    
    last->Qnext = new_node;                             //make this the last node
    return;
}



int firstComeFirstServe(struct Process *inProc){
    
    //unsigned short int activeProcess = 0;             //which process is "executing"
    int activeProcessesExist = 1;                      //assume at least one live process at init
    unsigned short int index = 0;                 //start evaluation of processes at row 1
    
    
    
    struct Process *queueList;
    queueList = NULL;
    
    /*update new processes to queue for each timestep*/
    while (activeProcessesExist && globalTimeTicker < 50) {        //check processes left that aren't finished
        struct Process *ipIndex = inProc;
        while (ipIndex != NULL){                       //iterate input data
            
            if (!ipIndex->complete){                    //check if the process is live
                activeProcessesExist = 1;              //any live processes sets flag
                if (ipIndex->arrivalTime == globalTimeTicker){  //check if it's new to the queue
                    printf("added one\n");
                    appendQ(&queueList, &inProc);
                    
                    //if (queueList == NULL){
                    //    queueList = inProc;
                    //    printf("%d\n", queueList->pid);
                    //}
                    //while (last->next != NULL)                        //loop till the last node
                    //    last = last->next;
                    //queue[queuePos] = ptr;             //add to queue if just arrived
                    //queuePos++;                        //move to next free space in array
                    //last->next = new_node;
                }
            }
            
            ipIndex = ipIndex->next;                     //go to next link
            
        }
        index++;                                   //increment to next struct in array
        globalTimeTicker ++;                       //otherwise, there's more work to do, go to next time step
        printf("%lu\n", globalTimeTicker);
    }
    
    /*process the queue/currently "executing" process
     if (!queue[activeProcess]->exeStartTime)       //if this process just began to execute
     queue[activeProcess]->exeStartTime = globalTimeTicker;  //record the start time
     if ((queue[activeProcess]->remExeTime --) == 0){//decreast time remaining and see if it's 0
     queue[activeProcess]->complete = 1;        //if so, mark as complete
     queue[activeProcess]->exeDoneTime = globalTimeTicker;
     activeProcess++;                           //move to next process in queue
     if (!queue[activeProcess]){                //if no more in queue
     activeProcessesExist = 0;              //turn off flag
     }
     }
     
     if (activeProcessesExist == 0){                //if all processes are complete
     return 0;                                  // finish successfully
     } else {
     
     printf("%ld=ticks %d=active ", globalTimeTicker, activeProcessesExist);
     printf("%d=rem %d=activeProcess  %d=index\n", queue[activeProcess]->remExeTime, activeProcess, index);
     */

    return 0;
}
