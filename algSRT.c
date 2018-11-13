/*    
 CSC521 Operating system
 Project:      2 mydispatcher
 Programmer:   Rob Miles
 Professor:    Dr. Lee
 File Created: Oct 15, 2018
 File Updated: Oct 15, 2018
 */

#include "mydispatcher.h"

int shortestRemainingTime(struct Process *inProc){
    
    int expiredCounter = 0;                            //number of completed processes
    struct Process *queueList;                         //dispatcher queue
    queueList = NULL;                                  //initialized to nothing, gets first process later
    struct Process *activeProcess;                     //which process is "executing"
    activeProcess = queueList;                         //will keep track of the executing process
    struct Process *previousProcess;                   //holds last process for when we need to remove a process
    previousProcess = NULL;                            //it starts as null
    struct Process *processIterator;                   //iterator for process selection
    processIterator = NULL;                            //start with NULL, assign later
    
    while (1) {                                       //check processes left that aren't finished
        unsigned short sizeComp;                      //for process selection
        struct Process *ipIndex = inProc;              //iterator for queue management, reset to head each loop

        while (ipIndex != NULL){                       //iterate input data
            if (!ipIndex->complete){                    //check if the process is live
                if (ipIndex->arrivalTime == globalTimeTicker){  //check if it's new to the queue
                    appendQ(&queueList, &ipIndex);     //append
                    /*if(activeProcess == NULL){                      //if this is the first iteration
                       activeProcess = queueList;                 //set the working process to the head of the list
                        printf("interrupd, activeProcess null\n");
                    }
                    if(activeProcess){
                        if (ipIndex->exeTime < activeProcess->remExeTime){
                            printf("interrupt, append, new shorter one\n");
                            previousProcess = activeProcess;
                            activeProcess = ipIndex;
                        } else {
                            printf("interrupt w append, no further actions %d\n", ipIndex->exeTime);
                        }
                    }*/
                }
            }
            ipIndex = ipIndex->next;                   //go to next item in list
        }
        
        if(activeProcess == NULL)                      //if this is the first iteration
            activeProcess = queueList;                 //set the working process to the head of the list
        printf("tp\n");
        
        if(activeProcess){//
            sizeComp = activeProcess->remExeTime;//
            if (!activeProcess->exeStartTime){         //if this process just began to execute
                activeProcess->exeStartTime = globalTimeTicker;  //record the start time
            }
            
            if (activeProcess->remExeTime == 0){       //see if reminaing time is 0
                if(!activeProcess->complete)           //if it's not dormant
                    expiredCounter++;                  //increase tally for complete processes
                activeProcess->complete = 1;           //if so, mark as complete
                activeProcess->exeDoneTime = globalTimeTicker;
                
                if (activeProcess->Qnext == NULL){     //if at end of queue
                    printf("drop end\n");
                    if (activeProcess == queueList){   //if you're first and last item, complete and work still needs to be done
                        printf("i'm squeezed\n");
                        activeProcess = NULL;
                        queueList = NULL;
                    }else{
                        activeProcess = queueList;     //go back to start of queue
                    }
                        previousProcess->Qnext = NULL; //drop the expired process
                }else{
                    if (!previousProcess || (activeProcess == queueList)){                  //if there is a previous process
                        printf("kill first process");
                        queueList = activeProcess->Qnext;  //otherwise, drop the first process, link head to next
                    }else{
                        printf("normal Drop\n");
                        previousProcess->Qnext = activeProcess->Qnext;//drop completed process from list
                    }
                    activeProcess = activeProcess->Qnext;  //move to the next process
                }
                
                sizeComp = 65535;                      //set large number to compare shorter processes to
                processIterator = queueList;           //set iterator to head of queue
                while (processIterator != NULL){      //loop through queue list
                    if (processIterator->remExeTime < sizeComp){  //if process remaining is less than compare num
                        previousProcess = activeProcess;   //store active process
                        activeProcess = processIterator;   //set active process to the iterator value
                        sizeComp = activeProcess->remExeTime;  //set new comparison value
                    }
                    processIterator = processIterator->Qnext;  //set iterator to next in queue
                    
                }
                if(queueList == NULL)
                    printf("empty queue\n");
            }
            
        }
        if (expiredCounter == TOTAL_ROWS){             //if all of the processes are complete
            break;                                     //break the loop
        } else {
            if(activeProcess){
                if(activeProcess->remExeTime > 0)      //if it's still live
                    activeProcess->remExeTime --;       //EXECUTE - decreast time remaining
                printf("time:%ld   PID:%d   AT:%d  ", globalTimeTicker, activeProcess->pid, activeProcess->arrivalTime);
                printf("remains:%d   sizeComp:%d  size:%d   ", activeProcess->remExeTime, sizeComp, activeProcess->exeTime);
                printf("%d == %d \n", expiredCounter, TOTAL_ROWS);
            }

            globalTimeTicker ++;                       //otherwise, there's more work to do, go to next time step
            
        }
    }
    return 0;
}
